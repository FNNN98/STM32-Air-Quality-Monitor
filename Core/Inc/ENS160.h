/*
 * ENS160.h
 *
 *  Created on: Apr 5, 2024
 *      Author: axaro1
 */
#include "stm32f4xx_hal_conf.h"

#ifndef INC_ENS160_H_
#define INC_ENS160_H_

#define PART_ID             0x00 // Read Device Identity - Length: 2 bytes
#define OPMODE              0x10 // Read/Write Operating Mode - Length: 1 byte
#define CONFIG              0x11 // Read/Write Interrupt Pin Configuration - Length: 1 byte
#define COMMAND             0x12 // Read/Write Additional System Commands - Length: 1 byte
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
#define DATA_MISR           0x38 // Read Data Integrity Field (optional) - Length: 1 byte
#define GPR_WRITE(x)        (0x40 + (x)) // Read/Write General Purpose Write Registers - Length: 8 bytes
#define GPR_READ(x)         (0x48 + (x)) // Read General Purpose Read Registers - Length: 8 bytes

#endif /* INC_ENS160_H_ */
