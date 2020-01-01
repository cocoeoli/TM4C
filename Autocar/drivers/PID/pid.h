#ifndef __PID_H
#define __PID_H

#include <stdbool.h>
#include <stdint.h>

#define allow_error 1       //����

typedef struct pid
{
 //  float ref;     //�趨ֵ
 //  float fdb;     //����ֵ
     
	 float T;          //��λms
     float KP;         //a0 = Kp+Ki*T+Kd/T
     float KD;         //a1 = Kp+2Kd/T
     float KI;         //a2 = Kd/T
     
     float error;      //�������
     float error_1;    //�ϴ����
     float error_2;    //���ϴ����
     
     float output;     //pid�������  
     float output_1;   //pid�ϴ����

}PID_value;                    

void str_float(void);
void PID_Init(void);
void check_yaw(float yaw);
void PID_operation(PID_value *p);
void PID_out(float given_yaw, float this_yaw);

void Change_pid(void);
void position_pid(float given_dis, float this_dis);

uint8_t constrain_int(uint8_t amt, uint8_t low, uint8_t high);      //


		 				    
#endif
