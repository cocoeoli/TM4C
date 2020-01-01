#include "pid.h"
#include "stdio.h"
#include "string.h"
#include "../mpu6050/inv_mpu.h"
#include "../uart/uart.h"
#include "../car_ctrl/car_ctrl.h"
#include "pid.h"

PID_value  pid_yaw;
PID_value  pid_pos;

extern char uart0_buff[Buff0_Len];
extern char uart1_buff[Buff1_Len];
extern char uart5_buff[Buff5_Len];
extern float set_yaw;
extern uint8_t Pose;

void PID_Init(void)
{
	memset(&pid_yaw, 0, sizeof(PID_value));
	memset(&pid_pos, 0, sizeof(PID_value));
	pid_yaw.KP = 10;
	pid_yaw.KD = 200;
	pid_yaw.KI = 0;
	pid_yaw.T = 1;            //��λs

	pid_pos.KP = 1;
	pid_pos.KD = 0;
	pid_pos.KI = 0;
	pid_pos.T = 1;            //��λs

}
//*A@0@0@0@#

 void check_yaw(float yaw)      //�ж��Ƿ���ҪPid����
 {
		float dis_yaw=0;
		dis_yaw = yaw - set_yaw;

        if((dis_yaw <= 0 && dis_yaw > -allow_error) || (dis_yaw >= 0 && dis_yaw < allow_error)){  //�жϽǶ�ƫ���Ƿ�С�ڹ涨ֵ
            switch(Pose)
             {
             case 0: {
                car_stop();
                break;
             }
             case 0x01: {                //ǰ��
                 car_go_forward();
                 break;
             }
             case 0x02: {
                 car_go_back();
                 break;
             }
             case 0x04: {
                 car_go_left();
                break;
             }
             case 0x08: {
                 car_go_right();
                 break;
             }
//             case '5': {
//                   set_yaw = 0;             //0��
//                   UART_send_string("0 C \n", UART1_BASE);
//                   break;
//               }
//             case '6': {
//                   set_yaw = 90;            //90
//                   UART_send_string("90 C \n", UART1_BASE);
//                   break;
//               }
//             case '7': {
//                   set_yaw = -90;
//                   UART_send_string("-90 \n", UART1_BASE);
//                  break;
//               }
//             case '8': {
//                   set_yaw = -180;
//                   UART_send_string("-180 \n", UART1_BASE);
//                   break;
//               }
             }

        }else PID_out(set_yaw, yaw);


 }

void PID_operation(PID_value *p)
{   
    float a0,a1,a2;
    //�����м����a0,a1,a2;
    a0 = p->KP + p->KI*p->T + p->KD/p->T ;
    a1 = p->KP + 2*p->KD/p->T ;
    a2 = p->KD/p->T ;
    //�������
    p->output = p->output_1 + a0*p->error - a1*p->error_1 + a2*p->error_2 ;
    //Ϊ�´μ������
    //����˳��ǧ��Ҫ�����Ȼ���ռ�ձ��Ǵ���ġ�
    p->output_1 = p->output;
    p->error_2 = p->error_1;
    p->error_1 = p->error;
}

