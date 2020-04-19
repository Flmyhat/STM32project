#include "stm32f0xx.h"

#define Alarm_H         GPIOB->BSRR = GPIO_Pin_7	 /* GPIO_SetBits(GPIOB , GPIO_Pin_6)   */
#define Alarm_L        GPIOB->BRR  = GPIO_Pin_7   /* GPIO_ResetBits(GPIOB , GPIO_Pin_6) */

void Alarm_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	/* Configure I2C2 pins: PB6->SCL and PB7->SDA */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);//����GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1 ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ��ѡ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  //��·�������ӵ���GPIO_OType_PP
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//SDA_H;//PB8����
	//SCL_H;//PB9����
	Alarm_L;
}



