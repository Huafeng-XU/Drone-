/*********************************************************************************
JJ_fly by TIVA
�ļ�����mpu6050.h
������mpu6050���ݶ�ȡ�봦���ο������ɰ����
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "driverlib/rom.h"
#include "driverlib/fpu.h"

#define SMPLRT_DIV	0x19	//�����ǲ�����
#define	 CONFIG		0x1A	//��ͨ�˲�Ƶ��
#define	 GYRO_CONFIG	0x1B	//�������Լ켰������Χ
#define	 ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ��
#define	 ACCEL_XOUT_H	0x3B    //���ٶ�
#define	 ACCEL_XOUT_L	0x3C
#define ACCEL_YOUT_H	0x3D
#define ACCEL_YOUT_L	0x3E
#define ACCEL_ZOUT_H	0x3F
#define	 ACCEL_ZOUT_L	0x40
#define	 TEMP_OUT_H	    0x41
#define	 TEMP_OUT_L	    0x42
#define	 GYRO_XOUT_H	0x43    //���ٶ�
#define	 GYRO_XOUT_L	0x44
#define	 GYRO_YOUT_H	0x45
#define	 GYRO_YOUT_L	0x46
#define	 GYRO_ZOUT_H	0x47
#define	 GYRO_ZOUT_L	0x48
#define	 PWR_MGMT_1	0x6B	//��Դ����
#define WHO_AM_I 0x75

#define RtA 		57.324841f		//  180/3.1415  �Ƕ��� ת��Ϊ������
#define AtR    	0.0174533f		//  1/RtA             RtA����
#define Acc_G 	0.0011963f		//  1/32768/4/9.8     ���ٶ�����Ϊ4G
//#define Gyro_G 	0.0610351/2				//���ٶȱ�ɶ�   �˲�����Ӧ����1000��ÿ��
//#define Gyro_Gr	0.0010653/2				//���ٶȱ�ɻ���	�˲�����Ӧ����1000��ÿ��
#define Gyro_G 	0.01525878f	//  1/32768/1000      ����������Ϊ +��1000
#define Gyro_Gr	0.0002663f   //  1/32768/1000/57.3
#define FILTER_NUM 10//�����˲�����

void mpu6050_init();
void MPU6050_ZERO(void);
void Prepare_Data(void);
void MPU6050_Dataanl(void);

//�����Ǽ��ٶȼƵĲ�����
extern int ACC_OFFSET_X,ACC_OFFSET_Y,ACC_OFFSET_Z;
extern int GYRO_OFFSET_X,GYRO_OFFSET_Y,GYRO_OFFSET_Z;
//�����Ǽ��ٶȼ�ʵʱֵ��������
extern int MPU6050_ACC_LAST_X,MPU6050_ACC_LAST_Y,MPU6050_ACC_LAST_Z;
extern int MPU6050_GYRO_LAST_X,MPU6050_GYRO_LAST_Y,MPU6050_GYRO_LAST_Z;
//�����Ǽ��ٶȼƻ��������˲�����
extern int ACC_X_BUF[FILTER_NUM],ACC_Y_BUF[FILTER_NUM],ACC_Z_BUF[FILTER_NUM];
extern int GYRO_X_BUF[FILTER_NUM],GYRO_Y_BUF[FILTER_NUM],GYRO_Z_BUF[FILTER_NUM];
//�����Ǽ��ٶȼ�ƽ��ֵ�˲����ֵ
extern int   ACC_AVG_X,ACC_AVG_Y,ACC_AVG_Z;
extern int   GYRO_AVG_X,GYRO_AVG_Y,GYRO_AVG_Z;
//�����ǻ���ֵ
extern float GYRO_I_X,GYRO_I_Y,GYRO_I_Z;

#endif /* MPU6050_H_ */
