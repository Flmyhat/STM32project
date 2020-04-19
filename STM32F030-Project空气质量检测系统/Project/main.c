/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ����Ҫ����ɶ�eeprom��д�����Ͷ�����
 * ��汾  ��V1.3.0
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/

//ͷ�ļ�
#include <string.h>
#include "stm32f0xx.h"
#include "led.h"
#include "SYSTICK.h"
#include "usart.h"
#include "i2c.h"
#include <stdio.h>
#include "MyLCD.h"
#include "ADC.h"
#include "Alarm.h"
#include "DHT12.h"

const unsigned char  *point;//���岻�ɸı��ָ��
unsigned char ACK=0;
extern unsigned char  picture_tab[];//��ģ��Ϣ
extern unsigned char F16x16[];
extern unsigned char BMP1[];
unsigned char temp_string[]="Hello everyone!"; 
unsigned char air_string[]="AQI"; 
unsigned char maohao_string[]=":"; 

int main(void)
{
	uint16_t Temp_Value;
	float ADC_Value=0.00;
	char strTemp[20];
	unsigned int i=0;
    SYSTICK_Init();			//ϵͳ��ʼ��
    USART1_Config();//PA9  TX     PA10     RX		������9600
    //LED_GPIO_Config();	
    I2C_Configuration();	//IIC��ʼ������   SCL����PB7    SDA����PB8
	ADC_Configuration();	//ADC����   PA0
	Alarm_Configuration();		//����������
	//IIC_Init();
	sensor_iic_init();//DHT12_IIC��ʼ��
	
	//OLED������ʾ
	point= &picture_tab[0];
	OLED_init();
    OLED_full();
	delay_ms(1000);
	OLED_clear();//����
	
    while (1)
    {	
		Temp_Value = ADC_GetConversionValue(ADC1);		//��ȼ������
		ADC_Value = (3.3/4096)*Temp_Value;			 /*��ADֵת��Ϊ��ѹֵ*/
		printf("\r\n ����һ�������������ϵͳ \r\n");
		sprintf(strTemp, "%.1f", 100*ADC_Value);     //���3.30V����˼��ת��Ϊ�ַ���
		if(Temp_Value>3000)
			{
				Alarm_H;			//����⵽�ĵ�ѹֵ����3/4���ֵ����������������
			}
			
		//Picture_display(point);//	�䱾����һ��ͼƬ
		
		OLED_ShowStr(0,0,temp_string,2);
		OLED_ShowStr(0,2,air_string,2);
		OLED_ShowStr(56,2,maohao_string,2);
		OLED_ShowStr(64,2,strTemp,2);
		for(i=0;i<2;i++)
		{
			OLED_ShowCN(24+i*16,2,i); //������ʾ 
		}
		
		sensor_read();//��ȡ��ʪ������		
		printf("The Temp_Value is %d \r\n",Temp_Value);
        printf("The AQI_ Value is %f \r\n",100*ADC_Value);
		
		//OLED_DrawBMP(0,0,127,7,BMP1);
		delay_ms(1000);	
		//Alarm_L;
		//OLED_clear();//����
		//Picture_ReverseDisplay(point);//ͼƬ��ɫ��ʾ
		//delay_ms(1000);
		//OLED_OFF(); 
		//if(i%5==0)
		{
		//	OLED_ON();
		}
    }
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





