/*
 * oled.c
 *
 *  Created on: 2016年10月17日
 *      Author: weycen
 */
////OLED的显存
////存放格式如下.
////[0]0 1 2 3 ... 127
//      .
//      .
//      .
//      .
//      .
//      .
//      .
//      .
////[1]0 1 2 3 ... 127
////[2]0 1 2 3 ... 127
////[3]0 1 2 3 ... 127
////[4]0 1 2 3 ... 127
////[5]0 1 2 3 ... 127
////[6]0 1 2 3 ... 127
////[7]0 1 2 3 ... 127

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "oled.h"
#include "oled_font.h"



/***********************************/
void OLED_Configuer(void);
void OLED_SetPosition(uint8_t u8X , uint8_t u8Y);
void OLED_I2CSendByte(uint8_t CMD_or_DAT, uint8_t Byte);
void OLED_FillScreen(void);

/************************************/



/***************************************************
 *    延时 s函数
 * ***********************************************/

void DelayXs(uint16_t xs)
{
    SysCtlDelay(xs*(SysCtlClockGet() / 3));
}

/***************************************************
 *    延时 ms函数
 * ***********************************************/

void DelayXms(uint16_t xms)
{
    SysCtlDelay(xms*(SysCtlClockGet() / 3000));
}

/***************************************************
 *    延时 us函数
 * ***********************************************/

void DelayXus(uint16_t xus)
{
    SysCtlDelay(xus*(SysCtlClockGet() / 3000000));
}

