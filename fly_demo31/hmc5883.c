/*********************************************************************************
JJ_fly by TIVA
�ļ�����hmc5883.c
������hmc5883���ݶ�ȡ�봦��
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#include "hmc5883.h"
#include "IIC.h"
#include "mpu6050.h"
int hmc5883_x,hmc5883_y,hmc5883_z;//�ų���ʼֵ
int HMC_AVG_X,HMC_AVG_Y,HMC_AVG_Z;//ƽ��ֵ�˲���Ĵ���ֵ
int HMC_X_BUF[FILTER_NUM],HMC_Y_BUF[FILTER_NUM],HMC_Z_BUF[FILTER_NUM];//�����ƻ����˲�����

void hmc5883_init()//��ʼ��������
{
	SLAVE_ADDRESS=0x1E;
	i2c_write(0x00,0x18);//��������ģʽ�������������75hz���޲���ƽ��
    i2c_write(0x01, 0x20);//����ѡ��
    i2c_write(0x02,0x00);//��������ģʽ
}
void hmc5883_read()//��ȡ����������
{
	long int temp1=0,temp2=0,temp3=0;
	static unsigned char filter_cnt_=0;
	unsigned char i;
	SLAVE_ADDRESS=0x1E;

	hmc5883_x=Get16Bit(0x03);//��ȡ���ᴫ�����ų�ֵ
	hmc5883_y=Get16Bit(0x05);
	hmc5883_z=Get16Bit(0x07);

	HMC_X_BUF[filter_cnt_] = hmc5883_x;//���»�����������
	HMC_Y_BUF[filter_cnt_] = hmc5883_y;
	HMC_Z_BUF[filter_cnt_] = hmc5883_z;

	for(i=0;i<FILTER_NUM;i++)
	{
	  temp1 += HMC_X_BUF[i];
	  temp2 += HMC_Y_BUF[i];
	  temp3 += HMC_Z_BUF[i];
	}

	HMC_AVG_X = temp1 / FILTER_NUM;
	HMC_AVG_Y = temp2 / FILTER_NUM;
	HMC_AVG_Z = temp3 / FILTER_NUM;

	filter_cnt_++;
	if(filter_cnt_==FILTER_NUM)
	{
		filter_cnt_=0;
	}
}
