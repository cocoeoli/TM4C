//倒立摆
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "inc/hw_memmap.h"                 //defining the memory map of the device
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/fpu.h"
#include "driverlib/uart.h"
#include "driverlib/qei.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "utils/uartstdio.h"

#include "mydrivers/pid/pid.h"
#include "mydrivers/uart/uart.h"
#include "mydrivers/key/key.h"
#include "mydrivers/QEI/QEI_Model.h"
#include "mydrivers/pwm/pwm.h"
#include "mydrivers/adc/adc.h"
#include "mydrivers/mpu6050/mpu6050.h"
#include "mydrivers/mpu6050/inv_mpu.h"
#include "mydrivers/mpu6050/inv_mpu_dmp_motion_driver.h"


float    pitch=0,roll=0,yaw=0; //欧拉角

void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);      //200M/5 = 40M
        UART0_init();
        while(mpu_dmp_init())  //初始化mpu6050
            delay_ms(10);
        UARTprintf("Mpu6050 Initialization Is Complete!\n\n");
        while(1)
        {
            mpu_dmp_get_data(&pitch,&roll,&yaw);
            delay_ms(100);
            UARTprintf("yaw is %d     roll is  %d      Pitch is %d    \n",(short)yaw,(short)roll,(short)pitch);
        }
}


