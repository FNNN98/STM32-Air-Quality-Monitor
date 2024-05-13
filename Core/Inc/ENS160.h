/*
 * ENS160.h
 *
 *  Created on: Apr 5, 2024
 *      Author: axaro1
 */
#include "stm32f4xx_hal.h"
#ifndef INC_ENS160_H_
#define INC_ENS160_H_

#define SLAVE_ADDR 			0x52 // I2C Slave Address

#define PART_ID             0x00 // Read Device Identity - Length: 2 bytes
#define OPMODE              0x10 // Read/Write Operating Mode - Length: 1 byte
#define CONFIG              0x11 // Read/Write Interrupt Pin Configuration - Length: 1 byte
#define COMMAND             0x12 // Read/Write Additional System Commands - Length: 1 byte  NB|| WORKS ONLY IN IDLE MODE
#define TEMP_IN             0x13 // Read/Write Host Ambient Temperature Information - Length: 2 bytes
#define RH_IN               0x15 // Read/Write Host Relative Humidity Information - Length: 2 bytes
// Reserved: 0x17 to 0x1F
#define DEVICE_STATUS       0x20 // Read Operating Mode - Length: 1 byte
#define DATA_AQI            0x21 // Read Air Quality Index - Length: 1 byte
#define DATA_TVOC           0x22 // Read TVOC Concentration (ppb) - Length: 2 bytes
#define DATA_ECO2           0x24 // Read Equivalent CO2 Concentration (ppm) - Length: 2 bytes
// Reserved: 0x26, 0x28
#define READ_RESERVED       0x2A // Read Reserved - Length: 2 bytes
// Reserved: 0x2C to 0x2F
#define DATA_T              0x30 // Read Temperature used in calculations - Length: 2 bytes
#define DATA_RH             0x32 // Read Relative Humidity used in calculations - Length: 2 bytes
// Reserved: 0x34 to 0x37
#define DATA_MISR           0x38) // Read Data Integrity Field (optional) - Length: 1 byte
#define GPR_WRITE(x)        0x40 + (x) // Read/Write General Purpose Write Registers - Length: 8 bytes
#define GPR_READ(x)         0x48 + (x) // Read General Purpose Read Registers - Length: 8 bytes

#define OPMODE_DEEP_SLEEP   0x00 // low-power standby --> Sensor will respond only to OPMODE
#define OPMODE_IDLE         0x01 // low-power mode     --> To be used only to configure before running Standard mode
#define OPMODE_STANDARD     0x02 // Recommended operating mode
#define OPMODE_RESET        0xF0 // RESET


// COMMAND REGISTER R/W
#define COMMAND_NOP         0x00
#define COMMAND_GET_APPVER  0x0E // Display ens160 firmware version to GPR_READ4, GPR_READ5, GPR_READ6 [respectively, Major/Minor/Release]
#define COMMAND_CLRGPR      0xCC // Clears all GPR registers


// TEMP_IN temperature compensation to sensor
uint16_t ENS160_CONCAT_BYTES(uint8_t msb, uint8_t lsb);

void ens160_Init();

void set_opmode(uint8_t mode);

void set_int(uint8_t mode);

void write_reg_spi(uint8_t reg, const void* pBuf, size_t size);
size_t read_reg_spi(uint8_t reg, void* pBuf, size_t size);

void i2c_writeReg(uint16_t reg, const void* pBuf, size_t size);
size_t i2c_readReg(uint16_t reg, void* pBuf, size_t size);

uint8_t read_data_aqi();
uint16_t read_data_tvoc();
uint16_t read_data_eco2();

void read_firmware_version(uint8_t* major, uint8_t* minor, uint8_t* release);
void setTempAndHum(float ambientTemp, float relativeHumidity);
uint8_t get_ENS160Status(void);
uint8_t read_opmode();
uint16_t read_part_id();

#endif /* INC_ENS160_H_ */