//****************************************
//
//  init oled I2C
//
//****************************************
void OLED_I2CInit(void)
{
    //
    SysCtlPeripheralEnable(OLED_GPIO_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(OLED_I2C_SYSCTL_PERIPH);

    //
    GPIOPinTypeI2CSCL(OLED_GPIO_PORT_BASE, OLED_I2C_SCL);
    GPIOPinTypeI2C(OLED_GPIO_PORT_BASE, OLED_I2C_SDA);

    //
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    //
    I2CMasterInitExpClk(OLED_I2C_BASE, SysCtlClockGet(), true);

    //
    OLED_Configuer();
}

//
//  oled初始设置
//
void OLED_Configuer(void)
{
    /* display off */
    OLED_I2CSendByte(OLED_CMD,0xAE);

    /* set lower column address */
    OLED_I2CSendByte(OLED_CMD,0x00);

    /* set higher column address */
    OLED_I2CSendByte(OLED_CMD,0x10);

    /* set display start line */
    OLED_I2CSendByte(OLED_CMD,0x40);

    /* set page address */
    OLED_I2CSendByte(OLED_CMD,0xB0);

    /* contract control  */
    OLED_I2CSendByte(OLED_CMD,0x81);
    OLED_I2CSendByte(OLED_CMD,0x66);

    /* set segment remap */
    OLED_I2CSendByte(OLED_CMD,0xA1);

    /* normal / reverse */
    OLED_I2CSendByte(OLED_CMD,0xA6);

    /* multiplex ratio */
    OLED_I2CSendByte(OLED_CMD,0xA8);

    /* duty = 1/64 */
    OLED_I2CSendByte(OLED_CMD,0x3F);

    /* Com scan direction */
    OLED_I2CSendByte(OLED_CMD,0xC8);/* c3*/

    /* set display offset */
    OLED_I2CSendByte(OLED_CMD,0xD3);
    OLED_I2CSendByte(OLED_CMD,0x00);

    /* set osc division */
    OLED_I2CSendByte(OLED_CMD,0xD5);
    OLED_I2CSendByte(OLED_CMD,0x80);

    /* set area color mode off */
    OLED_I2CSendByte(OLED_CMD,0xD8);
    OLED_I2CSendByte(OLED_CMD,0x05);

    /* set pre-charge period */
    OLED_I2CSendByte(OLED_CMD,0xD9);
    OLED_I2CSendByte(OLED_CMD,0xF1);

    /* set COM pins */
    OLED_I2CSendByte(OLED_CMD,0xDA);
    OLED_I2CSendByte(OLED_CMD,0x12);

    /* set vcomh */
    OLED_I2CSendByte(OLED_CMD,0xDB);
    OLED_I2CSendByte(OLED_CMD,0x30);

    /* set charge pump disable */
    OLED_I2CSendByte(OLED_CMD,0x8D);
    OLED_I2CSendByte(OLED_CMD,0x14);

    /* display on*/
    OLED_I2CSendByte(OLED_CMD,0xAF);
}


//
// I2C发送一个字节
//
void OLED_I2CSendByte(uint8_t CMD_or_DAT,uint8_t Byte)
{
    uint8_t i2cWriteBuffer;

    // frame 1:  send slave_addr + R/W   0011 1100
    I2CMasterSlaveAddrSet(OLED_I2C_BASE, OLED_I2C_ADDR, false);

    // frame 2:
    I2CMasterControl(OLED_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //
    i2cWriteBuffer = (CMD_or_DAT == OLED_CMD) ? OLED_I2C_CMD : OLED_I2C_DAT;

    // frame 3:
    I2CMasterDataPut(OLED_I2C_BASE, i2cWriteBuffer);
    I2CMasterControl(OLED_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

    // wait for master free
    while(I2CMasterBusy(OLED_I2C_BASE))
        ;

    // frame 4:
    i2cWriteBuffer = Byte;

    I2CMasterDataPut(OLED_I2C_BASE, i2cWriteBuffer);

    // wait for master free
    while(I2CMasterBusy(OLED_I2C_BASE))
        ;

    I2CMasterControl(OLED_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

    // wait for master free
    while(I2CMasterBusy(OLED_I2C_BASE))
        ;
}

//
//  在指定位置打点函数
// bFILL: true 填充 ，false 清除
void OLED_DrawPiexl(uint8_t u8X,uint8_t u8Y,bool bFILL)
{
    uint8_t temp;

    // 限幅
    u8X = u8X > 127 ? 127 : u8X;
    u8Y = u8Y > 63 ? 63 : u8Y;

    if( bFILL )
        temp = 0x01 << ( u8Y % 8 );
    else
        temp = ~ ( 0x01 << ( u8Y % 8 ) );

    // 设置目标点page
    OLED_SetPosition(u8X,u8Y);

    // 发送目标点数据
    OLED_I2CSendByte(OLED_DAT,temp);
}

//
// 设置坐标位置  x:0-127, y:0-63
//
void OLED_SetPosition( uint8_t u8X , uint8_t u8Y )
{
    OLED_I2CSendByte( OLED_CMD , 0xB0 + u8Y / 8 ); // y page
    OLED_I2CSendByte( OLED_CMD , ( ( u8X & 0xF0 ) >> 4 ) | 0x10 ); // x轴
    OLED_I2CSendByte( OLED_CMD , ( u8X & 0x0F ) );
}
//void OLED_SetPosition( uint8_t u8X , uint8_t u8Y )
//{
//    OLED_I2CSendByte( OLED_CMD , 0xB0 + u8Y); // y page
//    OLED_I2CSendByte( OLED_CMD , ( ( u8X & 0xF0 ) >> 4 ) | 0x10 ); // x轴
//    OLED_I2CSendByte( OLED_CMD , ( u8X & 0x0F ) );
//}

//
// 打开显示
//
void OLED_DisplayOn(void)
{
    OLED_I2CSendByte(OLED_CMD,0X8D);  //SET DCDC命令
    OLED_I2CSendByte(OLED_CMD,0X14);  //DCDC ON
    OLED_I2CSendByte(OLED_CMD,0XAF);  //DISPLAY ON
}

//
// 关闭显示
//
void OLED_DisplayOff(void)
{
    OLED_I2CSendByte(OLED_CMD,0X8D);  //SET DCDC命令
    OLED_I2CSendByte(OLED_CMD,0X10);  //DCDC off
    OLED_I2CSendByte(OLED_CMD,0XAE);  //DISPLAY off
}

//
// 清屏函数
//
void OLED_ClearScreen(void)
{
//    uint8_t x,y;
//    for(x=0;x<128;x++) // 128列
//    {
//        for(y=0;y<8;y++)
//        {
//            OLED_SetPosition(x,y*8); // 8页
//            OLED_I2CSendByte(OLED_DAT,0x00);  //每页竖着8位均写0
//        }
//    }

        uint8_t i,n;
        for(i=0;i<8;i++)
        {
            OLED_I2CSendByte(OLED_CMD,0xB0 + i);
            OLED_I2CSendByte(OLED_CMD,0x00);
            OLED_I2CSendByte(OLED_CMD,0x10);
            for(n=0;n<128;n++)
                OLED_I2CSendByte(OLED_DAT,0x0);
        } //更新显示
}

//
// oled写满屏
//
void OLED_FillScreen(void)
{
//    uint8_t x,y;
//    for(x=0;x<128;x++) // 128列
//    {
//        for(y=0;y<8;y++)
//        {
//            OLED_SetPosition(x,y*8); // 8页
//            OLED_I2CSendByte(OLED_DAT,0xFF);  //每页竖着8位均写0
//        }
//    }

    uint8_t i,n;
    for(i=0;i<8;i++)
    {
        OLED_I2CSendByte(OLED_CMD,0xB0 + i);
        OLED_I2CSendByte(OLED_CMD,0x00);
        OLED_I2CSendByte(OLED_CMD,0x10);
        for(n=0;n<128;n++)
            OLED_I2CSendByte(OLED_DAT,0xAA);
    } //更新显示

}

/*************************************************************
函数名：  LCDDrawLine
函数说明：使用Bresenham法,画任意两点间的直线
传入参数：(x0,y0),竖直线的起点;(x1,y1)竖直线的终点 color=1,点亮；color=0,擦除
传出参数：无
返回值：  无
************************************************************/
void LCDDrawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,bool FILL)
{

    int32_t   dx;       // 直线x轴差值变量
    int32_t   dy;        // 直线y轴差值变量
    int32_t   dx_sym;   // x轴增长方向，为-1时减值方向，为1时增值方向
    int32_t   dy_sym;   // y轴增长方向，为-1时减值方向，为1时增值方向
    int32_t   dx_2;     // dx*2值变量，用于加快运算速度
    int32_t   dy_2;     // dy*2值变量，用于加快运算速度
    int32_t   di;       // 决策变量
    dx = x1-x0;     // 求取两点之间的差值
    dy = y1-y0;
    if(dx<0)
        dx_sym=-1;
    else{
        if(dx>0)
            dx_sym=1;
    }
    if(dy>0)
        dy_sym=1;
    else{
        if(dy<0)
            dy_sym=-1;
    }
    dx=dx_sym*dx;
    dy=dy_sym*dy;
    dx_2=dx*2;
    dy_2=dy*2;
    if(dx>=dy)
    {
        di=dy_2-dx;
        while(x0!=x1)
        {
            OLED_DrawPiexl(x0,y0,FILL);
            x0+=dx_sym;
            if(di<0)
                di+=dy_2;
            else{
                di+=dy_2-dx_2;
                y0+=dy_sym;
            }
        }
        OLED_DrawPiexl(x0,y0,FILL);
    }else{
        di=dx_2-dy;
        while(y0!=y1)
        {
            OLED_DrawPiexl(x0,y0,FILL);
            y0+=dy_sym;
            if(di<0)
                di+=dx_2;
            else{
                di+=dx_2-dy_2;
                x0+=dx_sym;
            }
        }
        OLED_DrawPiexl(x0,y0,FILL);
    }
}


//
//显示汉字
//
void OLED_DisplayChinese(uint8_t u8X,uint8_t u8Y,uint8_t number)
{
    uint8_t i/*adder=0*/;
    uint8_t temp;

    temp = 2 * number;
    OLED_SetPosition(u8X,u8Y); // 起始点，即页
    for( i = 0; i < 16; i++ )
    {
        OLED_I2CSendByte( OLED_DAT, FONT_16_16[ temp ][ i ] );
        //OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
        //adder + = 1;
     }

    OLED_SetPosition( u8X, u8Y + 8 ); // 移到下一页
    for( i = 0; i < 16; i++ )
    {
        OLED_I2CSendByte( OLED_DAT, FONT_16_16[ temp + 1 ][ i ] );
        //OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
        //adder+=1;
    }
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_DisplayChar(uint8_t u8X,uint8_t u8Y,uint8_t chr)
{
    uint8_t i=0 , c=0;
    uint16_t temp ;

    c = chr-' ';//得到偏移后的值 asic码值
    temp = c*16;
//    if(Char_Size ==16)
//    {
        OLED_SetPosition(u8X,u8Y);
        for(i=0;i<8;i++)
            OLED_I2CSendByte(OLED_DAT,FONT_8_16[temp+i]);
        OLED_SetPosition(u8X,u8Y+8);
        for(i=0;i<8;i++)
            OLED_I2CSendByte(OLED_DAT,FONT_8_16[temp+i+8]);
//    }
//     else {
//         OLED_SetPosition(u8X,u8Y);
//        for(i=0;i<6;i++)
//            OLED_I2CSendByte(OLED_DAT,FONT_8_16[c][i]);
//        }
}

/**************************************************
*名称：void disp_num(double num,uchar dec_dig)
*功能:显示任意实数，并可设定保留小数位数，且有四舍五入功能
*入口参数：num :要显示的数 , dec_dig :保留小数位
**************************************************/
void OLED_DisplayNumber(uint8_t u8X,uint8_t u8Y,double num,uint8_t dec_dig)
{
    //uint32_t a;
    int num_int,num_dec_int,m=0,k=0,j;
    double num_dec;
    uint8_t xtemp,ytemp;
    xtemp =u8X;
    ytemp =u8Y;

    uint8_t integ[ 10 ],decim[ 10 ];
    num_int = ( int )( num + 5 * pow( 10,-( dec_dig + 1 ) ) );/* a= 1234 */
    num_dec = num - num_int; /* b= 0.5678 */

    for( j = num_int; j > 0; j = j / 10 )
    {
        integ[k++]=j % 10; /* 整数位分解 */
    }

    num_dec_int = ( int )( num_dec * pow( 10 , dec_dig ) );  /* 小数位变整数 */

    for(j=num_dec_int;j>0;j=j/10)
    {
        decim[m++]=j%10; /* 小数位分解 */
    }

    /* 显示整数位 */
    for(j=k-1;j>=0;j--)
    {
        OLED_DisplayChar(xtemp,ytemp,integ[j]+48);
        //LCDSendData(DAT,integ[j]+48);
        xtemp+=8;
    }

    if(num_int==0)
    {
        OLED_DisplayChar(xtemp,ytemp,'0');
        //LCDSendData(DAT,'0');
        xtemp+=8;
    }

    /*  显示整数 小数之间小数点*/
    OLED_DisplayChar(xtemp,ytemp,'.');
    //LCDSendData(DAT,'.');
    xtemp+=8;

    /*  显示小数位 */
    for(j=dec_dig-1;j>=0;j--)
    {
        OLED_DisplayChar(xtemp,ytemp,decim[j]+48);
        //LCDSendData(DAT,decim[j]+48);
        xtemp+=8;
    }
}

/************************************************/
void OLED_Show_Init();

void OLED_Show_Init()
{
    OLED_ClearScreen();

    OLED_DisplayChar(0 , 0,'T');
    OLED_DisplayChar(8 , 0,'H');
    OLED_DisplayChar(16, 0,':');
    OLED_DisplayChar(64, 0,'D');
    OLED_DisplayChar(72, 0,'i');
    OLED_DisplayChar(80, 0,'r');
    OLED_DisplayChar(88, 0,':');
    OLED_DisplayChar(0 ,16,'N');
    OLED_DisplayChar(8 ,16,'S');
    OLED_DisplayChar(16,16,':');
    OLED_DisplayChar(72,16,'D');
    OLED_DisplayChar(80,16,'S');
    OLED_DisplayChar(88,16,':');
    OLED_DisplayChar(0 ,32,'D');
    OLED_DisplayChar(16,32,':');
    OLED_DisplayChar(40,32,'%');
    OLED_DisplayChar(80,32,'S');
    OLED_DisplayChar(88,32,':');
    OLED_DisplayChar(80,48,'V');
    OLED_DisplayChar(88,48,':');
}
void OLED_Show(int16_t  OilDoor_Value,
               uint16_t RealTime_Speed,
               int8_t   Direction,
               uint16_t Target_Speed_UART,
               uint8_t  Duty_Motor,
               uint16_t Distance_mm,
               uint16_t Speed_Sound)
{

    //*************  1   油门值（-100到100） ****************************
    if(OilDoor_Value == 0)
        OLED_DisplayChar(24, 0,' ');
    else if(OilDoor_Value < 0){
        OLED_DisplayChar(24, 0,'-');
        OilDoor_Value = -OilDoor_Value;
    }
    else
        OLED_DisplayChar(24, 0,'+');

    OLED_DisplayChar(32, 0,(int) ( OilDoor_Value/100 +48 )     );
    OLED_DisplayChar(40, 0,(int) ( (OilDoor_Value/10)%10 +48 ) );
    OLED_DisplayChar(48, 0,(int) ( OilDoor_Value%10 +48 )      );
    //************  2   方向显示**************************************
    if(Direction > 0)
    {
        OLED_DisplayChinese(96, 0, 0);//正
        OLED_DisplayChinese(112,0, 2);//转
    }
    else
    {
        OLED_DisplayChinese(96, 0, 1);//反
        OLED_DisplayChinese(112,0, 2);//转
    }
    //************  3   电机真实速度显示******************************
    OLED_DisplayChar(24,16,(int) ( RealTime_Speed/100 +48 )     );
    OLED_DisplayChar(32,16,(int) ( (RealTime_Speed/10)%10 +48 ) );
    OLED_DisplayChar(40,16,(int) ( RealTime_Speed%10 +48 )      );

    //************  4  串口设定的目标速度*****************************
    OLED_DisplayChar(96, 16,(int) (  Target_Speed_UART/100 +48 )    );
    OLED_DisplayChar(104,16,(int) ( (Target_Speed_UART/10)%10 +48 ) );
    OLED_DisplayChar(112,16,(int) (  Target_Speed_UART%10 +48 )     );
    //************  5  占空比********************************
    OLED_DisplayChar(24,32,(int) ( Duty_Motor/10 +48 ) );
    OLED_DisplayChar(32,32,(int) ( Duty_Motor%10 +48 ) );
    //************  6  超声波测得的距离******************************
    OLED_DisplayChar(96,32, (int) (  Distance_mm/1000 +48 )   );
    OLED_DisplayChar(104,32,(int) ( (Distance_mm/100)%10 +48 ));
    OLED_DisplayChar(112,32,(int) ( (Distance_mm/10)%10 +48 ) );
    OLED_DisplayChar(120,32,(int) (  Distance_mm%10 +48 )     );
    //************  7  温度补偿后的声速******************************
    OLED_DisplayChar(96, 48,(int) (  Speed_Sound/100 +48 )    );
    OLED_DisplayChar(104,48,(int) ( (Speed_Sound/10)%10 +48 ) );
    OLED_DisplayChar(112,48,(int) (  Speed_Sound%10 +48 )     );
    //*************************************************************************Finish
}


