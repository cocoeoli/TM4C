/*
 * pwm_config.c
 *
 *  Created on: 2019.4.21
 *      Author: DuYihao
 */
#include "pwm_config.h"

int pwm_clock_div;

void PWM_clock_div_set(void)
{
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
    pwm_clock_div = 16;
}

void PWM0_0123_init(void)//驱动电机
{
    //开启外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;
    
    //时钟分频
    PWM_clock_div_set();
    
    //引脚复用配置
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);

    //发生器设置
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //频率设置
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/pwm_clock_div/1000);//1KHz
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/pwm_clock_div/1000);//1KHz
    
    //脉宽设置
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)*60/100);//Duty:60%
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)*60/100);//Duty:60%
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)*60/100);//Duty:60%
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)*60/100);//Duty:60%

    //打开发生器
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    
    //关闭输出
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, false);
}

void PWM0_4567_init(void)//伺服电机
{
    //开启外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    //时钟分频
    PWM_clock_div_set();
    
    //引脚复用设置
    GPIOPinConfigure(GPIO_PE4_M0PWM4);
    GPIOPinConfigure(GPIO_PE5_M0PWM5);
    GPIOPinConfigure(GPIO_PC4_M0PWM6);
    GPIOPinConfigure(GPIO_PC5_M0PWM7);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
    
    //发生器工作模式设置
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //频率设置
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/pwm_clock_div/50);//50Hz
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, SysCtlClockGet()/pwm_clock_div/50);//50Hz
    
    //脉宽设置
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*95/1000);//pulse:500us
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*75/1000);//pulse:2500us
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*75/1000);//pulse:500us
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*115/1000);//pulse:500us

    //打开发生器
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    
    //关闭输出
    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);
}
