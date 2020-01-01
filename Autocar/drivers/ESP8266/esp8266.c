#include "stdio.h"
#include "string.h"
#include "esp8266.h"
#include "../my_delay/delay.h"
#include "../uart/uart.h"
#include "../PID/pid.h"

//uint8_t IS_unvantra;                                       //是否开启透传？
//char *cstr1 = "*C1RZ#";   //系统复位
//uint16_t Ti=180;

extern uint8_t uart5_buff[20]; 			   //wifi接收缓冲,最大20个字节.
//uint16_t USART2_RX_STA;   	                           //标志位，判断是否收到消息
//extern float set_yaw;

//void error_mes(void)
//{
//	uint8_t i;
//	uint8_t errormes[] = {0xB4,0xED,0xCE,0xF3,0xD6,0xB8,0xC1,0xEE,0xA3,0xAC,0xC7,
//                     0xEB,0xD6,0xD8,0xB7,0xA2,0xA3,0xA1,0x0D,0x0A}; //错误提示
//	for(i = 0; i < 20; i++){
//					USART2->DR = errormes[i];
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//				}
//	delay_ms(100);
//}


void ESP8266Clint_Init(void)        //作为客户端
{
			uint8_t i ;
		    uint8_t at_rst[] = {0x41, 0x54, 0x2B, 0x52, 0x53, 0x54, 0x0D, 0x0A};                   //AT+RST(回车) 初始化
			uint8_t at_cipstart[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D,   //电脑
				0x22,0x54,0x43,0x50,0x22,0x2C,0x22,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x34,
				0x33,0x2E,0x33,0x38,0x22,0x2C,0x38,0x30,0x38,0x30,0x0D,0x0A};                //AT+CIPSTART="TCP","192.168.43.38",8080(回车)  连接服务器
//			uint8_t at_cipstart[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D,   //手机
//			    0x22,0x54,0x43,0x50,0x22,0x2C,0x22,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x34,
//			    0x33,0x2E,0x31,0x22,0x2C,0x31,0x32,0x33,0x34,0x0D,0x0A};                     //AT+CIPSTART="TCP","192.168.43.1",1234(回车)  连接服务器
			uint8_t at_cipmode[] = {0x41,0x54,0x2B,0x43,0x49,0x50,0x4D,0x4F,0x44,0x45,0x3D,0x31,0x0D,0x0A}; //	AT+CIPMODE=1(回车)   模式设置一
			uint8_t at_cipsend[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x45,0x4E,0x44,0x0D,0x0A};            //AT+CIPSEND(回车)        透传模式
			
			for(i = 0; i < 8; i++){
			    UART_send_char(at_rst[i], UART5_BASE);
			}
			delay_ms(1500);
			for(i = 0; i < 40; i++){
			    UART_send_char(at_cipstart[i], UART5_BASE);
			}
			delay_ms(2000);
			for(i = 0; i < 14; i++){
			    UART_send_char(at_cipmode[i], UART5_BASE);
			}
			delay_ms(800);
			for(i = 0; i < 12; i++){
			    UART_send_char(at_cipsend[i], UART5_BASE);
			}
			delay_ms(800);
			UART_send_string("wifi connected! \n", UART5_BASE);
//			IS_unvantra = 1;  //开启透传
}

////////
void ESP8266Server_Init(void)        //作为服务器，       ip:192.168.4.1   key: 88888888    port:333
{
            uint8_t i ;
            uint8_t at_rst[] = {0x41, 0x54, 0x2B, 0x52, 0x53, 0x54, 0x0D, 0x0A};                 //AT+RST(回车) 初始化
            uint8_t at_cipmux[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x4D,0x55,0x58,0x3D,0x31,0x0D,0x0A};                //AT+CIPMUX=1(回车)  多连接
            uint8_t at_cipserver[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x45,0x52,0x56,0x45,0x52,0x3D,0x31,0x0D,0x0A}; //  AT+CIPSERVER=1(回车) 服务器开启
            uint8_t at_cipsto[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x4F,0x3D,0x33,0x36,0x30,0x30,0x0D,0x0A};  //AT+CIPSTO=3600(回车)  超时时间1h

            for(i = 0; i < 8; i++){
                UART_send_char(at_rst[i], UART5_BASE);
            }
            delay_ms(1500);
            for(i = 0; i < 13; i++){
                UART_send_char(at_cipmux[i], UART5_BASE);
            }
            delay_ms(1000);
            for(i = 0; i < 16; i++){
                UART_send_char(at_cipserver[i], UART5_BASE);
            }
            delay_ms(800);
            for(i = 0; i < 16; i++){
                UART_send_char(at_cipsto[i], UART5_BASE);
            }
            delay_ms(800);
}

