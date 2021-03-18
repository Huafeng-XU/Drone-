/*********************************************************************************
JJ_fly by TIVA
�ļ�����IIC.c
������Ӳ��IIC
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#include "IIC.h"
unsigned char SLAVE_ADDRESS;
void i2c_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);// ʹ��I2C2ģ���ʱ���ź�
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//������ʹ��

	GPIOPinConfigure(GPIO_PA6_I2C1SCL);
	GPIOPinConfigure(GPIO_PA7_I2C1SDA);// ��PB2�Ĺ���ѡ��ΪI2C2ģ���ʱ���źţ���PB3ѡ��Ϊ�����ź�

    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);// ��PB2��PB3�����������й�I2C���ܵ�����

    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet()/2, true);

    I2CMasterEnable(I2C1_BASE);
}
unsigned char i2c_write(unsigned char reg_addr,unsigned char data)//IICд�Ĵ���
{
    //����I2C2��ģ�齫Ҫ���������ϵĴ�ģ���ַ
    //false������ģ�鷢�ͣ���ģ�����
	I2CMasterSlaveAddrSet(I2C1_BASE,SLAVE_ADDRESS, false);
	I2CMasterDataPut(I2C1_BASE, reg_addr);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C1_BASE));
	// ��ģ�鿪ʼ���ͼĴ�����ַ
	I2CMasterDataPut(I2C1_BASE, data);
	// ��ģ�鿪ʼ��������
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
	while(I2CMasterBusy(I2C1_BASE));
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_STOP);
	while(I2CMasterBusy(I2C1_BASE));
	/*I2CMasterDataPut(I2C2_BASE, data);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C2_BASE));*/
	return 0;
}
unsigned char i2c_read(unsigned char reg_addr)//IIC���Ĵ���
{
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, false);
    I2CMasterDataPut(I2C1_BASE, reg_addr);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C1_BASE));
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(I2C1_BASE));
    return I2CMasterDataGet(I2C1_BASE);
}
int Get16Bit(unsigned char reg_addr)
{
	  unsigned char ho,lo;
	  int temp;
	  ho = i2c_read(reg_addr);
	  lo = i2c_read(reg_addr+1);
	  temp=(ho<<8)+lo;
	  if(temp>=32768)
		  return -1*(65536-temp);
	  else
		  return temp;
}
