/*********************************************************************************
JJ_fly by TIVA
�ļ�����capture.h
����������ң�������ջ�������PWM�����ɲ�����·
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/

#ifndef CAPTURE_H_
#define CAPTURE_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "display_oled.h"
#include "driverlib/timer.h"

#define GPIO_PB0_T2CCP0         0x00010007
#define GPIO_PB1_T2CCP1         0x00010407
#define GPIO_PB2_T3CCP0         0x00010807
#define GPIO_PB3_T3CCP1         0x00010C07
#define GPIO_PB4_T1CCP0         0x00011007
#define GPIO_PB5_T1CCP1         0x00011407

void capture_init();
void get_rc_value();
extern uint16_t CH_1,CH_2,CH_3,CH_4,CH_5,CH_6;//ת�������������ͨ��ֵ
#endif /* CAPTURE_H_ */
