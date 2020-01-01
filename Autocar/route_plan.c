///*
// * route_plan.c
// *
// *  Created on: 2019年7月11日
// *      Author: xiong
// */
//#include "stdio.h"
//#include "drivers/car_ctrl/car_ctrl.h"
//#include "drivers/my_delay/delay.h"
//#include "drivers/mpu6050/mpu6050.h"
//#include "drivers/mpu6050/inv_mpu.h"
//#include "drivers/mpu6050/inv_mpu_dmp_motion_driver.h"
//#include "drivers/PID/pid.h"
//#include "drivers/uart/uart.h"
//#include "route_plan.h"
//
//extern uint8_t Pose;
//extern float  dis2, dis3;
//extern float set_yaw;
//
//float YAW = 0;
//
//void in_station1_4(void)
//{
//    while(dis2 > 100)
//    {
//        Pose = 0x01;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task1--4\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//}
//
//void in_station5_6(void)
//{
//     set_yaw = -90;                   //右转90°
//     while(YAW > -88  || YAW < -92)
//     {
//         mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//         check_yaw(YAW);             //检查是否需要角度pid调节
//         chuankou_put();             //打印
//         UART_send_string("task1--5\x0d\x0a", UART1_BASE);
//     }
//     car_stop();
//     delay_ms(400);
//     while(dis3 > 100.0)
//     {
//         Pose = 0x08;
//         mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//         check_yaw(YAW);
//         chuankou_put();             //打印
//         UART_send_string("task1--6\x0d\x0a", UART1_BASE);
//     }
//     Pose = 0;
//     car_stop();
//}
//
//void task_1(float x,float y)   //入库
//{
//    while(dis2  >  x)
//    {
//        Pose = 0x01;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task1--1\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    //是否需要pid
//    delay_ms(400);
//    while(dis3 <  y)
//    {
//        Pose = 0x04;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);
//        chuankou_put();             //打印
//        UART_send_string("task1--2\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    delay_ms(400);
//    if(gar_num == 5 || gar_num == 6)
//    {
//        in_station5_6();
//    }
//    else if(gar_num == 4)
//    {
//        while(dis3 >  75)
//            {
//                Pose = 0x08;
//                mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//                check_yaw(YAW);
//                chuankou_put();             //打印
//                UART_send_string("task1--3\x0d\x0a", UART1_BASE);
//            }
//        Pose = 0;
//        car_stop();
//        delay_ms(400);
//        in_station1_4();
//    }
//    else
//    {
//        in_station1_4();
//    }
//}
//
//
//
//void out_station1_4(float x,float y)
//{
//    while(dis2 < y)
//    {
//        Pose = 0x02;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task2--1\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    delay_ms(400);
//    while(dis3 > x)
//    {
//        Pose = 0x08;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task2--2\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    delay_ms(400);
//}
//
//void out_station5_6(float x,float y)
//{
//    while(dis3 < 330)
//    {
//        Pose = 0x04;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task2--3\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    delay_ms(400);
//
//    set_yaw = 0;                    //转回垂直角度
//     while(YAW < -2 || YAW > 2 )
//     {
//         mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//         check_yaw(YAW);             //检查是否需要角度pid调节
//         chuankou_put();             //打印
//         UART_send_string("task2--4\x0d\x0a", UART1_BASE);
//     }
// //    set_yaw = 0;
//     car_stop();
//     delay_ms(400);
//    while(dis3 > x)
//    {
//        Pose = 0x08;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task2--5\x0d\x0a", UART1_BASE);
//    }
//    Pose = 0;
//    car_stop();
//    delay_ms(400);
//}
//
//void task_2(float x,float y)   // 出库
//{
//    if(gar_num == 5 || gar_num == 6)
//    {
////        pid_flag = 1;
//        out_station5_6(x,y);
//    }
//    else{
//        out_station1_4(x,y);
//    }
//    while(dis2 < 1400)
//    {
//        Pose = 0x02;
//        mpu_dmp_get_data(&YAW);     //50ms计算时间，尽量不被中断影响
//        check_yaw(YAW);             //检查是否需要角度pid调节
//        chuankou_put();             //打印
//        UART_send_string("task2--6\x0d\x0a", UART1_BASE);
////        car_go_back();
//    }
//    Pose = 0;
//    car_stop();
//
//}
//
//void chuankou_put()
//{
//    char yaw_str[30];
//    sprintf(yaw_str, "n0.val=%d\xff\xff\xff", (int)dis2);
//    UART_send_string(yaw_str, UART5_BASE);
//    sprintf(yaw_str, "n1.val=%d\xff\xff\xff", (int)dis3);
//    UART_send_string(yaw_str, UART5_BASE);
//    sprintf(yaw_str, "n2.val=%d\xff\xff\xff", (int)YAW);
//    UART_send_string(yaw_str, UART5_BASE);
//}
//
