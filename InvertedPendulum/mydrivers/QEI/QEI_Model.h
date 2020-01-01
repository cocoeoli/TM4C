///*
// * QEI_Model.h
// *
// *  Created on: 2018Äê1ÔÂ29ÈÕ
// *      Author: bobo
// */
//
//#ifndef QEI_MODEL_H_
//#define QEI_MODEL_H_
//
//typedef struct
//{
//    uint32_t periph;
//    uint32_t base;
//    uint32_t swap_flag;
//    uint32_t Qinterrupt;
//
//    uint32_t gpio_periph;
//    uint32_t gpio_port;
//    uint8_t  gpio_pin;
//    uint32_t gpio_cfg_a;
//    uint32_t gpio_cfg_b;
//
//    int32_t dir;
//    int32_t velocity;   /*  unit: pulse edge per second */   //
//    int32_t Init_Pos;
//    uint32_t Now_Pos;      //0~1040
//
//}user_qei_data_t;
//
//extern user_qei_data_t qei_data_array[2];
////extern void QEI_InitConfig(user_qei_data_t *qei_data);
//extern void QEI_Config(void);
//extern void QEI0_IRQHandler(void);
//
//int read_QEI(void);
//
//#endif /* QEI_MODEL_H_ */
