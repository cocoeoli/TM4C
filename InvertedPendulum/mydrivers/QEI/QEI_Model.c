///*
// * QEI_Model.c
// *
// *  Created on: 2018年1月29日
// *      Author: Loser
// */
//
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/tm4c123gh6pm.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/qei.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_gpio.h"
//#include "driverlib/interrupt.h"
//#include "inc/hw_types.h"
//#include "QEI_Model.h"
//
//// * note
//// *电机: 8r/s 13线 减速比 1:20
//// *一圈编码器输出390个脉冲
//// *390x4 = 1560
//#define MOTOR_QEI_VEL_FREQ      10
//
//bool Init_flag = true;
//
////void QEI_InitConfig(user_qei_data_t *qei_data);
//void QEI_Config(void);
//
//user_qei_data_t qei_data_array[2] =
//{
//        {        //QEI0: D6,D7
//                .periph = SYSCTL_PERIPH_QEI0,
//                .base = QEI0_BASE,
//                .swap_flag = QEI_CONFIG_SWAP,
//                .Qinterrupt = INT_QEI0,
//
//                .gpio_periph = SYSCTL_PERIPH_GPIOD,
//                .gpio_port = GPIO_PORTD_BASE,
//                .gpio_pin = (GPIO_PIN_6 | GPIO_PIN_7),
//                .gpio_cfg_a = GPIO_PD6_PHA0,
//                .gpio_cfg_b = GPIO_PD7_PHB0,
//
//                .dir = 1,         //方向
//                .velocity = 0,    //速率
//                .Init_Pos = 0,    //初始位置
//                .Now_Pos = 0,     //位置
//        },
//
//        {       //QEI1：C5,C6
//                .periph = SYSCTL_PERIPH_QEI1,
//                .base = QEI1_BASE,
//                .swap_flag = QEI_CONFIG_NO_SWAP,
//                .Qinterrupt = INT_QEI1,
//
//                .gpio_periph = SYSCTL_PERIPH_GPIOC,
//                .gpio_port = GPIO_PORTC_BASE,
//                .gpio_pin = (GPIO_PIN_5 | GPIO_PIN_6),
//                .gpio_cfg_a = GPIO_PC5_PHA1,
//                .gpio_cfg_b = GPIO_PC6_PHB1,
//
//                .dir = 1,
//                .velocity = 0,
//                .Init_Pos = 0,
//                .Now_Pos = 0,
//        },
//};
//
//
//void QEI_InitConfig(user_qei_data_t *qei_data)
//{
//    //
//    // Enable the QEI0 peripheral
//    //
//    SysCtlPeripheralEnable(qei_data->periph);
//    //
//    // Wait for the QEI0 module to be ready.
//    //
//    while(!SysCtlPeripheralReady(qei_data->periph));
//    //
//    // Configure gpio
//    //
//    SysCtlPeripheralEnable(qei_data->gpio_periph);
//    while(!SysCtlPeripheralReady(qei_data->gpio_periph));
//
//    if(qei_data->gpio_port == GPIO_PORTD_BASE && (qei_data->gpio_pin & GPIO_PIN_7))
//    {
//        //
//        // unlock PF0
//        //
//        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x4C4F434B;
//        HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
//        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x00;
//    }
//
//    GPIOPinConfigure(qei_data->gpio_cfg_a);
//    GPIOPinConfigure(qei_data->gpio_cfg_b);
//
//    GPIOPinTypeQEI(qei_data->gpio_port, qei_data->gpio_pin);
//
//    //
//    // Configure the quadrature encoder to capture edges on both signals and
//    // maintain an absolute position by resetting on index pulses. Using a
//    // 1000 line encoder at four edges per line, there are 4000 pulses per
//    // revolution; therefore set the maximum position to 3999 as the count
//    // is zero based.
//    //1560 -> 0x618
//    QEIConfigure(qei_data->base, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | qei_data->swap_flag), 0x618);
//    //
//    // Enable the quadrature encoder.
//    //
//    QEIEnable(qei_data->base);
//    //
//    // Configure qei velocity 周转率
//    //
//    QEIVelocityConfigure(qei_data->base, QEI_VELDIV_1, SysCtlClockGet() / MOTOR_QEI_VEL_FREQ);
//    QEIVelocityEnable(qei_data->base);
//
//    QEIIntEnable(qei_data->base, QEI_INTDIR | QEI_INTTIMER);
//    IntRegister(INT_QEI0,QEI0_IRQHandler);
//    IntEnable(qei_data->Qinterrupt);
//    //INT_QEI0
// //   IntRegister(INT_QEI0,QEI0_IRQHandler);
//}
//
//
//void QEI_Config(void)
//{
////  uint32_t i;
////  for(i = 0; i < sizeof(qei_data_array) / sizeof(qei_data_array[0]); i++)  //QEI1配置
////    {
////      QEI_InitConfig(qei_data_array + i);
////      SysCtlDelay(SysCtlClockGet()*10/3000);
////    }
//   QEI_InitConfig(qei_data_array+0);        //只配置QEI 0
//   SysCtlDelay(SysCtlClockGet()*5/3000);    //延时一段时间
//}
//
////位置信息的读取 0~1040 ==转一圈有1040个脉冲 ==每个脉冲0.3462°
////速度信息的读取            ==脉冲数/秒
//void qei_irq_handler(int32_t QEInum)
//{
//    uint32_t status = QEIIntStatus(qei_data_array[QEInum].base, true);
//    QEIIntClear(qei_data_array[QEInum].base, status);
//
//    if(status & QEI_INTTIMER)
//    {
//        qei_data_array[QEInum].velocity = QEIVelocityGet(qei_data_array[QEInum].base) * MOTOR_QEI_VEL_FREQ * QEIDirectionGet(qei_data_array[QEInum].base);
//        //qei_data_array[QEInum].Now_Pos = QEIPositionGet(qei_data_array[QEInum].base);
//    }
//
//    if(status & QEI_INTDIR)
//    {
//        qei_data_array[QEInum].dir = -qei_data_array[QEInum].dir;
//    }
//    //初始位置
//    if(Init_flag)
//    {
//        qei_data_array[QEInum].Init_Pos = QEIPositionGet(qei_data_array[QEInum].base);
//        Init_flag = false;
//    }
//    //UARTprintf("进入了中断 \n");
//    //读取位置和速度信息
////    qei_data_array[QEInum].Now_Pos = QEIPositionGet(qei_data_array[QEInum].base);
////    qei_data_array[QEInum].velocity = QEIVelocityGet(qei_data_array[QEInum].base) * MOTOR_QEI_VEL_FREQ * QEIDirectionGet(qei_data_array[QEInum].base);
//}
//
//
//void QEI0_IRQHandler(void)
//{
//    qei_irq_handler(0);
//}
//
////void QEI1_IRQHandler(void)
////{
////    qei_irq_handler(1);
////}
//
//
//int read_QEI(void)          //读取 qei 脉冲值
//{
//        int qei_value;
//
//        QEIIntDisable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
//
//        //     SysCtlDelay((SysCtlClockGet()/3000));    //1ms一次
//            //读取数值，有正负
//
//        //   UARTprintf("位置值： %d \n", position_value);  //打印角速度
//        //
//        //      if(i++ > 10){
//        //          UARTprintf("脉冲为： %d plus \n", position_value);  //打印角速度
//        //          i = 0;
//        //      }
//
//        //  QEIIntEnable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
//        //          if(qei_data_array[0].velocity>0)
//        //          {
//        //
//        //              QEI_Augledata.Angel_Velocity = (int)((qei_data_array[0].velocity/1560.0)*60); //x°/s
//        //          }
//        //          else
//        //          {
//        //              QEI_Augledata.Angel_Velocity = (int)((qei_data_array[0].velocity/1560.0)*60); //x°/s
//        //          }
//        qei_value = qei_data_array[0].velocity;
//        //          UARTprintf("Init_Pos %d",qei_data_array[0].Init_Pos);                  //最初的位置
//        //          UARTprintf("   Now_AugPos %d",QEI_Augledata.Angel_Pos);                 //当前角度位置
//        //          UARTprintf("转速为： %6d rpm\n",QEI_Augledata.Angel_Velocity);  //角速度
//        //
//        QEIIntEnable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
//
//        return qei_value;
//
//}
