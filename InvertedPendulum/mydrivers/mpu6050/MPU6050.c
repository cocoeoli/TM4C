/*
 * MPU6050.c
 *
 *  Created on: 2018��2��5��
 *      Author: admin
 */

#include "MPU6050.h"

/*
 * MPU6050�ĳ�ʼ������
 */
uint8_t MPU6050_Init(void)
{
    uint8_t res;

    I2C0_Init();
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0x80);//��Դ����Ĵ��� 1(0X6B).��λMPU6050
    delay_ms(200);
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0x00);//��Դ����Ĵ��� 1(0X6B).����MPU6050
    MPU_Set_Gyro_Fsr(3);   //�����Ǵ�����,��2000dps
    MPU_Set_Accel_Fsr(0);  //���ٶȴ�����,��2g
    MPU_Set_Rate(50);      //���ò�����50Hz,���ֵ�ͨ�˲���25Hz
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_INT_EN_REG, 0X00);    //�ж�ʹ�ܼĴ���.�ر������ж�
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_USER_CTRL_REG, 0X00); //�û����ƼĴ���.I2C��ģʽ�ر�
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_FIFO_EN_REG, 0X00);   //FIFOʹ�ܼĴ���.�ر�FIFO
    I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_INTBP_CFG_REG, 0X80); //�ж�/��·���üĴ���.INT���ŵ͵�ƽ��Ч

    I2CReadRegOneByte(I2C0_BASE, MPU_ADDR, MPU_DEVICE_ID_REG, &res);
    if(res == MPU_ADDR) //����ID��ȷ
    {
        I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT1_REG, 0X01); //����CLKSEL,PLL X��Ϊ�ο�
        I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_PWR_MGMT2_REG, 0X00); //���ٶ��������Ƕ�����
        MPU_Set_Rate(50);                                                 //���ò�����Ϊ50Hz,���ֵ�ͨ�˲���25Hz
    }
    else
        return 1;
    return 0;
}

/*
 * ����MPU6050�����Ǵ����������̷�Χ
 *fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
 *����ֵ:0,���óɹ�
 *����,����ʧ��
 */
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_GYRO_CFG_REG, fsr<<3);//���������������̷�Χ
}

/*
 * ����MPU6050���ٶȴ����������̷�Χ
 *fsr:0,��2g;1,��4g;2,��8g;3,��16g
 *����ֵ:0,���óɹ�
 *����,����ʧ��
 */
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_ACCEL_CFG_REG, fsr<<3);//���ü��ٶȴ����������̷�Χ
}

/*
 *����MPU6050�����ֵ�ͨ�˲���
 *lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
 *����ֵ:0,���óɹ�
 *����ֵ:0,���óɹ�����,����ʧ��
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
    return I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_CFG_REG, data);//�������ֵ�ͨ�˲���
}

/*
 * ����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
 *rate:4~1000(Hz)
 *����ֵ:0,���óɹ�
 *����,����ʧ��
 */
uint8_t MPU_Set_Rate(uint16_t rate)
{
    uint8_t data;
    if(rate > 1000)
        rate = 1000;
    if(rate < 4)
        rate = 4;
    data = 1000/rate-1;
    data = I2CWriteRegOneByte(I2C0_BASE, MPU_ADDR, MPU_SAMPLE_RATE_REG, data);  //�������ֵ�ͨ�˲���
    return MPU_Set_LPF(rate/2); //�Զ�����LPFΪ�����ʵ�һ��
}
uint8_t MPU_Set_Fifo(uint8_t sens)
{
    //Wait something to be added.
    return 0;
}

/*
 * MPU6050������ԭʼֵ
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
 * MPU6050���ٶȼ�ԭʼֵ
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
 * MPU6050�¶�ֵ
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
 * ͨ��Y��Z���ϵļ��ٶȷ��������еõ��Ƕ�ֵ
 * ***�Ŵ�ʮ��***
 */
float MPU6050_atanAcceYZ_Get_Angle(short AcceY, short AcceZ)
{
    double  tempAcceY = AcceY, tempAcceZ = AcceZ;
    double  tmepYZ    = tempAcceY/tempAcceZ;
    double  tempRes   = 572.9578*atan(tmepYZ);
    float   Result    = tempRes/10;

    return Result;
}


