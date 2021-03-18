/*
 * PWM.c
 *
 *  Created on: 2015-11-13
 *      Author: lenovo-pc
 */


#include "PWM.h"

void pwm_init()
{
    //PWMʱ�����ã�64��Ƶ
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
    //ʹ��PWM1ģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //ʹ��PWM1ģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    //ʹ��PWM����
    GPIOPinConfigure(GPIO_PE5_M1PWM3);
    GPIOPinConfigure(GPIO_PE4_M1PWM2);
    GPIOPinConfigure(GPIO_PD1_M1PWM1);
    GPIOPinConfigure(GPIO_PD0_M1PWM0);
    //��������ΪPWM����
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    //����PWM������0�ͷ�����1���Ӽ���������Ƶ
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_1,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //����PWM������1��Ƶ�ʣ�ʱ��Ƶ��/pwm��Ƶ��/n,80M/64/3125=400hz
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 50000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 50000);

    //����PWM1/PWM1�����������
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 20000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, 20000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, 20000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, 20000);

    //ʹ��PWM������
    PWMGenEnable(PWM1_BASE, PWM_GEN_0);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);

    //ʹ��PWM1��PWM1�����
    PWMOutputState(PWM1_BASE, (PWM_OUT_0_BIT), true);
    PWMOutputState(PWM1_BASE, (PWM_OUT_1_BIT), true);
    PWMOutputState(PWM1_BASE, (PWM_OUT_2_BIT), true);
    PWMOutputState(PWM1_BASE, (PWM_OUT_3_BIT), true);
}



