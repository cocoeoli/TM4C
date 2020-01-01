///*
// * key.c
// *
// *  Created on: 2019Äê1ÔÂ24ÈÕ
// *      Author: xiong
// */
//
//#include"key.h"
//
//volatile bool bKey0IntFlag = false;
//volatile bool bKey4IntFlag = false;
//
//void key_init(void)
//{
//
//   SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
//   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
//
//   HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
//   HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
//   HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
//
//   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
//   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//
//
//   GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
//
//   GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
//   GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
//
//   IntEnable(INT_GPIOF);
//   IntMasterEnable();
//
//}
//
//void key_process(void)
//{
//    if(true == bKey0IntFlag) {
//        bKey0IntFlag = false;
//
//                   // Turn on the LED1.
//                   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//                   UART_send_int16_t(1,1,UART0_BASE);
//
//                   // Delay 1s.
//                   SysCtlDelay(1000*(SysCtlClockGet()/3000));
//
//                   // Turn off the LED1.
//                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
//                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
//                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
//
//                // Clear all the pin interrupts before enable gpio-F4 interrupt again.
//                GPIOIntClear(GPIO_PORTF_BASE, GPIOIntStatus(GPIO_PORTF_BASE, false));
//                // Enable the gpio-F4 interrupt again.
//                GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
//            }
//    if(true == bKey4IntFlag) {
//        bKey4IntFlag = false;
//
//        // Turn on the LED1.
//                         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
//                         UART_send_int16_t(2,1,UART0_BASE);
//
//                         // Delay 1s.
//                         SysCtlDelay(1000*(SysCtlClockGet()/3000));
//
//                         // Turn off the LED1.
//                       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
//                       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
//                       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
//                    // Clear all the pin interrupts before enable gpio-F4 interrupt again.
//                    GPIOIntClear(GPIO_PORTF_BASE, GPIOIntStatus(GPIO_PORTF_BASE, false));
//                    // Enable the gpio-F4 interrupt again.
//                    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
//                }
//}
//
//void IntHandler_GPIOF(void)
//{
//    uint32_t ui32IntStatus;
//
//    ui32IntStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
//    GPIOIntClear(GPIO_PORTF_BASE, ui32IntStatus);
//
//    if((ui32IntStatus & GPIO_PIN_4) == GPIO_PIN_4)
//    {
//        bKey4IntFlag = true;
//        GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);
//    }
//    if((ui32IntStatus & GPIO_PIN_0) == GPIO_PIN_0)
//        {
//            bKey0IntFlag = true;
//            GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_0);
//        }
//}
//
//
