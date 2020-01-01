/*
 * pid.h
 *
 *  Created on: 2018年1月29日
 *      Author: wk
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#include<stdio.h>
#include<stdlib.h>
struct _pid
    {
        float SetSpeed;         //定义设定值
        float ActualSpeed;      //定义实际值
        float err;              //定义偏差值
        float err_last;         //定义上一个偏差值
        float Kp,Ki,Kd;         //定义比例、积分、微分系数
        float voltage;          //定义电压值（控制执行器的变量）
        float integral;         //定义积分值
    }pid,pidp;

extern void PID_init(void);
void PIDP_init(void);
extern float Pid_Speed(float goal_speed, float now_speed);
int Pid_Pos(int Encoder );

#endif /* PID_PID_H_ */
