/**********************************************************************************
** 实验名：读写eeprom
** 使用编译环境：MDK4.72A / MDK5.15 
** 固件库(ST) Version: STM32F0xx_StdPeriph_Driver V1.3.0
** 使用外设: 
**********************************************************************************/	   
测试说明：
编译并下载程序。

测试结果：
下载完程序后，主要是完成对EEPROM的写操作和读操作，即将写进eeprom的数据在读取出来，并显示在串口调试助手（9600-n8-1）的窗口界面上。

硬件连接：
LED灯：
	D1->PC13
	D2->PB0
	D4->PB1


USART1：
	TX->PA9
	RX->PA10
I2C:
	I2C1_SCL->PF6
	I2C1_SDA->PF7


淘宝购买：http://vcc-gnd.taobao.com
源地工作室：http://www.vcc-gnd.com
