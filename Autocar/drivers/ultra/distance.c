#include "distance.h"
#include "../timer/timer_config.h"
#include "driverlib/gpio.h"
#include "../my_delay/delay.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

void distance_measure_init(void)
{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
//        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) ;
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
//        ;
    
//    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x00);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0x00);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0x00);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    
//     timer0_init(100);              //¸ÄÓÃwtimer2
    WTimer0_CCP01_init();
//    WTimer1_CCP01_init();
}

//void distance1_trig(void)
//{
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0xFF);
//    ROM_SysCtlDelay(SysCtlClockGet()/300000);//10us
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x00);
//}
void distance2_trig(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0xFF);
    SysCtlDelay(SysCtlClockGet()/300000);//10us
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0x00);
}
void distance3_trig(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0xFF);
    SysCtlDelay(SysCtlClockGet()/300000);//10us
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0x00);
}
//void distance4_trig(void)
//{
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0xFF);
//    ROM_SysCtlDelay(SysCtlClockGet()/300000);//10us
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
//}
