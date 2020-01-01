/*
 * wtimer.c
 *
 *  Created on: 2019��8��3��
 *      Author: xiong
 */
#include "wtimer.h"
#include "../ultra/distance.h"
#include "../PID/pid.h"

extern float dis3;

void wtimer2AB_init(uint16_t Amscount,   uint16_t Bmscount)
{
       SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER2)) ;

       TimerConfigure(WTIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC |TIMER_CFG_B_PERIODIC);   //ʹ������32λ��ʱ�����ڼ���ģʽ
       TimerLoadSet(WTIMER2_BASE, TIMER_A , Amscount*(SysCtlClockGet()/1000)-1);   //��������1000*mscount��λ
       TimerLoadSet(WTIMER2_BASE, TIMER_B , Bmscount*(SysCtlClockGet()/1000)-1);   //��������1000*mscount��λ
//       TimerLoadSet64(WTIMER2_BASE, mscount*(SysCtlClockGet()/1000) );    //��������1000*mscount��λ

       IntPrioritySet(INT_WTIMER2A, 0x21);
       IntPrioritySet(INT_WTIMER2B, 0x22);

       TimerIntRegister(WTIMER2_BASE, TIMER_A, WTimer2A_IntHandler);
       TimerIntRegister(WTIMER2_BASE, TIMER_B, WTimer2B_IntHandler);

       IntEnable(INT_WTIMER2A);
       IntEnable(INT_WTIMER2B);
       TimerIntEnable(WTIMER2_BASE, TIMER_TIMA_TIMEOUT);
       TimerIntEnable(WTIMER2_BASE, TIMER_TIMB_TIMEOUT);

//          TimerDisable(WTIMER2_BASE, TIMER_A);
       TimerDisable(WTIMER2_BASE, TIMER_BOTH);
}

void wtimer4_init(uint8_t  scount)
{
         SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER4);
          while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER4)) ;

          TimerConfigure(WTIMER4_BASE, TIMER_CFG_PERIODIC);   //ʹ��ȫ��64λ��ʱ�����ڼ���ģʽ
//          TimerPrescaleSet(WTIMER3_BASE, TIMER_BOTH, 8 - 1);     //Ԥ��Ƶϵ�� 8

          TimerLoadSet64(WTIMER4_BASE, scount*(SysCtlClockGet()) );   //1000000*scount��

          IntPrioritySet(INT_WTIMER4A, 0x40);
          TimerIntRegister(WTIMER4_BASE, TIMER_BOTH, WTimer4_IntHandler);

          IntEnable(INT_WTIMER4A);
//          TimerIntDisable(WTIMER3_BASE, TIMER_TIMA_TIMEOUT);
          TimerIntEnable(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);

          TimerDisable(WTIMER4_BASE, TIMER_BOTH);

}

void WTimer2A_IntHandler(void)         //100msһ��
{
            TimerIntClear(WTIMER2_BASE, TIMER_TIMA_TIMEOUT);
            position_pid( 300 , dis3);
 }

void WTimer2B_IntHandler(void)         //90msһ��
{
            TimerIntClear(WTIMER2_BASE, TIMER_TIMB_TIMEOUT);
            static uint8_t count = 0;
            count++;
            switch(count)
            {
                case 1:
                    TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
                    distance2_trig();
                    break;
                case 2:
                    TimerControlEvent(WTIMER0_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
                    distance3_trig();
        //            break;
        //        case 3:
        //            TimerControlEvent(WTIMER1_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
        //            distance3_trig();
        //            break;
        //        case 4:
        //            TimerControlEvent(WTIMER1_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
        //            distance4_trig();
                    count = 0;
                    break;
            }
 }

void WTimer4_IntHandler(void)         //sһ��
{
            TimerIntClear(WTIMER3_BASE, TIMER_TIMA_TIMEOUT);
 }



