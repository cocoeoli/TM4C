//#include <stdio.h>
//#include <string.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_memmap.h"
//#include "inc/hw_gpio.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/pwm.h"
//#include "utils/uartstdio.h"
//#include "pid.h"
//#include "../uart/uart.h"
//#include "../QEI/QEI_Model.h"
//#include "../adc/adc.h"
//
//#define allow_error 50
//#define stop_area  500
//
//PID_value  pid_yaw;
//PID_value  pid_position;
//
//extern uint8_t  ui8RxBuffer[20];
//
//bool pid_dir=true;
//
//void PID_Init()
//{
//    memset(&pid_yaw, 0, sizeof(PID_value));
//    pid_yaw.KP = 1;
//    pid_yaw.KD = 0;
//    pid_yaw.KI = 0;
//    pid_yaw.T = 0.005;            //��λs
//    memset(&pid_position, 0, sizeof(PID_value));
//    pid_position.KP = 1;
//    pid_position.KD = 0;
//    pid_position.KI = 0;
//    pid_position.T = 0.025;
//}
//
//void position_pid(void)
//{
////        static uint16_t jcount=0;
//        uint8_t i;
//        char char_buf[10];
//        float a0,a1,a2;
//        int position_value = 0;
//
//        for(i=0; i<3; i++)
//          position_value = read_QEI();
//        if(pid_dir == true){
//          if(position_value < 0)
//              position_value = -position_value;
//        }else{
//          if(position_value > 0 )
//              position_value = -position_value;
//        }
//        position_value = position_value/3;
//
//        sprintf(char_buf, "%d", position_value);
//        sscanf(char_buf, "%f", &pid_position.error);
//
//        a0 = pid_position.KP + pid_position.KI*pid_position.T + pid_position.KD/pid_position.T ;
//        a1 = pid_position.KP + 2*pid_position.KD/pid_position.T ;
//        a2 = pid_position.KD/pid_position.T ;
//        //�������
//        pid_position.output = pid_position.output_1 + a0*pid_position.error - a1*pid_position.error_1 + a2*pid_position.error_2 ;
//
//        //Ϊ�´μ������
//        //����˳��ǧ��Ҫ�����Ȼ���ռ�ձ��Ǵ���ġ�
//        pid_position.output_1 = pid_position.output;
//        pid_position.error_2 = pid_position.error_1;
//        pid_position.error_1 = pid_position.error;
//
////        if(jcount++>50){
////             UARTprintf("pid_position.error: %d \n",(int)pid_position.error);
////             jcount = 0;
////        }
//}
//
//
//void yaw_pid(void)
//{
//    float a0,a1,a2;
//
//    //�����м����a0,a1,a2;
//    a0 = pid_yaw.KP + pid_yaw.KI*pid_yaw.T + pid_yaw.KD/pid_yaw.T ;
//    a1 = pid_yaw.KP + 2*pid_yaw.KD/pid_yaw.T ;
//    a2 = pid_yaw.KD/pid_yaw.T ;
//    //�������
//    pid_yaw.output = pid_yaw.output_1 + a0*pid_yaw.error - a1*pid_yaw.error_1 + a2*pid_yaw.error_2 ;
//    //Ϊ�´μ������
//    //����˳��ǧ��Ҫ�����Ȼ���ռ�ձ��Ǵ���ġ�
//    pid_yaw.output_1 = pid_yaw.output;
//    pid_yaw.error_2 = pid_yaw.error_1;
//    pid_yaw.error_1 = pid_yaw.error;
//
//}
//
//void PID_out(uint16_t given_yaw)
//{
//        static uint16_t j=0;
//        uint16_t pid_speed, yaw_speed, position_speed;
//        uint16_t this_yaw;
//
//        this_yaw = Get_ad0();
//        pid_yaw.error = (float)(this_yaw - given_yaw) ;    //ƫ��
//        if(pid_yaw.error > stop_area || pid_yaw.error < -stop_area ){
//            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 , 0);
//            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6 , 0);
//        }else{
//            if(pid_yaw.error > given_yaw){                     //��ת
//                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 , 0);
//                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6 , GPIO_PIN_6);
//                pid_dir = true;
//            }
//            else{
//                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 , GPIO_PIN_5);
//                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6 , 0);
//                pid_dir = false;
//            }
//        }
//
//        if(pid_yaw.error > allow_error || pid_yaw.error < -allow_error){
//            yaw_pid();                                //�ǶȻ�
//            if(pid_yaw.output < 0)
//                pid_yaw.output = -pid_yaw.output;
//            UARTprintf("pid_yaw.output: %d \n",(int)pid_yaw.output);
//            yaw_speed = constrain_int((int)pid_yaw.output, 40, 95);
//        }  else  yaw_speed = 0;
//
//        if(j%5 == 0){
//            position_pid();
//            if(pid_position.output < 0)
//                pid_position.output = -pid_position.output;
//            UARTprintf("pid_position.output: %d \n",(int)pid_position.output);
//            position_speed = constrain_int((int)pid_position.output, 0, 65);
//        }  else position_speed = 0;
//
//        pid_speed = (8*yaw_speed + 2*position_speed)/10 + 30;
//        pid_speed = constrain_int(pid_speed, 1, 90);
//
//        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*pid_speed) / 100 );
//        if(j++>100){
//           UARTprintf("\n pid_speed: %d \n",pid_speed);
//           j = 0;
//        }
//
//}
//
//
//uint16_t constrain_int(uint16_t amt, uint16_t low, uint16_t high)
//{
//    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
//}
//
//
//
//void str_float(void)                                   //�ַ����и�ת���㺯�������ڵ��Σ� �ַ�����ʽ��" *A@kp@ki@kd@#" ǰ��@Ҫ��Ҫ����
//{
//    uint8_t i=0;
//    char *temp, strp[30];
//    float num[5];    //����и���
//
//    UARTprintf("ui8RxBuffer: %s \n",ui8RxBuffer);
//    while(ui8RxBuffer[i] != 0x23)                  //û���ַ���ĩβ
//        sprintf(strp+i, "%c", ui8RxBuffer[i++]);   //��USART2_RX_BUFת�����ַ���  ע�������ַ�ָ�����ַ�������棡��ֹĪ��bug
//
//    UARTprintf("Strp: %s \n",strp);
//
////    for(i=0; i<strlen(strp)-1; i++){
////        if( strp[i] == '@' )
////        j++;                                          //�ж��м��������и�
////    }
//
//    temp = strtok(strp, "@");
//    UARTprintf("temp: %s \n",temp);
//
//    for(i=0; i<5; i++){                             //�ַ���תfloat����
//        if(temp!=NULL){
//           sscanf(temp, "%f", &num[i]);
//           temp = strtok(NULL,"@");
//        }
//    }
////    pid_position.KP = num[0];
////    pid_position.KI = num[1];
////    pid_position.KD = num[2];
////    UARTprintf("kp: %d ki :%d kd: %d \n",(int)pid_position.KP*1000, (int)pid_position.KI*1000, (int)pid_position.KD*1000);
//
//    pid_yaw.KP = num[0];
//    pid_yaw.KI = num[1];
//    pid_yaw.KD = num[2];
//    UARTprintf("kp: %d ki :%d kd: %d \n",(int)pid_yaw.KP*1000, (int)pid_yaw.KI*1000, (int)pid_yaw.KD*1000);
//    memset(ui8RxBuffer, '\0', sizeof(ui8RxBuffer));
//
//}
//
