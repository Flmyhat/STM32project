//****************************************************************//
//ģ��IIC���ó���
//ע�⣺DHT12��IIC��ͨѶƵ�ʲ��ó���50KHZ
// ��˾��    ���ɵ���
//****************************************************************//

#include "myiic.h"

//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_AHBPeriph_GPIOB, ENABLE );//ʹ��GPIOB	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;//PB13,PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//��©
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14); 	//PB13,PB14 �����
}

void SDA_MODE_IN(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//��y??????
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��?��??�꨺?
GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOB, &GPIO_InitStructure);//3?��??��????
}

void SDA_MODE_OUT(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//��y??????
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��?3??�꨺?
GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//2?��?��?��-��?����
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//��?3??��?��
GPIO_Init(GPIOB, &GPIO_InitStructure);//3?��??��????
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_MODE_OUT();     //sda�����
	set_SDA;	  	  
	set_SCL;
	delay_us(14);
 	clr_SDA;//��ʼ����SCLΪ��ʱ�����ݴӸߵ��ͱ仯
	delay_us(14);
	clr_SCL;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_MODE_OUT();//sda�����
	clr_SCL;
	clr_SDA;//ֹͣ:��SCLΪ��ʱ�����ݴӵ͵��߱仯
 	delay_us(14);
	set_SCL;
	delay_us(14);	 
	set_SDA;//����I2C���߽����ź�
							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	clr_SCL;
	set_SDA;
	SDA_MODE_IN();      //SDA����Ϊ����  
	delay_us(14);	   
	set_SCL;
	delay_us(14);	 
	while(read_SDA)//�ȵ�SDA���
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
		delay_us(1);
	}
	clr_SCL;//ʱ�����0
	delay_us(10); 
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	clr_SCL;
	SDA_MODE_OUT();
	clr_SDA;
	delay_us(15);
	set_SCL;
	delay_us(15);
	clr_SCL;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	clr_SCL;
	SDA_MODE_OUT();
	set_SDA;
	delay_us(15);
	set_SCL;
	delay_us(15);
	clr_SCL;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_MODE_OUT(); 	    
    clr_SCL;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
		clr_SCL;
		if((txd&0x80)>>7)
			set_SDA;
		else
			clr_SDA;
		txd<<=1; 	  
		delay_us(15);   //��ʱ
		set_SCL;
		delay_us(15); 	
    }
	clr_SCL;	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_MODE_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        clr_SCL; 
        delay_us(50);
		set_SCL;
		delay_us(50);
        receive<<=1;
        if(read_SDA)receive++;   
    }
        clr_SCL;						 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



























