/*
 * IIC_Init.h
 *
 *  Created on: 2018Äê2ÔÂ5ÈÕ
 *      Author: admin
 */

#ifndef I2C_INIT_I2C_INIT_H_
#define I2C_INIT_I2C_INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"

extern void I2C0_Init(void);
extern void I2C0_WriteOneByte(uint8_t SlaveAddress, uint8_t RegisterAddress, uint8_t Data);
extern void I2C0_ReadOneByte(uint8_t SlaveAddress, uint8_t RegisterAddress, uint32_t *Data);

extern uint32_t I2CWriteRegOneByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t ui8RegData);

extern uint32_t I2CWriteRegTwoByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t ui16RegData);

extern uint32_t I2CWriteRegMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData, uint32_t ui32WriteCount);
extern uint32_t I2CWriteRegMultiByte_MPU(uint8_t ui8SlaAddr, uint8_t ui8RegAddr, uint32_t ui32WriteCount, uint8_t *pui8RegData);

extern uint32_t I2CReadRegOneByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData);

extern uint32_t I2CReadRegTwoByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t *pui16RegData);

extern uint32_t I2CReadRegMultiByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr,uint8_t *pui8RegData, uint32_t ui32ReadCount);
extern uint32_t I2CReadRegMultiByte_MPU(uint8_t ui8SlaAddr, uint8_t ui8RegAddr, uint32_t ui32ReadCount, uint8_t *pui8RegData);

#endif /* I2C_INIT_I2C_INIT_H_ */






