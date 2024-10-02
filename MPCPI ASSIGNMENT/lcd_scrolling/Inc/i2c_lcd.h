/*
 * i2c_lcd.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Nilesh
 */

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "i2c.h"

#define LCD_SLAVE_ADDR_W	0x4E
#define LCD_SLAVE_ADDR_R	0x4F
//#define LCD_SLAVE_ADDR_W	0x7E
//#define LCD_SLAVE_ADDR_R	0x7F
#define LCDCLEAR		0x01
#define LCDFUNCSET8BIT	0x30
#define LCDFUNCSET4BIT	0x20
#define LCDFUNCSET4BIT1LINE		0x20
#define LCDFUNCSET4BIT2LINES	0x28
#define LCDDISPCTRL		0x08
#define LCDDISPON		0x0C
#define LCDENTRYMODE	0x06
#define LCDLINE1		0x80
#define LCDLINE2		0xC0
#define LCDSHIFT		0x18

#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3

#define LCDCMD		0x80
#define LCDDATA		1


int LcdInit(void);
void LcdWrite4Bit(uint8_t val);
void LcdWriteByte(uint8_t rs, uint8_t val);
void LcdPuts(uint8_t line, char str[]);
//void SwitchIntrCount();
void LcdShiftLeft(void);
#endif /* I2C_LCD_H_ */