void Espserver_send(char *str)     //服务器不能透传，   用发送函数模拟透传
{
    char *sendstr = "AT+CIPSEND=0,", numstr[5]={0};
    int icount=0;

    UARTIntDisable(UART5_BASE, UART_INT_RX | UART_INT_RT);          //关闭中断，防止接收确认字符

    icount = strlen(str);

    sprintf(numstr, "%d\x0d\x0a", icount);
    strcat(sendstr, numstr);
    UART_send_string(sendstr, UART5_BASE);           //发送指令  AT+CIPSEND=0,X(回车)
    delay_ms(100);
    UART_send_string(str, UART5_BASE);               //发送字符串

    memset(sendstr, 20, '\0');
    UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
}

// void select_mode(void)          //选择工作模式
// {
//	uint8_t len, str_num;
//
//	len = USART2_RX_STA&0x3fff;
//	str_num = uart5_buff[1];
//	switch((int)str_num){   		 //判断命令类型
////		case 65: str_float();        //A系列命令,调试pid     //
////		break;
//		case 67: esp_config(len);      //C系列命令   系统配置
//		break;
//		case 71: esp_routeplan(len);   //G系列命令   启动模式
//		break;
//		case 85: esp_controlcar(len);   //U系列命令  车辆控制
//	    break;
//		default:  error_mes();
//	}
// }

//void esp_config(uint16_t len)   //esp8266配置
//{
//	uint8_t str1, i, iserr=0;
//    str1 = uart5_buff[2];
//	switch((int)str1){
//		case 49:{                                        //系统复位命令
//				for(i=0; i<len; i++){
//					if(uart5_buff[i] == *cstr1++)
//					iserr++;
//				}
//				if(iserr==len){
//					 __set_FAULTMASK(1);
//					 NVIC_SystemReset();                 //系统软件复位
//					 delay_ms(500);
//					if(RCC_GetFlagStatus(RCC_FLAG_SFTRST)==0)
//						soft_reset(0);                  //复位失败
//				}
//				else error_mes();                       //指令错误
//				break;
//			}
//		case 50: UART_send_string("*CAR-OK#", USART2);
//			break;
//
////		case 50: esp_ipconfig();                        //esp8266 ip配置命令
////			break;
////		case 51: esp_wificonfig();                      //esp8266 wifi连接指令
////			break;
//		default: error_mes();
//	}
//
//}

//void esp_controlcar(uint16_t len)
//{
//	uint8_t str2;
//	char st[20];
//
//    str2 = uart5_buff[2];
//	switch((int)str2){
//		case 49:{     //检测是否可行U1
//			Car_Stop();
//			Iscar_run = 0;
//			UART_send_string("*U1-OK#", USART2);
//			delay_ms(500);
//			Barrier_detach();
//			break;
//		}
//		case 50:{
//			Car_Stop();
//			Iscar_run = 0;
//			UART_send_string("*U2-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//		case 51: {                                    //开始运动
//			Car_Run(Current_speed);
//			Iscar_run = 1;
//			UART_send_string("*U3-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//		case 52:{                                      //0度角度
//	//		Turn_angle(0-set_yaw, 1);
//			set_yaw = 0;
//			Iscar_run = 0;
//			UART_send_string("*U4-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//		case 53:{                                     //180度角度
//	//		Turn_angle(205-set_yaw, 3);
//			set_yaw = -180;
//			Iscar_run = 0;
//			UART_send_string("*U5-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//		case 54:{
//			Ti += 20;
//			sprintf(st, "ms: %d\n", Ti);
//		    UART_send_string(st, USART2);
//			delay_ms(100);
//			break;
//		}
//		case 55:{
//			Ti -= 20;
//			sprintf(st, "ms: %d\n", Ti);
//		    UART_send_string(st, USART2);
//			delay_ms(100);
//			break;
//		}
//        case 56:{
//			if(exter_speed>4500)
//				exter_speed = 2500;
//			exter_speed+=100;
//			sprintf(st, "exter_speed: %d\n", exter_speed);
//		    UART_send_string(st, USART2);
//			delay_ms(100);
//			break;
//		}
//		case 57:{                                    //右角度U9
//	//		Turn_angle(285-set_yaw, 2);
//			set_yaw = -90;
//			Iscar_run = 0;
//			UART_send_string("*U9-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//        case 65: {                                    //左角度
//	//		Turn_angle(75-set_yaw, 4);
//		    set_yaw = 90;
//			Iscar_run = 0;
//			UART_send_string("*UA-OK#", USART2);
//			delay_ms(100);
//			break;
//		}
//		default: error_mes();
//	}
//}
//
//void esp_routeplan(uint16_t len)
//{
//	uint8_t str;
//    str = uart5_buff[2];
//	switch((int)str){
//		case 48:{  			//待机模式
//			Mode = 0;
//			UART_send_string("*G0-OK#", USART2);
//			break;
//		}
//		case 49:{
//			Mode = 1;
//			UART_send_string("*G1-OK#", USART2);
//			break;
//		}
//		case 50:{
//			Mode = 2;
//			UART_send_string("*G2-OK#", USART2);
//			break;
//		}
//		default: error_mes();
//	}
//}



