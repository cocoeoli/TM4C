//#include "timer.h"
//
//
//extern uint16_t count;
//uint8_t flag;
//uint8_t duty=0;
//uint16_t num=0;
//float fVoltage0 = 0;
//
//// Configure the wtimer0B as a capture IO.
//void Timer0_init(void)      //用于控制超声波
//{
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//
//    GPIOPinConfigure(GPIO_PB7_T0CCP1);
//    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_7);
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_B_PERIODIC_UP|TIMER_CFG_SPLIT_PAIR );  //16bit
//
//    TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet()/20000);   //0.05ms
//    IntMasterEnable();
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
//    IntEnable(INT_TIMER0B);
//    IntPrioritySet(INT_TIMER0B, 0x0);
// //   TimerEnable(TIMER0_BASE,TIMER_B);
//
//}
//
//void Timer2_init(void)      //用于控制超声波
//{
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
//
//    GPIOPinConfigure(GPIO_PB1_T2CCP1);
//    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_1);
//    TimerConfigure(TIMER2_BASE, TIMER_CFG_B_PERIODIC_UP|TIMER_CFG_SPLIT_PAIR );  //16bit
//
//    TimerLoadSet(TIMER2_BASE, TIMER_B, SysCtlClockGet()/2000);   //0.5ms
//    IntMasterEnable();
//    TimerIntEnable(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
//    IntEnable(INT_TIMER2B);
//    IntPrioritySet(INT_TIMER2B, 0x0);
//    TimerEnable(TIMER2_BASE,TIMER_B);
//
//}
//
//void WTimer0_init(void)              //pc5 TIMER中断，用于控制电机转速
//{
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//
//    GPIOPinConfigure(GPIO_PC5_WT0CCP1);
//    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_5);
//    TimerConfigure(WTIMER0_BASE, TIMER_CFG_B_PERIODIC_UP|TIMER_CFG_SPLIT_PAIR );  //32bit
//
//    TimerLoadSet(WTIMER0_BASE, TIMER_B, SysCtlClockGet()/2000);   //0.5ms
//    IntMasterEnable();
//    TimerIntEnable(WTIMER0_BASE, TIMER_TIMB_TIMEOUT);
//    IntEnable(INT_WTIMER0B);
//    IntPrioritySet(INT_WTIMER0B, 0x5);
//  //  TimerEnable(WTIMER0_BASE,TIMER_B);
//}
//
//void HarfTimerBvalue_clear(uint32_t ui32Base, uint32_t ui32Timer)   // ex: (TIMER0_BASE, TIMER_B)
//{
//    TimerConfigure(ui32Base, TIMER_CFG_B_ONE_SHOT_UP|TIMER_CFG_SPLIT_PAIR );  //one per time
//    TimerEnable(ui32Base, ui32Timer);
//    TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet()/2000);   //1ms
//    ROM_SysCtlDelay((10*SysCtlClockGet()/3000));  //5ms
//    TimerDisable(ui32Base, ui32Timer);
//    TimerConfigure(ui32Base, TIMER_CFG_B_PERIODIC_UP|TIMER_CFG_SPLIT_PAIR );
//    TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet()/20000);
//}
//
//void Timer0BIntHandler(void)
//{
//
//    // Clear the TIMER_CAPB_EVENT interrupt status.
//    TimerIntClear(TIMER0_BASE, TimerIntStatus(TIMER0_BASE, true));
//    count++;
////    num++;
//
//         //   if(num == 100)    //100ms进入一次
//       //      {
//     //           app_ultrasonic_mode();
//    //             // Configure the ads1118 use input0, and read the voltage
//    //            // from the ads1118 input0.
//    //            ADS1118_Configure(ADS1118_CONFIG_0);
//    //            SysCtlDelay(10*(SysCtlClockGet()/3000));
//    //            ADS1118_DataGetFloat(&fVoltage0);
//    //
//    //            Search_thro((int)fVoltage0);
//    //            // Print the voltage0 and voltage1.
//    //            UARTprintf("ch0:%4umv \n",(uint32_t)fVoltage0);
//        //         num = 0;
////
////              }
////    num++;
////    if(num == 1000){
////        app_ultrasonic_mode();
////        compan();
////        num = 0;
////    }
//}
//
//void Timer2BIntHandler(void)
//{
//
//    // Clear the TIMER_CAPB_EVENT interrupt status.
//    TimerIntClear(TIMER2_BASE, TimerIntStatus(TIMER2_BASE, true));
//    num++;
//    if(num==4000)
//        num = 0;
//    if(flag == 0){
//        if(num % 20 == 0 ){
//                duty++;
//                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*duty) / 100 );
//                if(duty == 100)
//                    flag = 1;
//            }
//    }
//    else{
//        if(num % 20 == 0){
//                duty--;
//                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*duty) / 100 );
//                if(duty == 1)
//                    flag = 0;
//                }
//    }
////    num++;
//
//         //   if(num == 100)    //100ms进入一次
//       //      {
//     //           app_ultrasonic_mode();
//    //             // Configure the ads1118 use input0, and read the voltage
//    //            // from the ads1118 input0.
//    //            ADS1118_Configure(ADS1118_CONFIG_0);
//    //            SysCtlDelay(10*(SysCtlClockGet()/3000));
//    //            ADS1118_DataGetFloat(&fVoltage0);
//    //
//    //            Search_thro((int)fVoltage0);
//    //            // Print the voltage0 and voltage1.
//    //            UARTprintf("ch0:%4umv \n",(uint32_t)fVoltage0);
//        //         num = 0;
////
////              }
////    num++;
////    if(num == 1000){
////        app_ultrasonic_mode();
////        compan();
////        num = 0;
////    }
//}
//
//void WTimer0BIntHandler(void)
//{
//    TimerIntClear(WTIMER0_BASE, TimerIntStatus(WTIMER0_BASE, true));
//    num++;
//        if(num == 2000)    //100ms进入一次
//         {
////             // Configure the ads1118 use input0, and read the voltage
////            // from the ads1118 input0.
////            ADS1118_Configure(ADS1118_CONFIG_0);
////            SysCtlDelay(10*(SysCtlClockGet()/3000));
////            ADS1118_DataGetFloat(&fVoltage0);
////
////            Search_thro((int)fVoltage0);
////            // Print the voltage0 and voltage1.
////            UARTprintf("ch0:%4umv \n",(uint32_t)fVoltage0);
//             num = 0;
//
//          }
//    // Clear the TIMER_CAPB_EVENT interrupt status.
//
//
//}
