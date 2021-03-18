/*********************************************************************************
JJ_fly by TIVA
�ļ�����init.c
��������ʼ�����Լ����
���ߣ�¬���
ʱ�䣺2015.11
**********************************************************************************/
#include "display_oled.h"
#include "IIC.h"
#include "mpu6050.h"
#include "uarts.h"
#include "timers.h"
#include "hmc5883.h"
#include "nrf2401.h"
#include "capture.h"
#include "PWM.h"
#include "control.h"
#include "init.h"
#include "imu_new.h"
#include "mymath.h"
#include "US100.h"
#include "flow.h"
unsigned char _time_flag_1;
unsigned char _time_flag_2;
int check_count=100;
int check_count2=400;
int check_end;
int check_aspeed_end;
int yaw_check,yaw_check_old;
long int offset_gyro_z,offset_gyro_y,offset_gyro_x;
long int offset_acc_z,offset_acc_y,offset_acc_x;
float G;
void all_init()
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);//�ⲿ16M����
	init_first();//�Լ�ǰ��ʼ��
	check();//�Լ�
	init_last();//�Լ���ʼ��
}
void init_first()//�Լ�ǰ��ʼ��
{
	capture_init();//��ʼ������ʱ�����������ң������
	uart_init();//��ʼ������
	i2c_init();//��ʼ��Ӳ��IIC
	pwm_init();//pwm��ʼ��
	mpu6050_init();//��ʼ��mpu6050
	US_100_init();//��ʼ��������
	while(i2c_read(WHO_AM_I)!=0x68);//У��6050��ַ
}
void init_last()//�Լ���ʼ��
{
	control_init();//pid������ʼ��
	timer_init();//��ʼ������ʱ���������������
	//flow_init();
	k60_init();
}
void check()//�Լ�
{
	//����ͨ�����У��Լ쿪�ش�
	while(CH_3>CH_3_TEST+5||CH_3<CH_3_TEST-5)//�������ش��м䣬�ݴ�10
	{
		get_rc_value();//��ȡң����
	}
	//�Լ춨ʱ����
	delay_ms(100);
	check_start();
	//����ֵ���㣬����ҡ�˻���,�ݴ�10
	while(CH_1<CH_1_MIN-5||CH_1>CH_1_MIN+5||CH_2<CH_2_MID-5|| CH_2>CH_2_MID+5||CH_5<CH_5_MID-5||CH_5>CH_5_MID+5||CH_6<CH_6_MID-5||CH_6>CH_6_MID+5)
	{
		get_rc_value();//��ȡң����
	}
	//�ȴ��Լ����
	while(check_end != 1);
}

void check_6050_offest()//6050�Լ첹�����ݴ���
{
	check_count--;//�Լ����-1
	//////////////////���yawƯ�Ʋ�����//////////////////
	offset_gyro_z += MPU6050_GYRO_LAST_Z;
	offset_gyro_y += MPU6050_GYRO_LAST_Y;
	offset_gyro_x += MPU6050_GYRO_LAST_X;
	offset_acc_z += MPU6050_ACC_LAST_Z;
	offset_acc_y += MPU6050_ACC_LAST_Y;
	offset_acc_x += MPU6050_ACC_LAST_X;
	if(check_count==0)//���ٶ��Լ����
	{
		GYRO_OFFSET_Z = offset_gyro_z / 100;//���z����
		GYRO_OFFSET_Y = offset_gyro_y / 100;//���y����
		GYRO_OFFSET_X = offset_gyro_x / 100;//���x����
		ACC_OFFSET_Z = offset_acc_z / 100;
		ACC_OFFSET_Y = offset_acc_y / 100;
		ACC_OFFSET_X = offset_acc_x / 100;
		G= my_sqrt(ACC_OFFSET_X*ACC_OFFSET_X + ACC_OFFSET_Y*ACC_OFFSET_Y + ACC_OFFSET_Z*ACC_OFFSET_Z);;
		check_aspeed_end = 1;//��־λ
		//�ر��Լ춨ʱ��
		//TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	}
}
void check_angle_offest()//�Ƕ��Լ첹�����ݴ���
{
	if(check_aspeed_end == 1)//ȷ�����ٶ�У׼���
	{
		check_count2--;//�Լ����-1
		if(check_count2<100)
		{
			//////////////////�Ƕ�ȥ���//////////////////
			offset_angle_x += Q_ANGLE_X;
			offset_angle_y += Q_ANGLE_Y;
			if(check_count2==0)//�Ƕ��Լ����
			{
				offset_angle_y = offset_angle_y / 100;//���y����
				offset_angle_x = offset_angle_x / 100;//���x����
				check_end = 1;//��־λ
				//�ر��Լ춨ʱ��
				TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
			}
		}

	}
}
void check_start()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//ʹ��TIMER0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC);//�����Լ���ģʽ
	TimerLoadSet(TIMER0_BASE, TIMER_B,SysCtlClockGet() / 400 - 1);//����Ƶ��400HZ
	IntEnable(INT_TIMER0B_SNOWFLAKE);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);//TIMEOUT��־λ�����ж�
    IntMasterEnable();//���ж�
    TimerEnable(TIMER0_BASE, TIMER_B);//TIMER0A��ʼ������������ֵ����TimerLoadSet�������ж�
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
void Timer0BIntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);//�����־λ
    _time_flag_1++;//ʱ���־1
    //////////////2.5ms����//////////////////
    Prepare_Data();//��̬���������ݶ�ȡ���򵥴���
    get_rc_value();//��ȡң����
    /////////////////////////////////////
    if(_time_flag_1==2)
    {
    	_time_flag_1=0;
        //////////////5ms����//////////////////
    	Get_Attitude();//������̬����
    	check_6050_offest();
    	check_angle_offest();
        ///////////////////////////////////
    }
}

