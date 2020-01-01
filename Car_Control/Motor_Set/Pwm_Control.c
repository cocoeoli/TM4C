/*
 * Pwm_Control.c
 *
 *  Created on: 2018年2月1日
 *      Author: wk
 */

#include "Pwm_Control.h"
#include "delay.h"
#include "pid.h"

extern uint32_t QEI0_Value, QEI1_Value;
extern int pid_result;

void MoTor_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);//设置PWM模块的时钟，此处即系统时钟2分频.

    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinConfigure(GPIO_PE4_M0PWM4);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/16/1000);   //1000Hz
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/16/1000);  //1000Hz
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/16/50);   //50Hz
}

void Steering_Gear_SET_Direction(int Steering_Gear_Angle)
{
    float fTempDuty = 0.025*Steering_Gear_Angle + 7.2;

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, (int)(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*fTempDuty/100.0) );
    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}
int  MoTor_SET_Direction(int Motor_Direction)
{
//    if(Motor_Direction > 0)//正转
//    {
//        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_7);  //set direction
//        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_7);
//        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);
//        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
//
//        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);  //set direction
//        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
//        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
//
//        return 1;//set speed ?--?
//    }
//    else if(Motor_Direction < 0)//反转
//    {
//        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_7);  //set direction
//        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_7);
//        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
//        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
//
//        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);  //set direction
//        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
//        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
//
//        return -1;
//    }
    if(Motor_Direction > 0)//正转
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_7);  //set direction
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);

        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);  //set direction
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);

        return 1;//set speed ?--?
    }
    else if(Motor_Direction < 0)//反转
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_7);  //set direction
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_7);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);

        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);  //set direction
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);

        return -1;
    }
    else//停止
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_7);  //set direction
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);

        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);  //set direction
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);

        return 0;
    }
}

void MoTor_Speed_Set(int PWMPulseWidth1, int PWMPulseWidth2)
{
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)*PWMPulseWidth1)/330);
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)*PWMPulseWidth2)/300);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}

void MoTor_Left_Speed_Set(int PWMPulseWidth1)
{
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)*PWMPulseWidth1)/330);
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
void MoTor_Right_Speed_Set(int PWMPulseWidth2)
{
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)*PWMPulseWidth2)/300);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
void MoTor_Set(int Motor_Direction1, int PWMPulseWidth1, int Motor_Direction2, int PWMPulseWidth2)
{
    MoTor_SET_Direction(Motor_Direction1);
    MoTor_SET_Direction(Motor_Direction2);
    MoTor_Speed_Set(PWMPulseWidth1, PWMPulseWidth2);
}