//void esp_ipconfig(void)
//{
//	uint8_t str, i, ord_buf[30];
//    uint8_t atc_ipstart[] = {0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D}; //"AT+CIPSTART="

//	str = uart5_buff[3];
//	
//	for(i=4; i<USART2_RX_STA-1; i++)
//		ord_buf[i-4]=uart5_buff[i];	   //将收到字符的有用信息放置ord_buf中
//	
//	ord_buf[USART2_RX_STA-5] = 0x0d;
//	ord_buf[USART2_RX_STA-4] = 0x0a;
//	switch((int)str){
//		case 31:{ 			//发送TCP连接地址及端口
//			for(i=0; i<3; i++){
//				  USART2->DR = 0x2B;
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//			}
//			delay_ms(1000);
//			IS_unvantra=0;  //关闭透传
//			for(i = 0; i < 12; i++){
//					USART2->DR = atc_ipstart[i];
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//				}
//			for(i = 0; i < USART2_RX_STA-3; i++){
//					USART2->DR = ord_buf[i];
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//			}
//			delay_ms(2000);
//			break;
//		}
//		default: error_mes();
//	}
//}


//void esp_wificonfig(void)
//{
//	uint8_t str, i, ord_buf[30];
//	uint8_t at_cwjap[] = {0x41,0x54,0x2B,0x43,0x57,0x4A,0x41,0x50,0x3D}; //"AT+CWJAP="
//	str = uart5_buff[3];
//	for(i=4; i<USART2_RX_STA-1; i++)
//		ord_buf[i-4]=uart5_buff[i];	   //将收到字符的有用信息放置ord_buf中
//	ord_buf[USART2_RX_STA-5] = 0x0d;
//	ord_buf[USART2_RX_STA-4] = 0x0a;
//	switch((int)str){
//		case 31:{                           //发送TCP连接地址及端口
//			for(i=0; i<3; i++){
//				  USART2->DR = 0x2B;
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//			}
//			delay_ms(1000);
//			IS_unvantra=0;  //关闭透传
//			for(i = 0; i < 9; i++){
//					USART2->DR = at_cwjap[i];
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//				}
//			for(i = 0; i < USART2_RX_STA-3; i++){
//					USART2->DR = ord_buf[i];
//					while((USART2->SR & 0x40) == 0);//直到发送成功
//			}
//			delay_ms(2000);
//			break;
//		 }
//		default: error_mes();
//	}
//	
//}


//void Turn_angle(float angle, uint8_t dir)
//{
//	uint16_t Speed;
//	Speed = Current_speed + 300;
//	switch(dir){
//		case 1:{
//			if(angle<0 && angle>-180){
//				//Car_SpinRight(Speed+200, Speed);
//			}
//			else{
//				//Car_SpinLeft(Speed, Speed);
//			}
//			delay_ms(Ti);
//			Car_Stop();
//			break;
//		}
//		case 2:{
//			if(angle>0 && angle<180){
//				Car_SpinLeft(Speed+200, Speed);
//			}
//			else{
//				Car_SpinRight(Speed+200, Speed);
//			}
//			delay_ms(Ti);
//			Car_Stop();
//			break;
//		}
//		case 3:{
//			if(angle>0){
//				Car_SpinLeft(Speed+200, Speed);
//			}
//			else{
//				Car_SpinRight(Speed+200, Speed);
//			}
//			delay_ms(Ti);
//			Car_Stop();
//			break;
//		}
//		case 4:{
//			if(angle<0){
//				Car_SpinRight(Speed+200, Speed);
//			}
//			else{
//				Car_SpinLeft(Speed+200, Speed);
//			}
//			delay_ms(Ti);
//			Car_Stop();
//			break;
//		}
//	}
//
//
//}
