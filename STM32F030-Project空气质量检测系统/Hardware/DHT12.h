#ifndef _DHT12_H_
#define _DHT12_H_
#include "stm32f0xx.h"
#include "myiic.h"
#include "stdio.h"
#include "usart.h"
#include "MyLCD.h"


void sensor_iic_init(void);//��ʼ��DHT12_IIC
void sensor_read(void);//��ȡ����

extern unsigned char maohao_string[]; 



#endif	//_DHT12_H_
