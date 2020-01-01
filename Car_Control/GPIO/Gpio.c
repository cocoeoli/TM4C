/*
 * Gpio.c
 *
 *  Created on: 2018��2��1��
 *      Author: wk
 */
#include "Gpio.h"
uint8_t KeyRead = 0;

void Led_Key_Init(void)
{
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
       GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2);
       HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
       HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
       HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
       GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);                     //    ����key1-->PF4 ����
       GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
unsigned char key_scan(void)
{
    KeyRead = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
    if(!KeyRead)
    {
        delay_ms(100);
        //ȷ�ϰ������£�����1
        if(!KeyRead)
            return 1;
        while(!KeyRead);
    }
    else
        return 0;
    //����û�а���ʱ����������ֵΪ0
}
