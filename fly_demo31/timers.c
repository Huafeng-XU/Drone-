/*********************************************************************************
JJ_fly by TIVA
�ļ�����timers.c
�������������
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#include "timers.h"
#include "mpu6050.h"
#include "nrf2401.h"
#include "imu_new.h"
#include "hmc5883.h"
#include "capture.h"
#include "control.h"
#include "US100.h"
#include "flow.h"
unsigned char flag=0;
unsigned char time_flag_1=0;
unsigned char time_flag_2=0;
unsigned char time_flag_3=0;
unsigned char time_flag_4=0;
unsigned char time_flag_5=0;
unsigned char UART_Send_flag=0;
unsigned char height_ready;
unsigned char height_control;

unsigned char game_count;
unsigned char error_flag1;
unsigned char game_time_1;
void game();
//��ʱ����ʼ����ʹ��timer0A����������������ж�
void timer_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//ʹ��TIMER0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);//�����Լ���ģʽ
	TimerLoadSet(TIMER0_BASE, TIMER_A,SysCtlClockGet() / 400 - 1);//����Ƶ��400HZ
	IntEnable(INT_TIMER0A_SNOWFLAKE);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//TIMEOUT��־λ�����ж�
    IntMasterEnable();//���ж�
    TimerEnable(TIMER0_BASE, TIMER_A);//TIMER0A��ʼ������������ֵ����TimerLoadSet�������ж�
    game_count=0;
}
//timer0�жϴ�������2.5ms����һ��
void Timer0AIntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//�����־λ
    time_flag_1++;//ʱ���־1
    time_flag_2++;//ʱ���־2
    time_flag_3++;//ʱ���־3
    time_flag_4++;//ʱ���־4
    time_flag_5++;//ʱ���־5
    //////////////2.5ms����//////////////////
    get_rc_value();
    Prepare_Data();//��̬���������ݶ�ȡ���򵥴���
    //hmc5883_read();
    //SPI_Write_register(WRITE_REG+STATUS,0xff);//���nrf2401��״̬�Ĵ�����׼����һ�η���
    /////////////////////////////////////
    if(time_flag_1==2)
    {
    	time_flag_1=0;
        //////////////5ms����//////////////////
    	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
    	Get_Attitude();//������̬����
    	control();
    	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0xff);
        ///////////////////////////////////
    }
    if(time_flag_2==3)
    {
    	time_flag_2=0;
        //////////////7.5ms����//////////////////
    	UART_Send_flag++;//�������ݷ��ͱ�־λ
    	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
    	//nrf2401_send_RCData();
    	//nrf2401_send_RCData();
	    //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0xff);
        //SysCtlDelay(10000);
        //SPI_Write_register(WRITE_REG+STATUS,0xff);
        ///////////////////////////////////
    }
    if(time_flag_3==15)//30ms����
    {
    	if(height_ready==0)
    	{
    		US_100_trig();
    		height_ready=1;
    	}
    	else if(height_ready==1)
    	{
    		US_100_get();
    		height_ready=0;
    		height_control++;
    		if(height_control==2)
    		{
    			height_control=0;
    			control_height();
    		}
    	}
    	time_flag_3=0;
    }
    if(time_flag_4==80)//100ms����
    {
    	game();
    	control_point_1();
    	time_flag_4=0;
    }
    if(time_flag_5==120)//500ms����
    {
    	land();
    	time_flag_5=0;
    }
}
void game()
{
	if(game_count==0)
	{
		if(fly_low==1)
		{
			game_time_1++;
			if(game_time_1==50)
			{
				game_count=1;
				game_time_1=0;
			}
		}
	}
	else if(game_count==1)
	{
		if(X1!=0&&Y1==0)
		{
			error_flag1++;
		}
		if(error_flag1==1)
		{
			game_count=2;
			error_flag1=0;
		}
	}
	else if(game_count==2)
	{
		game_time_1++;
		if(game_time_1==50)
		{
			game_count=3;
			game_time_1=0;
		}
	}
	else if(game_count==3)
	{
		if(Y1==0&&X1!=0&&X2!=0&&Y2!=0)
		{
			game_count=4;
		}
	}
	else if(game_count==4)
	{
		game_time_1++;
		if(game_time_1==50)
		{
			game_count=5;
			game_time_1=0;
		}
	}
	else if(game_count==5)
	{
		if(X1==0&&Y1==0&&X2!=0&&Y2!=0)
		{
			game_count=6;
		}
	}
	else if(game_count==6)
	{
		game_time_1++;
		if(game_time_1==50)
		{
			game_count=7;
			game_time_1=0;
		}
	}
	else if(game_count==7)
	{
		if(X1==0&&Y2==0&&X2!=0&&Y1!=0)
		{
			game_count=8;
		}
	}
	else if(game_count==8)
	{
		game_time_1++;
		if(game_time_1==50)
		{
			game_count=9;
			game_time_1=0;
		}
	}
	else if(game_count==9)
	{
		if(X1!=0&&Y2==0&&X2!=0&&Y1!=0)
		{
			game_count=10;
		}
	}
	else if(game_count==10)
	{
		game_time_1++;
		if(game_time_1==50)
		{
			game_count=11;
			game_time_1=0;
		}
	}
	else if(game_count==11)
	{
		if(X2==0&&Y2==0&&X1!=0&&Y1!=0)
		{
			game_count=12;
		}
	}
}
