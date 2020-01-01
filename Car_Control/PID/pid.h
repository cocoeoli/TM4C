/*
 * pid.h
 *
 *  Created on: 2018��1��29��
 *      Author: wk
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#include<stdio.h>
#include<stdlib.h>
struct _pid
    {
        float SetSpeed;         //�����趨ֵ
        float ActualSpeed;      //����ʵ��ֵ
        float err;              //����ƫ��ֵ
        float err_last;         //������һ��ƫ��ֵ
        float Kp,Ki,Kd;         //������������֡�΢��ϵ��
        float voltage;          //�����ѹֵ������ִ�����ı�����
        float integral;         //�������ֵ
    }pid,pidp;

extern void PID_init(void);
void PIDP_init(void);
extern float Pid_Speed(float goal_speed, float now_speed);
int Pid_Pos(int Encoder );

#endif /* PID_PID_H_ */
