/*
 * MPU6050.c
 *
 *  Created on: 2018年2月5日
 *      Author: admin
 */

#include "MPU6050.h"

/*
 * MPU6050的初始化配置
 */
uint8_t MPU6050_Init(void)
{
    uint8_t res;

    I2C0_Init();
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0x80);//电源管理寄存器 1(0X6B).复位MPU6050
    delay_ms(200);
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0x00);//电源管理寄存器 1(0X6B).唤醒MPU6050
    MPU_Set_Gyro_Fsr(3);   //陀螺仪传感器,±2000dps
    MPU_Set_Accel_Fsr(0);  //加速度传感器,±2g
    MPU_Set_Rate(50);      //设置采样率50Hz,数字低通滤波器25Hz
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_INT_EN_REG, 0X00);    //中断使能寄存器.关闭所有中断
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_USER_CTRL_REG, 0X00); //用户控制寄存器.I2C主模式关闭
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_FIFO_EN_REG, 0X00);   //FIFO使能寄存器.关闭FIFO
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_INTBP_CFG_REG, 0X80); //中断/旁路设置寄存器.INT引脚低电平有效

    I2CReadRegOneByte(I2C0_BASE, MPU_ADDR, MPU_DEVICE_ID_REG, &res);
    if(res == MPU_ADDR) //器件ID正确
    {
        I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0X01); //设置CLKSEL,PLL X轴为参考
        I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT2_REG, 0X00); //加速度与陀螺仪都工作
        MPU_Set_Rate(50);                                                 //设置采样率为50Hz,数字低通滤波器25Hz
    }
    else
        return 1;
    return 0;
}

/*
 * 设置MPU6050陀螺仪传感器满量程范围
 *fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
 *返回值:0,设置成功
 *其他,设置失败
 */
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_GYRO_CFG_REG, fsr<<3);//设置陀螺仪满量程范围
}

/*
 * 设置MPU6050加速度传感器满量程范围
 *fsr:0,±2g;1,±4g;2,±8g;3,±16g
 *返回值:0,设置成功
 *其他,设置失败
 */
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_ACCEL_CFG_REG, fsr<<3);//设置加速度传感器满量程范围
}

/*
 *设置MPU6050的数字低通滤波器
 *lpf:数字低通滤波频率(Hz)
 *返回值:0,设置成功
 *返回值:0,设置成功其他,设置失败
 */
uint8_t MPU_Set_LPF(uint16_t lpf)
{
    uint8_t data = 0;
    if(lpf >= 188)
        data=1;
    else if(lpf >= 98)
        data=2;
    else if(lpf >= 42)
        data=3;
    else if(lpf >= 20)
        data=4;
    else if(lpf >= 10)
        data=5;
    else
        data=6;
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_CFG_REG, data);//设置数字低通滤波器
}

/*
 * 设置MPU6050的采样率(假定Fs=1KHz)
 *rate:4~1000(Hz)
 *返回值:0,设置成功
 *其他,设置失败
 */
uint8_t MPU_Set_Rate(uint16_t rate)
{
    uint8_t data;
    if(rate > 1000)
        rate = 1000;
    if(rate < 4)
        rate = 4;
    data = 1000/rate-1;
    data = I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_SAMPLE_RATE_REG, data);  //设置数字低通滤波器
    return MPU_Set_LPF(rate/2); //自动设置LPF为采样率的一半
}
uint8_t MPU_Set_Fifo(uint8_t sens)
{
    //Wait something to be added.
    return 0;
}

/*
 * MPU6050陀螺仪原始值
 */
void MPU6050_Get_Gyroscope(short *GyroX, short *GyroY, short *GyroZ)
{
    uint8_t buffer[6];
    uint32_t res;

    res = I2CReadRegMultiByte(I2C0_BASE, MPU_ADDR, MPU_GYRO_XOUTH_REG, buffer, 6);
    if(res == 0)
    {
        *GyroX = ( (uint16_t)((buffer[0]<<8) | buffer[1]) );// *5/82;
        *GyroY = ( (uint16_t)((buffer[2]<<8) | buffer[3]) );// *5/82;
        *GyroZ = ( (uint16_t)((buffer[4]<<8) | buffer[5]) );// *5/82;
    }
    else
        ;
}

/*
 * MPU6050加速度计原始值
 */
void MPU6050_Get_Accelerometer(short *AcceX, short *AcceY, short *AcceZ)
{
    uint8_t buffer[6];
    uint32_t res;

    res = I2CReadRegMultiByte(I2C0_BASE, MPU_ADDR, 0x3B, buffer, 6);
    if(res == 0)
    {
        *AcceX = ( (uint16_t)((buffer[0]<<8) | buffer[1]) );// /16384;
        *AcceY = ( (uint16_t)((buffer[2]<<8) | buffer[3]) );// /16384;
        *AcceZ = ( (uint16_t)((buffer[4]<<8) | buffer[5]) );// /16384;
    }
    else
        ;
}

/*
 * MPU6050温度值
 */
void MPU6050_Get_Temperature(short *Temperature)
{
    uint16_t buffer[2];
    short raw;
    short temp;

    I2CReadRegTwoByte(I2C0_BASE, MPU_ADDR, MPU_TEMP_OUTH_REG, buffer);

    raw = ((uint16_t)buffer[0]<<8) | buffer[1];
    temp = 36.53 + ((double)raw)/340;
    *Temperature = temp;
}

/*
 * 通过Y，Z轴上的加速度分量求反正切得到角度值
 * ***放大十倍***
 */
float MPU6050_atanAcceYZ_Get_Angle(short AcceY, short AcceZ)
{
    double  tempAcceY = AcceY, tempAcceZ = AcceZ;
    double  tmepYZ    = tempAcceY/tempAcceZ;
    double  tempRes   = 572.9578*atan(tmepYZ);
    float   Result    = tempRes/10;

    return Result;
}


