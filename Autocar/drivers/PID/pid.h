#ifndef __PID_H
#define __PID_H

#include <stdbool.h>
#include <stdint.h>

#define allow_error 1       //死区

typedef struct pid
{
 //  float ref;     //设定值
 //  float fdb;     //测量值
     
	 float T;          //单位ms
     float KP;         //a0 = Kp+Ki*T+Kd/T
     float KD;         //a1 = Kp+2Kd/T
     float KI;         //a2 = Kd/T
     
     float error;      //本次误差
     float error_1;    //上次误差
     float error_2;    //上上次误差
     
     float output;     //pid控制输出  
     float output_1;   //pid上次输出

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
