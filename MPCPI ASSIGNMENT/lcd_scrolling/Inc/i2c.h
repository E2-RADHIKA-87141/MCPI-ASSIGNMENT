/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 24, 2024
*/

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"

// I2C Bus -- I2C1 (PB6, PB7)
// 	PB6 -- SCL, PB7 -- SDA

#define SCL_PIN		6
#define SDA_PIN		7

void I2CInit(void);
void I2CStart(void);
void I2CRepeatStart(void);
void I2CStop(void);
void I2CSendSlaveAddr(uint8_t slaveaddr);
void I2CSendData(uint8_t data);
uint16_t I2CRecvData(void);
uint16_t I2CRecvDataNAck(void);
int I2CIsDeviceReady(uint8_t slaveaddr);
#endif /* I2C_H_ */
