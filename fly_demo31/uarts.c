/*********************************************************************************
JJ_fly by TIVA
�ļ�����uarts.c
���������ڷ�������գ��������°�ɰ���λ����ͨѶЭ�飬���ղ����жϣ�������
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/
#include "uarts.h"
#include "mpu6050.h"
#include "imu_new.h"
#include "capture.h"
#include "control.h"
#include "US100.h"
#include "flow.h"
#include "timers.h"

unsigned char UART_TXDATA[35];
unsigned char temp[20];
unsigned char rx_data[23];
unsigned char data_to_send[20];
unsigned char receive_count;

void uart_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//ʹ��uart0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//������ʹ��
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);//ʹ����ӦIO
	//uart0,������115200,8λ����λ1λֹͣλ
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX7_8,UART_FIFO_RX6_8);//����FIFO�ﵽ7/8ʱ�жϣ�����FIFO�ﵽ6/8ʱ�ж�
    IntMasterEnable();//�������ж�
    IntEnable(INT_UART0_SNOWFLAKE);//����uart0�ж�
    UARTIntEnable(UART0_BASE, UART_INT_RX);//������RX�ж�
}
/////////////////////////////�°�������λ��//////////////////////////////
static void ANO_DT_Send_Check(unsigned char head, unsigned char check_sum)
{
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xEF;
	data_to_send[3]=2;
	data_to_send[4]=head;
	data_to_send[5]=check_sum;

	unsigned char sum = 0;
	unsigned char i = 0;
	for(i=0;i<6;i++)
		sum += data_to_send[i];
	data_to_send[6]=sum;

	UARTSend(data_to_send,7);
}
void ANO_DT_Send_Status()//��ANO��λ�����ͷ�����̬
{
	unsigned char _cnt=0;
	unsigned char i=0;
	int  _temp;
	unsigned long _temp2;
	//֡ͷ
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	//����
	data_to_send[_cnt++]=0;
	//ŷ���ǲ���
	_temp = (int)((Q_ANGLE_X-offset_angle_x)*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)((Q_ANGLE_Y-offset_angle_y)*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(Q_ANGLE_Z*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	//�߶�
	_temp2 = (int)(US100_Alt*100);
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);


	//����ģʽ
	data_to_send[_cnt++] = 0;
	//����������
	data_to_send[_cnt++] = 0;
	//����
	data_to_send[3] = _cnt-4;
	//��У��
	unsigned char sum = 0;
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	//����
	UARTSend(data_to_send,_cnt);
}
void ANO_DT_Send_RCData()
{
	unsigned char _cnt=0;
	unsigned char i=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(CH_1);
	data_to_send[_cnt++]=BYTE0(CH_1);
	data_to_send[_cnt++]=BYTE1(CH_2);
	data_to_send[_cnt++]=BYTE0(CH_2);
	data_to_send[_cnt++]=BYTE1(CH_5);
	data_to_send[_cnt++]=BYTE0(CH_5);
	data_to_send[_cnt++]=BYTE1(CH_6);
	data_to_send[_cnt++]=BYTE0(CH_6);
	data_to_send[_cnt++]=BYTE1(CH_3);
	data_to_send[_cnt++]=BYTE0(CH_3);
	data_to_send[_cnt++]=BYTE1(CH_4);
	data_to_send[_cnt++]=BYTE0(CH_4);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=game_count;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;

	data_to_send[3] = _cnt-4;

	unsigned char sum = 0;
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];

	data_to_send[_cnt++]=sum;

	UARTSend(data_to_send, _cnt);
}

void ANO_DT_Send_MotoPWM()
{
	unsigned char _cnt=0;
	unsigned char i=0;
	int  _temp;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
	_temp = (int)(motor_1/50);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(motor_2/50);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(motor_3/50);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(motor_4/50);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=X1;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=Y1;
	//_temp = (int)(X);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=X2;
	//_temp = (int)(Y);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=Y2;

	data_to_send[3] = _cnt-4;

	unsigned char sum = 0;
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];

	data_to_send[_cnt++]=sum;

	UARTSend(data_to_send, _cnt);
}
void ANO_DT_Receive_PID()
{
	unsigned char sum = 0;
	unsigned char i=0;
	//unsigned char num=23;
	for(i=0;i<22;i++)
		sum += rx_data[i];
	if(sum!=rx_data[22])
	{
		//sum=rx_data[22];
		return;
	}
	if(rx_data[0]!=0xAA || rx_data[1]!=0xAF)
		return;
	if(rx_data[2]==0x10)
	{
		kp_aspeed_x=(rx_data[4]<<8)|(rx_data[5]);
		kp_aspeed_y=kp_aspeed_x;
		ki_aspeed_x=(rx_data[6]<<8)|(rx_data[7]);
		ki_aspeed_y=ki_aspeed_x;
		kd_aspeed_x=(rx_data[8]<<8)|(rx_data[9]);
		kd_aspeed_y=kd_aspeed_x;

		kp_angle_x=(rx_data[10]<<8)|(rx_data[11]);
		kp_angle_y=kp_angle_x;
		ki_angle_x=(rx_data[12]<<8)|(rx_data[13]);
		ki_angle_y=ki_angle_x;
		kd_angle_x=(rx_data[14]<<8)|(rx_data[15]);
		kd_angle_y=kd_angle_x;

		kp_aspeed_z=(rx_data[16]<<8)|(rx_data[17]);
		kp_angle_z=(rx_data[18]<<8)|(rx_data[19]);
		kd_aspeed_z=(rx_data[20]<<8)|(rx_data[21]);
		ANO_DT_Send_Check(rx_data[2],sum);
		sum=sum;
	}
	else if(rx_data[2]==0x11)
	{
		kp_height=(rx_data[4]<<8)|(rx_data[5]);
		ki_height=(rx_data[6]<<8)|(rx_data[7]);
		kd_height=(rx_data[8]<<8)|(rx_data[9]);
		kp_point=(rx_data[10]<<8)|(rx_data[11]);
		ki_point=(rx_data[12]<<8)|(rx_data[13]);
		kd_point=(rx_data[14]<<8)|(rx_data[15]);
		ki_height_ready=(rx_data[16]<<8)|(rx_data[17]);
		game_speed=(rx_data[18]<<8)|(rx_data[19]);
		shache=(rx_data[20]<<8)|(rx_data[21]);
		ANO_DT_Send_Check(rx_data[2],sum);
		sum=sum;
	}

}
void  ANO_DT_Send_Speed()
{
	unsigned char _cnt=0;
	unsigned char i=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0x00;
	data_to_send[_cnt++]=vx;
	data_to_send[_cnt++]=vy;
	data_to_send[3] = _cnt-4;
	unsigned char sum = 0;
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	UARTSend(data_to_send, _cnt);
}
void  UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        //UARTCharPutNonBlocking(UART1_BASE, *pui8Buffer++);
    	UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

/////////////////////////////�ɰ�������λ��//////////////////////////////
void UART_Send_AF(void)
{
	unsigned char i,sum;
	unsigned int _temp;

	UART_TXDATA[0]=0x88;
	UART_TXDATA[1]=0xAF;
	UART_TXDATA[2]=0x1C;
	UART_TXDATA[3]=BYTE1(MPU6050_ACC_LAST_X);
	UART_TXDATA[4]=BYTE0(MPU6050_ACC_LAST_X);
	UART_TXDATA[5]=BYTE1(MPU6050_ACC_LAST_Y);
	UART_TXDATA[6]=BYTE0(MPU6050_ACC_LAST_Y);
	UART_TXDATA[7]=BYTE1(MPU6050_ACC_LAST_Z);
	UART_TXDATA[8]=BYTE0(MPU6050_ACC_LAST_Z);
	UART_TXDATA[9]=BYTE1(MPU6050_GYRO_LAST_X);
	UART_TXDATA[10]=BYTE0(MPU6050_GYRO_LAST_X);
	UART_TXDATA[11]=BYTE1(MPU6050_GYRO_LAST_Y);
	UART_TXDATA[12]=BYTE0(MPU6050_GYRO_LAST_Y);
	UART_TXDATA[13]=BYTE1(MPU6050_GYRO_LAST_Z);
	UART_TXDATA[14]=BYTE0(MPU6050_GYRO_LAST_Z);
	UART_TXDATA[15]=0;
	UART_TXDATA[16]=0;
	UART_TXDATA[17]=0;
	UART_TXDATA[18]=0;
	UART_TXDATA[19]=0;
	UART_TXDATA[20]=0;
	_temp = (int)(Q_ANGLE_X*100);
	UART_TXDATA[21]=BYTE1(_temp);
	UART_TXDATA[22]=BYTE0(_temp);
	_temp = (int)(Q_ANGLE_Y*100);
	UART_TXDATA[23]=BYTE1(_temp);
	UART_TXDATA[24]=BYTE0(_temp);
	_temp = (int)(Q_ANGLE_Z*10);
	UART_TXDATA[25]=BYTE1(_temp);
	UART_TXDATA[26]=BYTE0(_temp);

	sum = 0;
	for(i=0;i<31;i++)
		sum += UART_TXDATA[i];

	UART_TXDATA[31]=sum;

	UARTSend(UART_TXDATA,32);
}
void UART_Send_AE(void)
{
	unsigned char i,sum;
	UART_TXDATA[0]=0x88;
	UART_TXDATA[1]=0xAE;
	UART_TXDATA[2]=0x1C;
	for(i=3;i<15;i++)
	{
		UART_TXDATA[i]=rx_data[i-3];

	}
	UART_TXDATA[21]=0;
	UART_TXDATA[22]=0;
	UART_TXDATA[23]=0;
	UART_TXDATA[24]=0;
	UART_TXDATA[25]=0;
	UART_TXDATA[26]=0;
	sum = 0;
	for(i=0;i<31;i++)
		sum += UART_TXDATA[i];
	UART_TXDATA[31]=sum;
	UARTSend(UART_TXDATA,32);
}
//*****************************************************************************
// UART1�жϴ������
//*****************************************************************************
void UARTIntHandler(void)
{
    uint32_t ui32Status;


    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
    while(UARTCharsAvail(UART0_BASE))
    {
    	rx_data[receive_count]=UARTCharGetNonBlocking(UART0_BASE);
    	if(rx_data[0]==0xAA)
    	{
    		receive_count++;
    		if(receive_count==23)
    		{
    			receive_count=0;
    			ANO_DT_Receive_PID();
    			rx_data[0]=0;
    		}
    	}
    }

}
