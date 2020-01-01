
/*
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
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
#include "driverlib/adc.h"
#include "driverlib/rom_map.h"
#include "uartstdio.h"

#include "drivers/uart/uart.h"
#include "drivers/my_delay/delay.h"


const char START[] ="tm0.en=1\xFF\xFF\xFF";
const char END[] ="tm0.en=0\xFF\xFF\xFF";



bool once = true ;
uint8_t uart_flag = 0;
uint8_t uart0_buff[20];
uint8_t uart5_buff[20];

uint32_t ulADC0_Value[8];
int flag=0;
int times=0;
int rec_flag=0;
uint32_t ValueAvg = 0;
uint32_t last_val = 0;

void parking_ctrl(void);
void INT_pri(void);
void LigCtrl_Init(void);
void parking_light(int i);
void ADCInitial(void);

void main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);   //200/2.5=40M
    UART0_init();               //两个板卡通信
    UART5_Init(115200);
    INT_pri();
    ADCInitial();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);


    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))  ;
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
    while(1)
    {
        delay_ms(500);
        UART_send_int32_t(last_val, 1, UART0_BASE);
        UART_send_string("\t\x0d\x0a", UART0_BASE);
        if(uart5_buff[1]=='S')
        {
            if(once){
                UART_send_char_string(uart5_buff, 10, UART0_BASE);
                once = false;
            }

            switch(uart5_buff[2])
            {
                case '1' :
                {
                    parking_light(1);
                    parking_ctrl();
                    break;
                }
                case '2' :
                {
                    parking_light(2);
                    parking_ctrl();
                    break;
                }
                case '3' :
                {
                    parking_light(3);
                    parking_ctrl();
                    break;
                }
                case '4' :
                {
                    parking_light(4);
                    parking_ctrl();
                    break;
                }
                case '5' :
                {
                    parking_light(5);
                    parking_ctrl();
                    break;
                }
                case '6' :
                {
                    parking_light(6);
                    parking_ctrl();
                    break;
                }
            }
        }
        else if(uart5_buff[1]=='D')
        {
            UART_send_char_string(uart5_buff, 10, UART0_BASE);
            switch(uart5_buff[2])
            {
                case '5':
                {
                    switch(uart5_buff[3])
                    {
                        case '1':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
                            parking_ctrl();
                            break;
                        }
                        case '2':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
                            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
                            parking_ctrl();
                            break;
                        }
                        case '3':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
                            parking_ctrl();
                            break;
                        }
                        case '4':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 , 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
                            parking_ctrl();
                            break;
                        }
                    }

                }
                case '6':
                {
                    switch(uart5_buff[3])
                    {
                        case '1':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 , 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            parking_ctrl();
                            break;
                        }
                        case '2':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4  | GPIO_PIN_6 | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 , 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_PIN_5);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            parking_ctrl();
                            break;
                        }
                        case '3':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5  | GPIO_PIN_7, 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 , 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            parking_ctrl();
                            break;
                        }
                        case '4':
                        {
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 , 0x0);//light 1 2 3 4
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 , 0x0);//light 5 6
                            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_PIN_7);
                            parking_ctrl();
                            break;
                        }
                    }
                }
            }
        }
    }
}

void INT_pri(void)
{
    IntPrioritySet(INT_UART0,0x02);
    IntPrioritySet(INT_UART5,0x01);
    UARTIntRegister(UART0_BASE,UART0IntHandler);
    UARTIntRegister(UART5_BASE,UART5IntHandler);
    IntMasterEnable();
}
void LigCtrl_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
}
void parking_light(int i)
{
    switch(i)
    {
        case 0:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            break;
        }
        case 1:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
            break;
        }
        case 2:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_PIN_5);
            break;
        }
        case 3:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);
            break;
        }
        case 4:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 , 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_PIN_7);
            break;
        }
        case 5:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
            break;
        }
        case 6:
        {
            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6 , 0x0);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_PIN_7);
            break;
        }
    }
}

void ADCInitial(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);
    //设置ADC参考电压为外部3V
    ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V);
    ADCSequenceConfigure(ADC0_BASE,0,ADC_TRIGGER_PROCESSOR,0);
    //选择被采样的通道,该步进可以定义成序列的末尾（ADC_CTL_END位），同时它也可以配置成在步进完成后产生一个中断（ADC_CTL_IE位）
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ADC_CTL_CH0 |ADC_CTL_END | ADC_CTL_IE);
    //使能ADC采集序列
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCIntClear(ADC0_BASE, 0);
    ADCIntEnable(ADC0_BASE, 0);
}
void parking_ctrl(void)
{
    ADCProcessorTrigger(ADC0_BASE,0);
    delay_ms(100);
    ADCSequenceDataGet(ADC0_BASE, 0, ulADC0_Value);
    ValueAvg=(ulADC0_Value[0] + ulADC0_Value[1] + ulADC0_Value[2] + ulADC0_Value[3] +
               ulADC0_Value[4]+ulADC0_Value[5]+ulADC0_Value[6]+ulADC0_Value[7]+4)/8;
    ADCProcessorTrigger(ADC0_BASE,0);
    delay_ms(100);
    ADCSequenceDataGet(ADC0_BASE, 0, ulADC0_Value);
    last_val=(ulADC0_Value[0] + ulADC0_Value[1] + ulADC0_Value[2] + ulADC0_Value[3] +
                   ulADC0_Value[4]+ulADC0_Value[5]+ulADC0_Value[6]+ulADC0_Value[7]+4)/8;
    if(abs(ValueAvg-last_val)>200)
    {
        if(flag==0)
        {
            ADCSequenceDisable(ADC0_BASE, 0);
            UART_send_string(START,UART5_BASE);
            flag+=1;
            delay_s(3);
            ADCSequenceEnable(ADC0_BASE, 0);
            times+=1;
        }
        else
        {
            ADCSequenceDisable(ADC0_BASE, 0);
            UART_send_string(END,UART5_BASE);
            parking_light(0);
            flag-=1;
            delay_s(5);
            UART_send_string("click t22,1\xff\xff\xff", UART5_BASE);
            ADCSequenceEnable(ADC0_BASE, 0);
            times+=1;
            if(times==2){
                memset(uart5_buff,0,20);
                times=0;
                memset(ulADC0_Value,0,8);
            }
            once = true;
        }
    }
}
