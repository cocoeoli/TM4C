#ifndef _CAR_CTRL_H_
#define _CAR_CTRL_H_

#include "../pwm/pwm_config.h"

void car_ctrl_init(void);

void car_go_forward(void);
void car_go_back(void);
void car_go_left(void);
void car_go_right(void);

void car_forward_left(uint8_t add);
void car_forward_right(uint8_t add);
void car_back_right(uint8_t add);
void car_back_left(uint8_t add);

void car_left_left(uint8_t add);
void car_left_right(uint8_t add);
void car_right_left(uint8_t add);
void car_right_right(uint8_t add);


void car_turn_left(uint8_t speed);
void car_turn_right(uint8_t speed);

//void car_keep_straight(void);
//void car_move_to(uint8_t x_target, uint8_t y_target);

void car_stop(void);

void car_wheel_dir_set(bool w1, bool w2, bool w3, bool w4);
void car_wheel_speed_set(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4);

#endif /* _CAR_CTRL_H_ */
