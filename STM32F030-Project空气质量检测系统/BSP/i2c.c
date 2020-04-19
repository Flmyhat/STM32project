/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��i2c.c
 * ����    ����ʼ��IIC��һЩ�����Ĳ���
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-12-20
 * Ӳ������: SCL--PF6,SDA--PF7 
 * ���Է�ʽ��J-Link-OB
******************************************************************************/	

//ͷ�ļ�
#include "SYSTICK.h"
#include "i2c.h"
#include "usart.h"
#include "string.h"



 /**
  * @file   I2C_Configuration
  * @brief  EEPROM�ܽ�����
  * @param  ��
  * @retval ��
  */
void I2C_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	/* Configure I2C2 pins: PB6->SCL and PB7->SDA */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);//����GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;//PB7   SCL
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ��ѡ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;//PB8  SDA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	//SDA_H;//PB8����
	//SCL_H;//PB9����
}


/**************************IICģ�鷢�ͺ���************************************************

 *************************************************************************/
//д��  ���SDA���ߣ��Եȴ����豸����Ӧ��
void IIC_write(unsigned char date)
{
	unsigned char i, temp;
	temp = date;
			
	for(i=0; i<8; i++)
	{	IIC_SCK_0;
		
        if ((temp&0x80)==0)
            IIC_SDA_0;
        else IIC_SDA_1;
		temp = temp << 1;
		delay_us(1);			  
		IIC_SCK_1;
		delay_us(1);
		
	}
	IIC_SCK_0;
	delay_us(1);
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
//								����ҪӦ��
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}

//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //���в��������ͷ�SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
    IIC_write(0x78);
        
}

//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
void IIC_stop()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
}

