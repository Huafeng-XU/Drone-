/*********************************************************************************
JJ_fly by TIVA
�ļ�����init.h
��������ʼ�����Լ����
���ߣ�¬���
ʱ�䣺2015.11
**********************************************************************************/

#ifndef INIT_H_
#define INIT_H_

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
#include "driverlib/uart.h"
#include "driverlib/timer.h"

extern int check_count;
extern int check_end;
extern int yaw_check,yaw_check_old;
extern int yaw_offest_add;
extern int yaw_offest;
extern float G;
void all_init();
void check_start();
void check_offest();
void check();
void init_last();
void init_first();
#endif /* INIT_H_ */
