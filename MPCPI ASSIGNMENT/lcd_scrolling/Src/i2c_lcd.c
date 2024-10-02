/*
 * i2c_lcd.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Nilesh
 */

#include "i2c_lcd.h"
void LcdWrite4Bit(uint8_t val)
{
	I2CStart();
	I2CSendSlaveAddr(LCD_SLAVE_ADDR_W);
	I2CSendData(val);
	I2CStop();
}

void LcdWriteByte(uint8_t rs, uint8_t val)
{
	uint8_t high = val & 0xF0, low = (val<<4) & 0xF0;
	uint8_t bvrs = (rs == LCDCMD) ? 0 : BV(LCD_RS);
	LcdWrite4Bit(high | bvrs | BV(LCD_EN) | BV(LCD_BL));
	DelayMs(1);
	LcdWrite4Bit(high | bvrs | BV(LCD_BL));

	LcdWrite4Bit(low | bvrs | BV(LCD_EN) | BV(LCD_BL));
	DelayMs(1);
	LcdWrite4Bit(low | bvrs | BV(LCD_BL));
}

int LcdInit()
{
	DelayMs(20);
	I2CInit();
	I2CStart();
	int ret = I2CIsDeviceReady(LCD_SLAVE_ADDR_W);
	I2CStop();
	if(!ret)
		return 0;
	LcdWrite4Bit(LCDFUNCSET8BIT | BV(LCD_EN));
	__NOP();
	LcdWrite4Bit(LCDFUNCSET8BIT);
	DelayMs(5);

	LcdWrite4Bit(LCDFUNCSET8BIT | BV(LCD_EN));
	__NOP();
	LcdWrite4Bit(LCDFUNCSET8BIT);
	DelayMs(1);

	LcdWrite4Bit(LCDFUNCSET8BIT | BV(LCD_EN));
	__NOP();
	LcdWrite4Bit(LCDFUNCSET8BIT);
	DelayMs(3);

	LcdWrite4Bit(LCDFUNCSET4BIT | BV(LCD_EN));
	__NOP();
	LcdWrite4Bit(LCDFUNCSET4BIT);
	DelayMs(3);

	LcdWriteByte(LCDCMD, LCDFUNCSET4BIT1LINE);  // Set LCD to 1-line mode
	DelayMs(1);
	LcdWriteByte(LCDCMD, LCDDISPCTRL);
	DelayMs(1);
	LcdWriteByte(LCDCMD, LCDCLEAR);
	DelayMs(1);
	LcdWriteByte(LCDCMD, LCDENTRYMODE);
	DelayMs(1);
	LcdWriteByte(LCDCMD, LCDDISPON);
	DelayMs(1);

	return ret;
}

void LcdPuts(uint8_t line, char str[])
{
	int i;
	LcdWriteByte(LCDCMD, line);
	DelayMs(1);
	for(i=0; str[i]!='\0'; i++)
		LcdWriteByte(LCDDATA, str[i]);
	}

void LcdShiftLeft(void)
{
	LcdWriteByte(LCDCMD,LCDSHIFT);
}
