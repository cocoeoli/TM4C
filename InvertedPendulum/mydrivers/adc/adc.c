///*
// * adc.c
// *
// *  Created on: 2019年4月1日
// *      Author: xiong
// */
//
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_memmap.h"                 //defining the memory map of the device
//#include "inc/hw_gpio.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/adc.h"
//#include "utils/uartstdio.h"
//
//void adc0_init()
//{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//    GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_0);
//    ADCSequenceConfigure(ADC0_BASE,3,ADC_TRIGGER_PROCESSOR,0);
//    ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_CH3|ADC_CTL_IE|ADC_CTL_END);
//    ADCSequenceEnable(ADC0_BASE,3);
//    ADCIntClear(ADC0_BASE,3);
//}
//
//uint32_t Get_ad0()
//{
//    uint8_t i;
//    uint32_t ulADC0_Value[1], adc_value=0;
//       for(i=0; i<3; i++){
//           ADCProcessorTrigger(ADC0_BASE,3);
//           while(!ADCIntStatus(ADC0_BASE,3,false))
//               UARTprintf("error\n");
//           ADCSequenceDataGet(ADC0_BASE,3,ulADC0_Value);
//           adc_value += ulADC0_Value[0];
//       }
//
//      return adc_value/3;               //取三次平均值
//
//}
//
//
