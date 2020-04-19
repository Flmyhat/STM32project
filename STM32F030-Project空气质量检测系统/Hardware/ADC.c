/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��ADC.c
 * ����    ��ADC1�����ļ�
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-12-20
 * Ӳ������  :PC3	
 * ���Է�ʽ��J-Link-OB
********************************************************************************/
#include "ADC.h"

 uint16_t RegularConvData;
 
 /**
  * @file   ADC_Configuration
  * @brief  ���ADC��DMA�ĳ�ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
   
	ADC_StructInit(&ADC_InitStructure);//��ʼ��ADC�ṹ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λ����
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //�涨ģʽװ������������ģʽ
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; 
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//���ݶ���Ϊ�Ҷ���
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward; //ADC��ɨ�跽��
  ADC_Init(ADC1, &ADC_InitStructure); 

    /* Convert the ADC1 Channel 0 with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SampleTime_55_5Cycles);//ADC_SampleTime_55_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); /* Wait the ADCEN falg */
  ADC_StartOfConversion(ADC1); /* ADC1 regular Software Start Conv */ 
}


