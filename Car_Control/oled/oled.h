/*
 * oled.h
 *
 *  Created on: 2016年10月17日
 *      Author: weycen
 */

#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>



/* Peripheral definitions for EK-TM4C123G board */
// I2C port
#define OLED_I2C_BASE               I2C0_BASE
#define OLED_I2C_SYSCTL_PERIPH      SYSCTL_PERIPH_I2C0

// GPIO for I2C pins
#define OLED_GPIO_PORT_BASE         GPIO_PORTB_BASE
#define OLED_GPIO_SYSCTL_PERIPH     SYSCTL_PERIPH_GPIOB
#define OLED_I2C_SCL                GPIO_PIN_2
#define OLED_I2C_SDA                GPIO_PIN_3

#define OLED_I2C_PINS               (OLED_I2C_SCL | OLED_I2C_SDA)

// GPIO pin configuer
#define OLED_GPIO_I2C_SCL           GPIO_PB2_I2C0SCL
#define OLED_GPIO_I2C_SDA           GPIO_PB3_I2C0SDA

// commands define
#define OLED_I2C_ADDR              0x3C
#define OLED_I2C_DAT               0x40
#define OLED_I2C_CMD               0x00
#define WRITE                      false
#define READ                       true
#define OLED_CMD                   1
#define OLED_DAT                   0
#define OLED_DELAY                 600





extern void DelayXms(uint16_t xms);
extern void OLED_I2CInit(void);
extern void OLED_DrawPiexl(uint8_t u8X,uint8_t u8Y,bool bFILL);
extern void OLED_FillScreen(void);
extern void LCDDrawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,bool FILL);
extern void OLED_ClearScreen();
extern void OLED_DisplayChinese(uint8_t u8X,uint8_t u8Y,uint8_t number);
extern void OLED_DisplayChar(uint8_t u8X,uint8_t u8Y,uint8_t chr);
extern void OLED_DisplayNumber(uint8_t u8X,uint8_t u8Y,double num,uint8_t dec_dig);
void OLED_Show_Init(void);
void OLED_Show(
        int16_t  OilDoor_Value,      //1,油门值, -100到100.
        uint16_t RealTime_Speed,     //2,电机转速，100到450 rpm.
        int8_t   Direction,          //3,方向,1则正转,否则反转.
        uint16_t Target_Speed_UART,  //4,通过串口设定的目标值.
        uint8_t  Duty_Motor,         //5,所测得的外部方波占空比.(00-99)
        uint16_t Distance_mm,        //6,超声波所测距离,单位mm.(0000-9999)
        uint16_t Speed_Sound
               );       //7,温度补偿后的声速,单位m/s.(000-999)

#endif /* OLED_H_ */
