/*
 * QEI_Config.c
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: D
 */
#include "QEI_Model.h"

void QEI0_Init(unsigned int QEI0_IntTime_ms)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    /* Unlock PD7 */
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR)  |= GPIO_PIN_7;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x00;

    GPIOPinConfigure(GPIO_PD6_PHA0);
    GPIOPinConfigure(GPIO_PD7_PHB0);
    GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    /* QEI Mode Configure */
    QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 13*30*4);

    /* Velocity Configure */
    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, QEI0_IntTime_ms*(SysCtlClockGet()/1000));
    QEIVelocityEnable(QEI0_BASE);

    QEIEnable(QEI0_BASE);

    /* Interrupt Configure and Enable */
    QEIIntRegister(QEI0_BASE, IntHandler_QEI0);
    QEIIntEnable(QEI0_BASE, QEI_INTDIR | QEI_INTTIMER);
    IntEnable(INT_QEI0);
}
void QEI1_Init(unsigned int QEI1_IntTime_ms)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);

    /* QEI Mode Configure */
    QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 13*30*4);

    /* Velocity Configure */
    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, QEI1_IntTime_ms*(SysCtlClockGet()/1000));
    QEIVelocityEnable(QEI1_BASE);

    QEIEnable(QEI1_BASE);

    /* Interrupt Configure and Enable */
    QEIIntRegister(QEI1_BASE, IntHandler_QEI1);
    QEIIntEnable(QEI1_BASE, QEI_INTDIR | QEI_INTTIMER);
    IntEnable(INT_QEI1);
}



