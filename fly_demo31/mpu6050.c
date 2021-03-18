/*********************************************************************************
JJ_fly by TIVA
�ļ�����mpu6050.c
������mpu6050���ݶ�ȡ�봦���ο������ɰ����
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#include "mpu6050.h"
#include "IIC.h"
#include "math.h"
#include "display_oled.h"
#include "hmc5883.h"
#include "init.h"
//�����Ǽ��ٶȼƵĲ�����
int ACC_OFFSET_X,ACC_OFFSET_Y,ACC_OFFSET_Z;
int GYRO_OFFSET_X,GYRO_OFFSET_Y,GYRO_OFFSET_Z;
//�����Ǽ��ٶȼ�ʵʱֵ��������
int MPU6050_ACC_LAST_X,MPU6050_ACC_LAST_Y,MPU6050_ACC_LAST_Z;
int MPU6050_GYRO_LAST_X,MPU6050_GYRO_LAST_Y,MPU6050_GYRO_LAST_Z;
//�����Ǽ��ٶȼƻ��������˲�����
int ACC_X_BUF[FILTER_NUM],ACC_Y_BUF[FILTER_NUM],ACC_Z_BUF[FILTER_NUM];
int GYRO_X_BUF[FILTER_NUM],GYRO_Y_BUF[FILTER_NUM],GYRO_Z_BUF[FILTER_NUM];
//�����Ǽ��ٶȼ�ƽ��ֵ�˲����ֵ
int   ACC_AVG_X,ACC_AVG_Y,ACC_AVG_Z;
int   GYRO_AVG_X,GYRO_AVG_Y,GYRO_AVG_Z;
//�����ǻ���ֵ
float GYRO_I_X,GYRO_I_Y,GYRO_I_Z;



void mpu6050_delay()//����ʱ
{
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
    SysCtlDelay(10000);
}
void mpu6050_init()
{
	SLAVE_ADDRESS=0x68;
	i2c_write(PWR_MGMT_1,0x00);//����mpu6050
    i2c_write(SMPLRT_DIV, 0x00);//���ò�����Ϊ500hz����Ϊ���濪�˵�ͨ�˲���������Ƶ��Ϊ1khz��1k/(1+1)=500hz
    SysCtlDelay(1000);
    i2c_write(CONFIG, 0x00);//04hz��ͨ�˲�
    SysCtlDelay(1000);
    i2c_write(CONFIG, 0x04);//40hz��ͨ�˲�
    SysCtlDelay(1000);
    i2c_write(GYRO_CONFIG, 0x08);//����������+-1000��/�룬���Լ�
    i2c_write(ACCEL_CONFIG, 0x08);//���ٶȼ�����+-8g�����Լ�
    mpu6050_delay();//����ʱ���ȴ�6050�����ȶ�����ȡ���
    //MPU6050_ZERO();//mpu6050ȡ���
}
void MPU6050_ZERO(void)//mpu6050ȡ������
{
	unsigned char i;
	unsigned char num=20;
	long int temp_1=0,temp_2=0,temp_3=0;//,temp_4=0,temp_5=0,temp_6=0;
	//������ֱ��У׼�����ٶȼ�Z��ע��У׼�������ٶ�
	for(i=0;i<num;i++)
	{
		temp_1+=Get16Bit(GYRO_XOUT_H);
		temp_2+=Get16Bit(GYRO_YOUT_H);
		temp_3+=Get16Bit(GYRO_ZOUT_H);
		//temp_4+=Get16Bit(ACCEL_XOUT_H);
		//temp_5+=Get16Bit(ACCEL_YOUT_H);
		//temp_6+=Get16Bit(ACCEL_ZOUT_H)-65536/8;//����Ϊ+-4g
	}
	GYRO_OFFSET_X=(int)temp_1/num;
	GYRO_OFFSET_Y=(int)temp_2/num;
	GYRO_OFFSET_Z=(int)temp_3/num;
	//ACC_OFFSET_X=temp_4/num;
	//ACC_OFFSET_Y=temp_5/num;
	//ACC_OFFSET_Z=temp_6/num;
}
void MPU6050_Dataanl(void)//�õ�mpu6050���ݲ���ȥ������
{
  SLAVE_ADDRESS=0x68;
  MPU6050_ACC_LAST_X = Get16Bit(ACCEL_XOUT_H);
  MPU6050_ACC_LAST_Y = Get16Bit(ACCEL_YOUT_H);
  MPU6050_ACC_LAST_Z = Get16Bit(ACCEL_ZOUT_H);

  MPU6050_GYRO_LAST_X = Get16Bit(GYRO_XOUT_H) - GYRO_OFFSET_X;
  MPU6050_GYRO_LAST_Y = Get16Bit(GYRO_YOUT_H) - GYRO_OFFSET_Y;
  MPU6050_GYRO_LAST_Z = Get16Bit(GYRO_ZOUT_H) - GYRO_OFFSET_Z+5;
}
void Prepare_Data(void)//��ȡMPU6050���ݽ���ƽ���˲���Ϊ��������׼������
{
  static unsigned char filter_cnt=0;
  long int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;
  unsigned char i;
  MPU6050_Dataanl();//��ɴ��������ݵĶ�ȡ�ͼ���
  ACC_X_BUF[filter_cnt] = MPU6050_ACC_LAST_X;//���»�����������
  ACC_Y_BUF[filter_cnt] = MPU6050_ACC_LAST_Y;
  ACC_Z_BUF[filter_cnt] = MPU6050_ACC_LAST_Z;
  GYRO_X_BUF[filter_cnt] = MPU6050_GYRO_LAST_X;
  GYRO_Y_BUF[filter_cnt] = MPU6050_GYRO_LAST_Y;
  GYRO_Z_BUF[filter_cnt] = MPU6050_GYRO_LAST_Z;
  for(i=0;i<FILTER_NUM;i++)
  {
    temp1 += ACC_X_BUF[i];
    temp2 += ACC_Y_BUF[i];
    temp3 += ACC_Z_BUF[i];
    temp4 += GYRO_X_BUF[i];
    temp5 += GYRO_Y_BUF[i];
    temp6 += GYRO_Z_BUF[i];
  }
  ACC_AVG_X = temp1 / FILTER_NUM;
  ACC_AVG_Y = temp2 / FILTER_NUM;
  ACC_AVG_Z = temp3 / FILTER_NUM;
  GYRO_AVG_X = temp4 / FILTER_NUM;
  GYRO_AVG_Y = temp5 / FILTER_NUM;
  GYRO_AVG_Z = temp6 / FILTER_NUM;
  /*if(check_end==1)
  {
	  if(GYRO_AVG_X<10&&GYRO_AVG_X>-10)
		  GYRO_AVG_X=0;
	  if(GYRO_AVG_Y<10&&GYRO_AVG_Y>-10)
		  GYRO_AVG_Y=0;
	  if(GYRO_AVG_Z<10&&GYRO_AVG_Z>-10)
		  GYRO_AVG_Z=0;
  }*/

  filter_cnt++;
  if(filter_cnt==FILTER_NUM)
  {
	  filter_cnt=0;
  }
  //MPU6050_GYRO_LAST_Z=-1*MPU6050_GYRO_LAST_Z;
  //�����ǻ��֣�û�д����������������yawֵ�������ǻ��ֵõ�
  GYRO_I_Z += (MPU6050_GYRO_LAST_Z*Gyro_G*0.0025f);
}
