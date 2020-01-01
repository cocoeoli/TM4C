#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "driverlib/rom_map.h"
#include "uartstdio.h"
#include "drivers/my_delay/delay.h"
#include "drivers/uart/uart.h"
#include "drivers/mpu6050/mpu6050.h"
#include "drivers/mpu6050/inv_mpu.h"
#include "drivers/mpu6050/inv_mpu_dmp_motion_driver.h"
#include "drivers/PID/pid.h"
#include "drivers/car_ctrl/car_ctrl.h"
#include "drivers/pwm/pwm_config.h"
#include "drivers/timer/timer_config.h"
#include "drivers/timer/wtimer.h"
#include "drivers/ultra/distance.h"
////////////////中断优先级
//    UART0        0x01
//    UART1        0x02
//    UART2        0x05
//    UART5        0x08
//////////////////////
void INT_pri(void);           //所有中断优先级设置
void PS2_choice(void);        //遥控模式选择

uint8_t Pose=0;
uint8_t PS2_flag = 0;
uint8_t uart_flag;                 //8位代表8个uart中断  00000001--uart0
float set_yaw = 0;                     //设置角度
float dis2=550, dis3=10;                      //距离
extern char uart1_buff[Buff1_Len];

void main(void)
 {
//    uint8_t icount1=0, icount2=0;
    float yaw=0;
    char str[30];
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);      //200/2.5=40M
    FPULazyStackingEnable();
    FPUEnable();
//    wtimer2AB_init(20,  90);   //宽位定时器ms为单位
    distance_measure_init();
    car_ctrl_init();
    PID_Init();
//    UART0_init(115200);       //openMv
    UART1_Init(115200);       //两个板卡通信
//    UART2_Init(9600);                //PS2手柄遥控
//    UART5_Init(115200);            //显示串口屏

//    while(mpu_dmp_init()){   //初始化mpu6050
//        UART_send_string(" mpu error",  UART1_BASE);
//        delay_ms(10);
//    }
//    INT_pri();
    delay_s(1);

    car_go_forward();
    while(1)
    {
        delay_s(5);
        car_go_left();
        delay_s(5);
        car_go_forward();
        if(uart_flag != 0){
                if(uart_flag&0x01){         //uart0中断
//                    if(uart0_buff[1] == 'A')
//                          str_float();
//                    Datapro();
                    uart_flag = 0;
                }
                if(uart_flag&0x02){
                    if(uart1_buff[1] == 'A')
                       str_float();
//                    Datapro();
                    uart_flag = 0;
                }
                if(uart_flag&0x04){
                    PS2_Data_pro();
                    uart_flag = 0;
                }
                if(uart_flag&0x10){        //uart5
                    uart_flag = 0;
                }
         }
        if(dis3 < 1000){
            sprintf(str, "A300\r\nB%d\r\n", (short)dis3);
            UART_send_string(str,  UART1_BASE);
            delay_ms(5);
        }
          mpu_dmp_get_data(&yaw);
          check_yaw(yaw);
//          UARTprintf("dis2 %d mm  dis3 %d mm\n", (short)dis2,   (short)dis3);
//          delay_ms(100);
//        PS2_choice();
    }
}

void INT_pri(void)
{
    TimerEnable(WTIMER2_BASE, TIMER_BOTH);         //打开宽位定时器
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntEnable(WTIMER0_BASE, TIMER_CAPA_EVENT);
    TimerIntEnable(WTIMER0_BASE, TIMER_CAPB_EVENT);
    IntMasterEnable();
}

float yaw=0;
void PS2_choice(void)
{
    switch(PS2_flag)
    {
        case 0:
        {
            car_stop();
            mpu_dmp_get_data(&yaw);
            set_yaw = yaw;
                break;
        }
        case 1:
        {
            Pose = 0x01;
            mpu_dmp_get_data(&yaw);
            check_yaw(yaw);
            break;
        }
        case 2:
        {
            Pose = 0x02;
            mpu_dmp_get_data(&yaw);
            check_yaw(yaw);
            break;
        }
        case 3:
        {
            Pose = 0x04;
            mpu_dmp_get_data(&yaw);
            check_yaw(yaw);
            break;
        }
        case 4:
        {
            Pose = 0x08;
            mpu_dmp_get_data(&yaw);
            check_yaw(yaw);
            break;
        }
        case 5:
        {
            car_turn_left(40);
            break;
        }
        case 6:
        {
            car_turn_right(40);
            break;
        }
    }
}

