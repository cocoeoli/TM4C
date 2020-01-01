#include "drivers/my_delay/delay.h"
#include "drivers/uart/uart.h"
#include "drivers/car_ctrl/car_ctrl.h"
#include "drivers/pwm/pwm_config.h"
#include "drivers/timer/timer_config.h"
#include "drivers/ultra/distance.h"
//#include "key.h"

//uint32_t t1,t2,t3,t4;
//extern float dis2, dis3;

////30ms触发一次, 340m/s*30ms = 10.2m, 10.2m/2 = 5.1m，即5.1m内不会冲突
//void Timer0_IntHandler(void)
//{
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//    static uint8_t count = 0;
//    count++;
//    switch(count)
//    {
//        case 1:
//            TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
//            distance2_trig();
//            break;
//        case 2:
//            TimerControlEvent(WTIMER0_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
//            distance3_trig();
////            break;
////        case 3:
////            TimerControlEvent(WTIMER1_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
////            distance3_trig();
////            break;
////        case 4:
////            TimerControlEvent(WTIMER1_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
////            distance4_trig();
//            count = 0;
//            break;
//    }
//}

//void WTimer0_CCP0_IntHandler(void)
//{
//    TimerIntClear(WTIMER0_BASE, TimerIntStatus(WTIMER0_BASE, true));
//    TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);
//
//    static uint32_t value[2] = {0, 0};
//    static uint8_t count = 0;
//    value[count++] = TimerValueGet(WTIMER0_BASE, TIMER_A);
//
//    if(count == 2)
//    {
//        count = 0;
//        float fperiod = value[1] > value[0] ? (value[1]-value[0]):(value[1]-value[0]+0xFFFFFFFF);
//        float temp = 85*fperiod/100000.0/2.0;
//        if(temp > 400)//超过4m认为数据错误
//            TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
//        else
//            dis2 = temp*10;
//    }
//}
//
//void WTimer0_CCP1_IntHandler(void)
//{
//    TimerIntClear(WTIMER0_BASE, TimerIntStatus(WTIMER0_BASE, true));
//    TimerControlEvent(WTIMER0_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
//
//    static uint32_t value[2] = {0, 0};
//    static uint8_t  count = 0;
//    value[count++] = TimerValueGet(WTIMER0_BASE, TIMER_B);
//
//    if(count == 2)
//    {
//        count = 0;
//        float fperiod = value[1] > value[0] ? (value[1]-value[0]):(value[1]-value[0]+0xFFFFFFFF);
//        float temp = 85*fperiod/100000.0/2.0;
//        if(temp > 400)//超过4m认为数据错误
//            TimerControlEvent(WTIMER0_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
//        else
//            dis3 = temp*10;
//    }
//}
//void WTimer1_CCP0_IntHandler(void)
//{
//    TimerIntClear(WTIMER1_BASE, TimerIntStatus(WTIMER1_BASE, true));
//    TimerControlEvent(WTIMER1_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);
//
//    static uint32_t value[2] = {0, 0};
//    static uint8_t  count = 0;
//    value[count++] = TimerValueGet(WTIMER1_BASE, TIMER_A);
//
//    if(count == 2)
//    {
//        count = 0;
//        float fperiod = value[1] > value[0] ? (value[1]-value[0]):(value[1]-value[0]+0xFFFFFFFF);
//        float temp = 85*fperiod/100000.0/2.0;
//        if(temp > 400)
//            TimerControlEvent(WTIMER1_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
//        else
//            dis3 = temp;
//    }
//}
//
//void WTimer1_CCP1_IntHandler(void)
//{
//    TimerIntClear(WTIMER1_BASE, TimerIntStatus(WTIMER1_BASE, true));
//    TimerControlEvent(WTIMER1_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
//
//    static uint32_t value[2] = {0, 0};
//    static uint8_t  count = 0;
//    value[count++] = TimerValueGet(WTIMER1_BASE, TIMER_B);
//
//    if(count == 2)
//    {
//        count = 0;
//        float fperiod = value[1] > value[0] ? (value[1]-value[0]):(value[1]-value[0]+0xFFFFFFFF);
//        float temp = 85*fperiod/100000.0/2.0;
//        if(temp > 400)
//            TimerControlEvent(WTIMER1_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
//        else
//            dis4 = temp;
//    }
//}

//void PORTF_IntHandler(void)
//{
//    uint32_t s = GPIOIntStatus(GPIO_PORTF_BASE, true);
//    GPIOIntClear(GPIO_PORTF_BASE, s);
//
//    if((s&GPIO_PIN_4) == GPIO_PIN_4)
//    {
//        while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))//等待按键松开
//            ;
//        extern bool key0_flag;
//        key0_flag = 1;
//    }
//}

//void IntHandler_UART1(void)
//{
//    UARTIntClear(UART1_BASE, UARTIntStatus(UART1_BASE, true));

//    char c;
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART1_BASE);
//    }
//}

//void IntHandler_UART2(void)
//{
//    UARTIntClear(UART2_BASE, UARTIntStatus(UART2_BASE, true));
//
//    char c;
//    while(UARTCharsAvail(UART2_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART2_BASE);
//    }
//}
//
//void IntHandler_UART3(void)
//{
//    UARTIntClear(UART3_BASE, UARTIntStatus(UART3_BASE, true));
//
//    char c = 0;
//    while(UARTCharsAvail(UART3_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART3_BASE);
//    }
//}
//
//void IntHandler_UART4(void)
//{
//    UARTIntClear(UART4_BASE, UARTIntStatus(UART4_BASE, true));
//
//    char c = 0;
//    while(UARTCharsAvail(UART4_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART4_BASE);
//
//
//    }
//}
//
//void IntHandler_UART5(void)
//{
//    UARTIntClear(UART5_BASE, UARTIntStatus(UART5_BASE, true));
//
//    char c = 0;
//    while(UARTCharsAvail(UART5_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART5_BASE);
//    }
//}
//
//void IntHandler_UART7(void)
//{
//    UARTIntClear(UART7_BASE, UARTIntStatus(UART7_BASE, true));
//    extern uint16_t block_pos;
//    extern bool camera_flag;
//    char c = 0;
//    char buf[5];
//    uint8_t i =0;
//    while(UARTCharsAvail(UART7_BASE))
//    {
//        c = UARTCharGetNonBlocking(UART7_BASE);
//        buf[i] = c;
//        i++;
//        if(i == 5)
//            break;
//    }
//    if( (buf[0] == '{') && (buf[4] == '}') ){
//        uint8_t b = (buf[1]-48);
//        uint8_t s = (buf[2]-48);
//        uint8_t g = (buf[3]-48);
//        block_pos = b*100+s*10+g;
//        block_pos = 320 - block_pos;
//    }
//    camera_flag = 1;
//}
