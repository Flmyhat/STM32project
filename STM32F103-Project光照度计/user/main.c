#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include "LED.h"
#include "stdio.h"
#include "OLED_IIC.h"
 
 /*
 Keil: MDK5.10.0.2
MCU:stm32f103c8
Ӳ���ӷ���
GY-39---STM32
1��GY-39_RX---STM32_TX,STM32��λ������A5 82 27 ��ģ��
2��STM32_TX---FT232,STM32�������ϴ�����λ��
3��GY-39_TX---STM32_RX������ģ������
���˵��:
�ó�����ô��ڷ�ʽ��ȡģ�����ݣ�������9600

ע��ģ�鲨������͸ó�������һ��Ϊ9600���жϺ���λ��stm32f10x_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4����ռ���ȼ���4����Ӧ���ȼ� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*��ռ���ȼ��ɴ���жϼ���͵��ж�*/
	/*��Ӧ���ȼ����ȼ�ִ��*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//�ж�����
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���Ӧ
  NVIC_Init(&NVIC_X);
}
void send_com(u8 data)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;//�����ֽ�
	//bytes[2]=0x28;
	USART_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}
//typedef struct
//{
//    uint32_t P;
//    uint16_t Temp;
//    uint16_t Hum;
//    uint16_t Alt;
//} bme;

int fputc(int ch, FILE *f)
{
 while (!(USART1->SR & USART_FLAG_TXE));
 USART_SendData(USART1, (unsigned char) ch);// USART1 ���Ի��� USART2 ��
 return (ch);
}

char strTemp[20];//OLED��ʾ��ʱ����

int main(void)
{
  u8 sum=0,i=0, j=0;
	float  Temp_gaungzhaodu=0;
//	int16_t data=0;
//	uint16_t data_16[2]={0};
	unsigned char maohao_string[]=":"; 
	unsigned char temp_string[]="Lux"; 
	//unsigned char zhixian_string[]="---"; 
	delay_init(72);
	NVIC_Configuration();
	Usart_Int(9600);
	
	point= &picture_tab[0];
	IO_init();	//OLED�˿ڳ�ʼ��
	OLED_init();
	OLED_full();
	delay_ms(1000);
	OLED_clear();
	
	delay_ms(100);//�ȴ�ģ���ʼ�����
	//send_com(0x82);//���Ͷ���ѹ��ʪ��ָ��
	//send_com(0x81);//����������ն�
	while(1)
	{
		
		send_com(0x51);//����������ն�
		delay_ms(100);
		if(Receive_ok)//���ڽ�����ϣ��ڴ����ж�1�����������õ�
		{
			for(sum=0,i=0;i<(raw_data[3]+4);i++)//rgb_data[3]=3
			sum+=raw_data[i];
			if(sum==raw_data[i])//У����ж�
			{
				Temp_gaungzhaodu=(raw_data[4]<<24)|(raw_data[5]<<16)|(raw_data[6]<<8)|(raw_data[7]);//��ȡ�����¶ȵ�ֵ
				Temp_gaungzhaodu=Temp_gaungzhaodu/100;//���ն�������
				sprintf(strTemp, "%.2f", Temp_gaungzhaodu);     //���3.30V����˼��ת��Ϊ�ַ���
				
				for(j=0;j<6;j++)
				{
					OLED_ShowCN(16+j*16,0,j); //������ʾ 
				}
				for(j=6;j<12;j++)
				{
					OLED_ShowCN((j-6)*16,2,j);
				}
				OLED_ShowStr(96,2,maohao_string,2);
				OLED_ShowStr(80,4,temp_string,2);
				OLED_ShowStr(24,4,strTemp,2);
				for(j=12;j<15;j++)
				{
					OLED_ShowCN(24+(j-12)*16,6,j);
				}
				OLED_ShowStr(72,6,maohao_string,2);
				for(j=15;j<18;j++)
				{
					OLED_ShowCN(80+(j-15)*16,6,j);
				}

			}
			Receive_ok=0;//����������ϱ�־
			delay_ms(1000);
		}
	}
}
