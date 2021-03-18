/*********************************************************************************
JJ_fly by TIVA
�ļ�����flow.c
������ADNS3080���ݶ�ȡ�봦��
���ߣ�¬���
ʱ�䣺2016.4
**********************************************************************************/
#include "PIN.h"
#include "flow.h"
#include "mymath.h"
unsigned char led_flag;
char vx,vy;
char vx_temp;
char vy_temp;
unsigned char flow_count;
unsigned char img[5];
unsigned char camera_count;
char flow_flag;
char flow_data[10];
unsigned char X1,Y1,X2,Y2;
void read_flow();
void read_camera();
void flow_init()//���ڳ�ʼ��
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);//ʹ��uart0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//������ʹ��
	GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_DIR_MODE_IN);//������������Ϊ����
	GPIOPinConfigure(GPIO_PE1_U7TX);
	GPIOPinConfigure(GPIO_PE0_U7RX);
	GPIOPinTypeUART(GPIO_PORTE_BASE,GPIO_PIN_0|GPIO_PIN_1);//ʹ����ӦIO
	//uart0,������115200,8λ����λ1λֹͣλ
	UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTFIFOEnable(UART7_BASE);
	UARTFIFOLevelSet(UART7_BASE,UART_FIFO_TX7_8,UART_FIFO_RX2_8);//����FIFO�ﵽ7/8ʱ�жϣ�����FIFO�ﵽ6/8ʱ�ж�
	UARTIntRegister(UART7_BASE,read_flow);
    IntMasterEnable();//�������ж�
    IntEnable(INT_UART7_SNOWFLAKE);//����uart0�ж�
    UARTIntEnable(UART7_BASE, UART_INT_RX);//������RX�ж�
}
void k60_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);//ʹ��uart0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//������ʹ��
	GPIOPinConfigure(GPIO_PC4_U4RX);
	GPIOPinConfigure(GPIO_PC5_U4TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5);//ʹ����ӦIO
	//uart0,������115200,8λ����λ1λֹͣλ
	UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTFIFOLevelSet(UART4_BASE,UART_FIFO_TX7_8,UART_FIFO_RX4_8);//����FIFO�ﵽ7/8ʱ�жϣ�����FIFO�ﵽ6/8ʱ�ж�
	UARTIntRegister(UART4_BASE,read_camera);
	IntMasterEnable();//�������ж�
    IntEnable(INT_UART4_SNOWFLAKE);//����uart0�ж�
    UARTIntEnable(UART4_BASE, UART_INT_RX);//������RX�ж�
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
}
void read_flow()//�����жϣ���֪��Ϊʲô��STARTUP���޷�ע���ж�������
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART7_BASE, true);

    UARTIntClear(UART7_BASE, ui32Status);
    while(UARTCharsAvail(UART7_BASE))
    {
    	flow_data[flow_count]=UARTCharGetNonBlocking(UART7_BASE);
    	if(flow_data[0]==0xAA)//֡ͷAA BB
    	{
    		flow_count++;
    		if(flow_count==4)
    		{
    			flow_count=0;
    			if(flow_data[1]==0xBB)
    			{
    				vx_temp=flow_data[2]+127;//ԭʼ������-127��+127���ڼ����127����ת��
    				vy_temp=flow_data[3]+127;
    				flow_flag=1;

    			}
    			flow_data[0]=0;
    		}
    	}
    }
}

char flow_vx_num,flow_vy_num;

char send_flag;
char FLOW_NUM=5;
int VX_BUF[10];
int VY_BUF[10];
int vx_lpf;
int vy_lpf;
char vx_his;
char vy_his;
//����ԭʼ����ë�̺ܶ࣬����Ҫ�˲�
//���˲����û����˲�����ͷȥβȡƽ�������˳�һЩë��
//��Ч���������룬����Ľ�
void flow_filter()
{
	char i;
	int temp1=0;
	int temp2=0;
	int max1,min1;
	int max2,min2;
	char vx_avg,vy_avg;
	VX_BUF[flow_vx_num] = vx_temp;//���»�����������
	VY_BUF[flow_vx_num] = vy_temp;//���»�����������
	max1=VX_BUF[0];
	min1=VX_BUF[0];
	max2=VY_BUF[0];
	min2=VY_BUF[0];
	for(i=0;i<FLOW_NUM;i++)//Ѱ�����������е��������Сֵ
	{
		if(VX_BUF[i]>max1) max1=VX_BUF[i];
		if(VX_BUF[i]<min1) min1=VX_BUF[i];
		if(VY_BUF[i]>max2) max2=VY_BUF[i];
		if(VY_BUF[i]<min2) max2=VY_BUF[i];
		temp1+=VX_BUF[i];
		temp2+=VY_BUF[i];
	}
	vx_avg = (temp1-max1-min1) / (FLOW_NUM-2);
	vy_avg = (temp2-max2-min2) / (FLOW_NUM-2);//�м�����������
	//Y+=(vy-127);
	if(vx_avg-vx_his<10&&vx_avg-vx_his>-10||vx_avg==127)//�˳�ë������
	{
			vx=vx_avg;
		    //X+=(vx-127);
			vx_his=vx;//������ʷ����
	}


	if(vy_avg-vy_his<10&&vy_avg-vy_his>-10||vy_avg==127)
	{
		    vy=vy_avg;
		    //Y+=(vy-127);
			vy_his=vy;
	}

	flow_vx_num++;
	if(flow_vx_num==FLOW_NUM)
	{
		flow_vx_num=0;
	}
}
void read_camera()
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART4_BASE, true);

    UARTIntClear(UART4_BASE, ui32Status);
    while(UARTCharsAvail(UART4_BASE))
    {
    	img[camera_count]=UARTCharGetNonBlocking(UART4_BASE);
    	if(img[0]==0xAA)//֡ͷAA BB
    	{
    		camera_count++;
    		if(camera_count==5)
    		{
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,led_flag);
				led_flag=0xff-led_flag;
    			camera_count=0;
    			X1=img[1];
    			Y1=img[2];
    			X2=img[3];
    			Y2=img[4];
    			img[0]=0;
    		}
    	}
    }
}
