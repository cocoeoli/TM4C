#include "timer_config.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

void timer0_init(uint32_t ms)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
        ;

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);//使用全宽32位定时器周期计数模式

    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, ms*(SysCtlClockGet()/3000));
    IntPrioritySet(INT_TIMER0A|INT_TIMER0B,0x03);
    TimerIntRegister(TIMER0_BASE, TIMER_BOTH, Timer0_IntHandler);
    IntEnable(INT_TIMER0A);
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_BOTH);
}

void WTimer0_CCP01_init()
{
    //打开相应外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0)) ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) ;
    
    //引脚复用配置
    GPIOPinConfigure(GPIO_PC4_WT0CCP0);
    GPIOPinConfigure(GPIO_PC5_WT0CCP1);
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_5);

    //定时器工作方式设置
    TimerConfigure(WTIMER0_BASE,  TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_B_CAP_TIME_UP);
    TimerControlEvent(WTIMER0_BASE, TIMER_BOTH, TIMER_EVENT_POS_EDGE);
    
    //注册中断函数
    TimerIntRegister(WTIMER0_BASE, TIMER_A, WTimer0_CCP0_IntHandler);
    TimerIntRegister(WTIMER0_BASE, TIMER_B, WTimer0_CCP1_IntHandler);
    
    //先关闭，需要是打开中断
    IntEnable(INT_WTIMER0A);
    IntEnable(INT_WTIMER0B);
//    IntDisable(INT_WTIMER0A);
//    IntDisable(INT_WTIMER0B);
    IntPrioritySet(INT_WTIMER0A|INT_WTIMER0B,0x04);

//    TimerIntEnable(WTIMER0_BASE, TIMER_CAPA_EVENT);
//    TimerIntEnable(WTIMER0_BASE, TIMER_CAPB_EVENT);
    TimerIntDisable(WTIMER0_BASE, TIMER_CAPA_EVENT);
    TimerIntDisable(WTIMER0_BASE, TIMER_CAPB_EVENT);
    
    //开启定时器
    TimerEnable(WTIMER0_BASE, TIMER_BOTH);
}
//void WTimer1_CCP01_init()
//{
//    //打开相应外设
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER1))
//        ;
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
//        ;
//
//    //引脚复用配置
//    GPIOPinConfigure(GPIO_PC6_WT1CCP0);
//    GPIOPinConfigure(GPIO_PC7_WT1CCP1);
//    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_6);
//    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_7);
//
//    //定时器工作方式设置
//    TimerConfigure(WTIMER1_BASE,  TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_B_CAP_TIME_UP);
//    TimerControlEvent(WTIMER1_BASE, TIMER_BOTH, TIMER_EVENT_POS_EDGE);
//
//    //注册中断函数
//    TimerIntRegister(WTIMER1_BASE, TIMER_A, WTimer1_CCP0_IntHandler);
//    TimerIntRegister(WTIMER1_BASE, TIMER_B, WTimer1_CCP1_IntHandler);
//
//    //开启中断
//    IntEnable(INT_WTIMER1A);
//    IntEnable(INT_WTIMER1B);
//    TimerIntEnable(WTIMER1_BASE, TIMER_CAPA_EVENT);
//    TimerIntEnable(WTIMER1_BASE, TIMER_CAPB_EVENT);
//
//    //开启定时器
//    TimerEnable(WTIMER1_BASE, TIMER_BOTH);
//}
