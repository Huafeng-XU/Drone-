/*********************************************************************************
JJ_fly by TIVA
�ļ�����imu_new.h
��������̬�������հ�
���ߣ�¬���
ʱ�䣺2015.11
**********************************************************************************/

#ifndef IMU_NEW_H_
#define IMU_NEW_H_
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符�?位整型变�? */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符�?位整型变�? */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符�?6位整型变�?*/
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符�?6位整型变�?*/
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符�?2位整型变�?*/
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符�?2位整型变�?*/
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数�?2位长度） */
typedef double         fp64;
#define RtA 		57.324841f		//  180/3.1415
#define AtR    	0.0174533f		//  1/RtA
#define Acc_G 	0.0011963f		//  1/32768/4/9.8
//#define Gyro_G 	0.03051756f/2f	//  1/32768/1000/2
//#define Gyro_Gr	0.0005326f/2f   //  1/32768/1000/57.3

extern float Az;
extern float Q_ANGLE_X,Q_ANGLE_Y,Q_ANGLE_Z;      //��Ԫ��������ĽǶ�
extern float Q_ANGLE_Xr,Q_ANGLE_Yr;
extern float Gx,Gy,Gz;
void Get_Attitude();
#endif /* IMU_NEW_H_ */
