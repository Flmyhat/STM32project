//****************************************************************//
//DHT12 IIC���ݶ�ȡ����
// ��˾��    ���ɵ���
//****************************************************************//

#include "DHT12.h"

float Temprature,Humi;//������ʪ�ȱ��� ���˱���Ϊȫ�ֱ���


/********************************************\
|* ���ܣ� DHT12_IIC��ʼ������	        *|
\********************************************/
void sensor_iic_init(void)
{
	IIC_Init();
}


/********************************************\
|* ���ܣ�DHT12��ȡ��ʪ�Ⱥ���       *|
\********************************************/
//������Humi_H��ʪ�ȸ�λ��Humi_L��ʪ�ȵ�λ��Temp_H���¶ȸ�λ��Temp_L���¶ȵ�λ��Temp_CAL��У��λ
//���ݸ�ʽΪ��ʪ�ȸ�λ��ʪ��������+ʪ�ȵ�λ��ʪ��С����+�¶ȸ�λ���¶�������+�¶ȵ�λ���¶�С����+ У��λ
//У�飺У��λ=ʪ�ȸ�λ+ʪ�ȵ�λ+�¶ȸ�λ+�¶ȵ�λ
void sensor_read(void)
{	
	char string_Temprature[20];
	char string_Humi[20];
	unsigned char error1[]=" CRC Error !! ";
	unsigned char error2[]=" Sensor Error !!";
	uint16_t i;
	uint8_t Humi_H,Humi_L,Temp_H,Temp_L,Temp_CAL,temp;

	IIC_Start();    //����������ʼ�ź�
	IIC_Send_Byte(0Xb8);    //����IIC��ַ
	if(!IIC_Wait_Ack())  //�ȴ��ӻ�Ӧ���źţ�����Ӧ�𣺿���IICͨѶƵ���Ƿ�̫�죬���ߴ��������ߴ���
	{
		i=0;
		IIC_Send_Byte(0);
		while(IIC_Wait_Ack())//�ȴ��ӻ�Ӧ���ź�
		{
		 	if(++i>=500)
			{
			 	break;
			}		 
		} 
		i=0;
		IIC_Start();       //����������ʼ�ź�
		IIC_Send_Byte(0Xb9);     //���Ͷ�ָ��
		while(IIC_Wait_Ack())    //�ȴ��ӻ�Ӧ���ź�
		{
		 	if(++i>=500)
			{
			 	break;
			}			 
		}
	
		Humi_H=IIC_Read_Byte(1);   //��ȡʪ�ȸ�λ
		Humi_L=IIC_Read_Byte(1);   //��ȡʪ�ȵ�λ
		Temp_H=IIC_Read_Byte(1);   //��ȡ�¶ȸ�λ
		Temp_L=IIC_Read_Byte(1);   //��ȡ�¶ȵ�λ
		Temp_CAL=IIC_Read_Byte(0); //��ȡУ��λ
		IIC_Stop();	   //����ֹͣ�ź�	
		temp = (uint8_t)(Humi_H+Humi_L+Temp_H+Temp_L);//ֻȡ��8λ
		if(Temp_CAL==temp)//���У��ɹ�����������
		{
			Humi=Humi_H*10+Humi_L; //ʪ��
	
			if(Temp_L&0X80)	//Ϊ���¶�
			{
				Temprature =0-(Temp_H*10+((Temp_L&0x7F)));
			}
			else   //Ϊ���¶�
			{
				Temprature=Temp_H*10+Temp_L;//Ϊ���¶�
			} 	
			//�ж���ʪ���Ƿ񳬹�������Χ���¶ȣ�-20��~60���϶ȣ�ʪ�ȣ�20%RH~95%RH��		
			if(Humi>950) 
			{
			  Humi=950;
			}
			if(Humi<200)
			{
				Humi =200;
			}
			if(Temprature>600)
			{
			  Temprature=600;
			}
			if(Temprature<-200)
			{
				Temprature = -200;
			}
			Temprature=Temprature/10;//����Ϊ�¶�ֵ
			Humi=Humi/10; //����Ϊʪ��ֵ
			printf("��ǰ�¶�Ϊ:  %.1f  ��\r\n",Temprature); //��ʾ�¶�
			printf("��ǰʪ��Ϊ:  %.1f  %%RH\r\n",Humi);//��ʾʪ��
			
			sprintf(string_Temprature, "%.1f ", Temprature);     //��˼��ת��Ϊ�ַ���
			sprintf(string_Humi, "%.1f %%RH", Temprature); 
			
			OLED_ShowStr(40,4,string_Temprature,2);
			OLED_ShowStr(40,6,string_Humi,2);
			
//			OLED_ShowCN(0,4,5);//��
//			OLED_ShowCN(16,4,6);//ǰ
//			OLED_ShowCN(0,6,5);//��
//			OLED_ShowCN(16,6,6);//ǰ
			OLED_ShowCN(0,4,2); //��
			OLED_ShowCN(16,4,4); //��
			OLED_ShowCN(0,6,3); //ʪ
			OLED_ShowCN(16,6,4); //��
			OLED_ShowCN(80,4,5); //��
			OLED_ShowStr(32,4,maohao_string,2);
			OLED_ShowStr(32,6,maohao_string,2);
			
		}
		else //У��ʧ��
		{
			printf("CRC Error !!\r\n");
			OLED_ShowStr(0,4,error1,2);
			OLED_ShowStr(0,6,error1,2);
		}
	}else
	{
	   printf("Sensor Error !!\r\n");
	   OLED_ShowStr(0,4,error2,2);
	   OLED_ShowStr(0,6,error2,2);
	}	

}



