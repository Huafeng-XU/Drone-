/*********************************************************************************
JJ_fly by TIVA
�ļ�����US100.c
������US100���ݶ�ȡ�봦��
���ߣ�¬���
ʱ�䣺2016.4
**********************************************************************************/
#include "uarts.h"
#include "mymath.h"
#include "US100.h"
#include "imu_new.h"
float dis;
float US100_Alt;
float US100_Alt_old;
void US_100_init()//���ڳ�ʼ��
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);//ʹ��uart0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//������ʹ��
	GPIOPinConfigure(GPIO_PC6_U3RX);
	GPIOPinConfigure(GPIO_PC7_U3TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7);//ʹ����ӦIO
	//uart0,������115200,8λ����λ1λֹͣλ
	UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTFIFOLevelSet(UART3_BASE,UART_FIFO_TX7_8,UART_FIFO_RX6_8);//����FIFO�ﵽ7/8ʱ�жϣ�����FIFO�ﵽ6/8ʱ�ж�
    //IntMasterEnable();//�������ж�
    //IntEnable(INT_UART3_SNOWFLAKE);//����uart0�ж�
    //UARTIntEnable(UART3_BASE, UART_INT_RX);//������RX�ж�
}
void US_100_trig()//�����ź�
{
	UARTCharPutNonBlocking(UART3_BASE, 0X55);
}
void US_100_get()//��ȡ���ؾ���ֵ
{
	unsigned char temp_H,temp_L;
	temp_H=UARTCharGetNonBlocking(UART3_BASE);
	temp_L=UARTCharGetNonBlocking(UART3_BASE);
	//�������ĸ�Ӧ�Ƕ���15�㵱�ɻ��ǶȺܴ�ʹ�����и߶ȶ�ȡ
	if(Q_ANGLE_X<13.0f&&Q_ANGLE_X>-13.0f&&Q_ANGLE_Y<13.0f&&Q_ANGLE_Y>-13.0f)
	{
		dis=(float)(temp_H*256+temp_L)/100;
		US100_Alt = Moving_Median(2,4,dis);//�ƶ���λֵ�˲�����Ȳ���̫��
		if(US100_Alt-US100_Alt_old>5.0f||US100_Alt-US100_Alt_old<-5.0f)//�˵�һЩë�̣��߶�ͻ�䣩
		{
			US100_Alt=US100_Alt_old;
		}
		US100_Alt_old = US100_Alt;//������ʷ����
	}
}

