/*
 * pid.c
 *
 *  Created on: 2018��1��29��
 *      Author: wk
 */

#include "pid.h"

void PID_init(void)
{
    pid.SetSpeed = 0;
    pid.ActualSpeed=0.0;
    pid.err        =0.0;
    pid.err_last   =0.0;
    pid.voltage    =0.0;
    pid.integral   =0.0;
    pid.Kp         =0.02; //�Լ��趨
    pid.Ki         =0.0002;   //�Լ��趨
    pid.Kd         =0.0005;//�Լ��趨
}
void PIDP_init(void)
{
    pidp.SetSpeed = 0;
    pidp.ActualSpeed=0.0;
    pidp.err        =0.0;
    pidp.err_last   =0.0;
    pidp.voltage    =0.0;
    pidp.integral   =0.0;
    pidp.Kp         = - 20; //�Լ��趨
    pidp.Ki         = 0 ;   //�Լ��趨
    pidp.Kd         = 10 ;//�Լ��趨
}
float Pid_Speed(float goal_speed, float now_speed)
{
    pid.SetSpeed    = goal_speed;                //�趨ֵ
    pid.ActualSpeed = now_speed;                //ʵ��ֵ
    pid.err         = goal_speed - now_speed;  //�趨ֵ-ʵ��ֵ
    pid.integral   += pid.err;                //����ֵ��ƫ���ۼ�
    pid.voltage     = pid.Kp*pid.err +
                      pid.Ki*pid.integral +
                      pid.Kd*(pid.err-pid.err_last);
    pid.err_last    = pid.err;            //��һ��ƫ��ֵ
    pid.ActualSpeed = pid.voltage*2.0;   //���ʵ��ֵ

    return pid.ActualSpeed;            //����
}

int Pid_Pos(int Encoder )
{
    static float Position_Bias, Position_Differential;
    pidp.err = Encoder;
    Position_Bias *= 0.8;
    Position_Bias += pidp.err*0.2;
    Position_Differential=Position_Bias-pidp.err_last;
    pidp.err_last = Position_Bias;
    pidp.ActualSpeed = Position_Bias*pidp.Kp+Position_Differential*pidp.Kp;
    return pidp.ActualSpeed;
}


