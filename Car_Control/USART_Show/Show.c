/*
 * Show.c
 *
 *  Created on: 2018Äê4ÔÂ6ÈÕ
 *      Author: admin
 */
#include "Show.h"

void ShowValue(uint8_t Pos, int16_t Value)
{
    bool Flag = 0;
    uint8_t ShowBuffer0[] = "t0.txt=\"000\"";
    uint8_t ShowBuffer1[] = "t1.txt=\"000\"";
    uint8_t ShowBuffer2[] = "t2.txt=\"000\"";

    if(Value < 0){
        Value = -Value;
        Flag = 1;
    }

    ShowBuffer0[8] = ShowBuffer1[8] = ShowBuffer2[8] = Value/100  +'0';
    ShowBuffer0[9] = ShowBuffer1[9] = ShowBuffer2[9] = Value/10%10+'0';
    ShowBuffer0[10]= ShowBuffer1[10]= ShowBuffer2[10]= Value%10   +'0';

    uint8_t i;
    switch(Pos)
    {
    case 0:
        for(i=0;i<=11;i++)
            UARTCharPut(UART_BASE_ADDRESS_Show, ShowBuffer0[i]);
        break;
    case 1:
        if(Flag == 1)
            ShowBuffer1[8] = '-';
        for(i=0;i<=11;i++)
            UARTCharPut(UART_BASE_ADDRESS_Show, ShowBuffer1[i]);
        break;
    case 2:
        for(i=0;i<=11;i++)
            UARTCharPut(UART_BASE_ADDRESS_Show, ShowBuffer2[i]);
        break;
    default:
        break;
    }

    UARTCharPut(UART_BASE_ADDRESS_Show, 0xFF);
    UARTCharPut(UART_BASE_ADDRESS_Show, 0xFF);
    UARTCharPut(UART_BASE_ADDRESS_Show, 0xFF);
}



