#include "car_ctrl.h"
#include "../my_delay/delay.h"

//速度在0-100之间，对应PWM的占空比
extern uint16_t w1_speed = 40;
extern uint16_t w2_speed = 42;
extern uint16_t w3_speed = 40;
extern uint16_t w4_speed = 40;

//四个电机的控制引脚
//1. Dir:PA2, PA3, PWM:PB4
//2. Dir:PA4, PA5, PWM:PB5
//3. Dir:PA6, PA7, PWM:PB6
//4. Dir:PC6, PC7, PWM:PB7

void car_ctrl_init(void)
{
    PWM0_0123_init();//驱动电机
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) ;
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) ;
    
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);    // 1
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);    // 2
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);    // 3
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);    // 4
    
    //开启驱动电机4路PWM输出
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
    
    car_stop();
}

void car_go_forward(void)
{
    car_wheel_dir_set(0, 0, 0, 0);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed, w4_speed);
}

void car_go_back(void)
{
    car_wheel_dir_set(1, 1, 1, 1);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed, w4_speed);
}

void car_go_left(void)
{
    car_wheel_dir_set(1, 0, 0, 1);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed, w4_speed);
}

void car_go_right(void)
{
    car_wheel_dir_set(0, 1, 1, 0);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed, w4_speed);
}

void car_turn_left(uint8_t speed)
{
    car_wheel_dir_set(1, 0, 1, 0);
    car_wheel_speed_set(speed, speed, speed, speed);
}

void car_turn_right(uint8_t speed)
{
    car_wheel_dir_set(0, 1, 0, 1);
    car_wheel_speed_set(speed, speed, speed, speed);
}

void car_forward_right(uint8_t add)
{
    car_wheel_dir_set(0, 0, 0, 0);
    car_wheel_speed_set(w1_speed + add, w2_speed, w3_speed + add, w4_speed);
}
void car_forward_left(uint8_t add)
{
    car_wheel_dir_set(0, 0, 0, 0);
    car_wheel_speed_set(w1_speed, w2_speed + add, w3_speed, w4_speed + add);
}

void car_back_right(uint8_t add)
{
    car_wheel_dir_set(1, 1, 1, 1);
    car_wheel_speed_set(w1_speed + add, w2_speed, w3_speed + add, w4_speed);
}
void car_back_left(uint8_t add)
{
    car_wheel_dir_set(1, 1, 1, 1);
    car_wheel_speed_set(w1_speed, w2_speed + add, w3_speed, w4_speed + add);
}

void car_left_left(uint8_t add)
{
    car_wheel_dir_set(1, 0, 0, 1);
    car_wheel_speed_set(w1_speed + add, w2_speed + add, w3_speed, w4_speed);
}
void car_left_right(uint8_t add)
{
    car_wheel_dir_set(1, 0, 0, 1);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed + add, w4_speed + add);
}

void car_right_left(uint8_t add)
{
    car_wheel_dir_set(0, 1, 1, 0);
    car_wheel_speed_set(w1_speed, w2_speed, w3_speed + add, w4_speed + add);
}
void car_right_right(uint8_t add)
{
    car_wheel_dir_set(0, 1, 1, 0);
    car_wheel_speed_set(w1_speed + add, w2_speed + add, w3_speed, w4_speed);
}

void car_stop(void)
{
    car_wheel_speed_set(1, 1, 1, 1);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0xFF);//1. PA2, PA3
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0xFF);
    
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0xFF);//2. PA4, PA5
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0xFF);
    
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0xFF);//3. PA6, PA7
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0xFF);
    
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0xFF);//4. PC6, PC7
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0xFF);
}

//void car_keep_straight(void)
//{
//    extern float dis2, dis3;
//    float Err, val = 0.5;
//    while(1){
//        Err = dis2 - dis3;
//        if(Err > 10){
//            break;
//        }
//        if(Err > val){
//            car_turn_left(20);
//        }
//        else if(Err < -val){
//            car_turn_right(20);
//        }
//        else{
//            break;
//        }
//    }
//}
//void car_move_to(uint8_t x_target, uint8_t y_target)
//{
//    extern float dis1, dis3, dis4;
//    float X, Y, err_x, err_y;
//    uint16_t count = 0;
//    car_keep_straight();
//    while(1){
//        X = (dis1+dis3)/2;
//
//        err_x = X - x_target;
//
//        if(err_x > 2){
//            car_go_left();
//        }
//        else if( err_x < -2 ){
//            car_go_right();
//        }
//        else{
//            car_stop();
//            break;
//        }
//        delay_ms(20);
//        count++;
//        if(count == 50){
//            count = 0;
//            car_keep_straight();
//        }
//    }
//
//    count = 0;
//    car_keep_straight();
//    while(1){
//        Y     = dis4;
//        err_y = Y - y_target;
//
//        if(err_y > 2){
//            car_go_back();
//        }
//        else if( err_y < -2 ){
//            car_go_forward();
//        }
//        else{
//            car_stop();
//            break;
//        }
//        delay_ms(20);
//        count++;
//        if(count == 50){
//            count = 0;
//            car_keep_straight();
//        }
//    }
//}
void car_wheel_speed_set(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4)
{
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, s1*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));//1
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, s2*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));//2
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, s3*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));//3
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, s4*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));//4
}

void car_wheel_dir_set(bool w1, bool w2, bool w3, bool w4)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, ((w1==1)?0xFF:0x00));//1. PA2, PA3
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, ((w1==0)?0xFF:0x00));

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, ((w2==1)?0xFF:0x00));//2. PA4, PA5
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, ((w2==0)?0xFF:0x00));

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, ((w3==1)?0xFF:0x00));//3. PA6, PA7
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, ((w3==0)?0xFF:0x00));

    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, ((w4==1)?0xFF:0x00));//4. PC6, PC7
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, ((w4==0)?0xFF:0x00));
}
