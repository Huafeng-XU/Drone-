/*********************************************************************************
JJ_fly by TIVA
�ļ�����IIC.h
������Ӳ��IIC
���ߣ�¬���
ʱ�䣺2015.10
**********************************************************************************/

#ifndef IIC_H_
#define IIC_H_

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

#define GPIO_PE4_I2C2SCL        0x00041003
#define GPIO_PE5_I2C2SDA        0x00041403
#define GPIO_PA6_I2C1SCL        0x00001803
#define GPIO_PA7_I2C1SDA        0x00001C03
extern unsigned char SLAVE_ADDRESS;

void i2c_init();
unsigned char i2c_write(unsigned char reg_addr,unsigned char data);
unsigned char i2c_read(unsigned char reg_addr);
int Get16Bit(unsigned char reg_addr);
#endif /* IIC_H_ */
