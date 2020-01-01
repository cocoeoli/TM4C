//#include "pwm.h"
//
//void pwm1_init(void)
//{
//        SysCtlPWMClockSet(SYSCTL_PWMDIV_32);  //80M/32
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//
//        //
//
//        // Consult the data sheet to see which functions are allocated per pin.
//        // TODO: change this to select the port/pin you are using.
//        //
//        GPIOPinConfigure(GPIO_PF1_M1PWM5);
//        GPIOPinConfigure(GPIO_PF2_M1PWM6);
//        GPIOPinConfigure(GPIO_PF3_M1PWM7);
//
//        //
//        // Configure the PWM function for this pin.
//        // Consult the data sheet to see which functions are allocated per pin.
//        // TODO: change this to select the port/pin you are using.
//        //
//        GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
//        GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
//        GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
//
//        PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
//        PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
//
//        // 10hz, 10ms, 100000000ns,  50000
//        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, SysCtlClockGet()/20000);
//        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet()/20000);
//
//        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*80) / 100 );  //10%
//        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*80) / 100 );
//        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*80) / 100 );
//        //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 5000);
//        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
//        PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
//        PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
//
//        //
//        // Enable the PWM generator block.
//        //
//        PWMGenEnable(PWM1_BASE, PWM_GEN_2);
//        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
//
//}
//
//void pwm0_init(void)
//{
//        SysCtlPWMClockSet(SYSCTL_PWMDIV_32);  //80M/32
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//
//        //
//
//        // Consult the data sheet to see which functions are allocated per pin.
//        // TODO: change this to select the port/pin you are using.
//        //
//        GPIOPinConfigure(GPIO_PE4_M0PWM4);
//        //
//        // Configure the PWM function for this pin.
//        // Consult the data sheet to see which functions are allocated per pin.
//        // TODO: change this to select the port/pin you are using.
//        //
//        GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
//
//        PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
//
//        // 10hz, 10ms, 100000000ns,  50000
//        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/1000);
//
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*10) / 100 );  //10%
//        //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 5000);
//        PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
//        //
//        // Enable the PWM generator block.
//        //
//        PWMGenEnable(PWM0_BASE, PWM_GEN_2);
//
//}
//
//void Search_thro(uint32_t Pass_value)
//{
//    static uint32_t tro_value[2];    //两次值缓存比较
//    static int16_t kd;        //判断斜率
//    uint32_t ad_value, t_value;
//
//    ad_value = Pass_value;
//    if(ad_value>3800){
//        tro_value[1] = tro_value[0];
//        tro_value[0] = ad_value;
//        kd = tro_value[0] - tro_value[1];
//    }
//    if( tro_value[0]>3800 && kd > 0 )
//        ad_value = 3800;
//
//    if( ad_value > 1800 && ad_value < 2000 ){     ////////////////////////电机停止区间
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*1) / 100 );
//    }
//    else{
//        if( ad_value < 1800 ){
//                t_value = (1800-ad_value)/18;
//                if(t_value > 95 || t_value<3 )
//                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*99) / 100 );
//                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*t_value) / 100 );
//            }
//            else{
//                t_value = (ad_value - 1800)/18;
//                if(t_value > 95 || t_value<3)
//                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*99) / 100 );
//                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*t_value) / 100 );
//            }
//    }
//
//}
//
//
//