void PID_out(float given_yaw, float this_yaw)
{
    uint8_t  pid_speed;

    if(given_yaw<-175){
        if(this_yaw > 120)
            this_yaw = -180 - (180-this_yaw);
    }
    pid_yaw.error = this_yaw - given_yaw ;    //ƫ��

    PID_operation(&pid_yaw);

    if(pid_yaw.output < 0)
        pid_speed = constrain_int(-(int)(pid_yaw.output*0.2 + pid_yaw.output_1*0.8), 5, 20);       //���Է�Χ��Ӧ
    else pid_speed = constrain_int((int)(pid_yaw.output*0.2 + pid_yaw.output_1*0.8), 5, 20);

    switch(Pose)         //��ͬ��̬��ͬ����
    {
         case 0:{
         if(pid_yaw.error>3){       //�������allow_error
                car_turn_right(10+pid_speed);
              }
          else{                //���С��-allow_error
              if(pid_yaw.error<-3)
             car_turn_left(10+pid_speed);
          }
          break;
         }
         case 0x01: {                //ǰ��
             if(pid_yaw.error>allow_error){       //�������allow_error
                         car_forward_right(pid_speed);
                     }
                     else{                //���С��-allow_error
                         if(pid_yaw.error<-allow_error)
                         car_forward_left(pid_speed);
                     }
             break;
         }
         case 0x02: {
             if(pid_yaw.error>allow_error){       //�������allow_error
                         car_back_left(pid_speed);
                     }
                     else{                //���С��-allow_error
                         if(pid_yaw.error<-allow_error)
                         car_back_right(pid_speed);
                     }
             break;
         }
         case 0x04: {
             if(pid_yaw.error>allow_error){       //�������allow_error
                 car_left_left(pid_speed);
                 }
                 else{                //���С��-allow_error
                     if(pid_yaw.error<-allow_error)
                 car_left_right(pid_speed+8);
                 }
            break;
         }
         case 0x08: {
             if(pid_yaw.error>allow_error){       //�������allow_error
                 car_right_left(pid_speed+8);
                 }
                 else{                //���С��-allow_error
                     if(pid_yaw.error<-allow_error)
                 car_right_right(pid_speed);
                 }
             break;
         }
     }

}

void position_pid(float given_dis, float this_dis)
{
    uint8_t cspeed;
    pid_pos.error = this_dis - given_dis ;    //ƫ��
    PID_operation(&pid_pos);

    if( (pid_pos.error < -15)  ||  (pid_pos.error > 15) ){
        if( pid_pos.output < 0){  //����
                   cspeed = 15 + -(int)pid_pos.output;
                   cspeed = constrain_int(cspeed ,20, 60);
                   car_wheel_dir_set(1, 0, 0, 1);
                   car_wheel_speed_set(cspeed, cspeed+2, cspeed, cspeed);
                   Pose = 0x04;
            }else{                               //����
                    cspeed = 15 + (int)pid_pos.output;
                    cspeed = constrain_int(cspeed ,20, 60);
                    car_wheel_dir_set(0, 1, 1, 0);
                    car_wheel_speed_set(cspeed, cspeed+2, cspeed, cspeed);
                    Pose = 0x08;
            }
    }

}

uint8_t constrain_int(uint8_t amt, uint8_t low, uint8_t high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//////���16λ��buff����
void str_float(void)                                   //�ַ����и�ת���㺯�������ڵ��Σ� �ַ�����ʽ��" *A@kp@ki@kd@#" ǰ��@Ҫ��Ҫ����
{
    uint8_t i=0;
    char *temp, strp[30];
    float num[4];    //����и���

    for(i=0; i<30; i++)
    {
        strp[i] = uart1_buff[i];
    }

    for(i=0; i<30; i++)
        if(strp[i] == 0x23)
            strp[i] = '\0';

    temp = strtok(strp, "@");
    for(i=0; i<5; i++){                             //�ַ���תfloat����
        if(temp!=NULL){
           sscanf(temp, "%f", &num[i]);
           temp = strtok(NULL,"@");
        }
    }
//    pid_yaw.KP = num[1];
//    pid_yaw.KI = num[2];
//    pid_yaw.KD = num[3];
    pid_pos.KP = num[1];
    pid_pos.KI = num[2];
    pid_pos.KD = num[3];
    sprintf(strp, "kp:%.4f ki:%.4f kd:%.4f \n", num[1], num[2], num[3]);
    UART_send_string(strp, UART1_BASE);
    memset(uart1_buff, '\0', sizeof(uart1_buff));
}

void Change_pid(void)
{
    uint8_t i = 0;
    char strp[15];
    float Num=0;

    for(i=0; i<15; i++)
        strp[i] = uart5_buff[i+1];

    for(i=0; i<15; i++)
        if(strp[i] == 0x23){
            strp[i] = '\0';
            break;
      }
     sscanf(strp+1, "%f", &Num);
     switch(strp[0])
     {
     case 'P' : pid_yaw.KP = Num;
         break;
     case 'I'  : pid_yaw.KI = Num;
         break;
     case 'D' : pid_yaw.KD = Num;
          break;
     default :  break;
     }
}


