#ifndef __MYIIC_H
#define __MYIIC_H
#include "SYSTICK.h"
#include "DHT12.h"
//#include "delay.h"

////IO��������
//#define SDA_IN()  {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=0x08000000;}//����������
//#define SDA_OUT() {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=0x03000000;}//ͨ���������


////IO��������	 
//#define IIC_SCL    PBout(13) //SCL���
//#define IIC_SDA    PBout(14) //SDA���	 
//#define READ_SDA   PBin(14)  //SDA���� 

#define read_SDA (GPIOB->IDR&GPIO_Pin_14) >>10 //PA10 SDA
#define set_SDA GPIO_SetBits(GPIOB, GPIO_Pin_14) //PA10 SDA
#define clr_SDA GPIO_ResetBits(GPIOB, GPIO_Pin_14) //PA10 SDA
#define set_SCL GPIO_SetBits(GPIOB, GPIO_Pin_13) //PA9 SCL
#define clr_SCL GPIO_ResetBits(GPIOB, GPIO_Pin_13) //PA9 SCL

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�


#endif
















