/*
 * pid.c
 *
 *  Created on: 2018年1月29日
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
    pid.Kp         =0.02; //自己设定
    pid.Ki         =0.0002;   //自己设定
    pid.Kd         =0.0005;//自己设定
}
void PIDP_init(void)
{
    pidp.SetSpeed = 0;
    pidp.ActualSpeed=0.0;
    pidp.err        =0.0;
    pidp.err_last   =0.0;
    pidp.voltage    =0.0;
    pidp.integral   =0.0;
    pidp.Kp         = - 20; //自己设定
    pidp.Ki         = 0 ;   //自己设定
    pidp.Kd         = 10 ;//自己设定
}
float Pid_Speed(float goal_speed, float now_speed)
{
    pid.SetSpeed    = goal_speed;                //设定值
    pid.ActualSpeed = now_speed;                //实际值
    pid.err         = goal_speed - now_speed;  //设定值-实际值
    pid.integral   += pid.err;                //积分值，偏差累加
    pid.voltage     = pid.Kp*pid.err +
                      pid.Ki*pid.integral +
                      pid.Kd*(pid.err-pid.err_last);
    pid.err_last    = pid.err;            //上一个偏差值
    pid.ActualSpeed = pid.voltage*2.0;   //算出实际值

    return pid.ActualSpeed;            //返回
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


