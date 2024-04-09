/*
 * pmsa003i.h
 *
 *  Created on: Apr 7, 2024
 *      Author: axaro1
 */
#include <stdbool.h>
#include "stm32f4xx_hal.h" // Needed for I2C

#ifndef INC_PMSA003I_H_
#define INC_PMSA003I_H_

#define PMSA003I_ADDRESS 0x12 // I2C Address

// Register Definitions
#define REG_START_CHAR_1    0x00 // Start character 1 - Fixed value 0x42
#define REG_START_CHAR_2    0x01 // Start character 2 - Fixed value 0x4D
#define REG_FRAME_LEN_HIGH  0x02 // Frame length high byte
#define REG_FRAME_LEN_LOW   0x03 // Frame length low byte
#define REG_DATA_1_HIGH     0x04 // PM1.0 concentration high byte (CF=1, standard particle)
#define REG_DATA_1_LOW      0x05 // PM1.0 concentration low byte
#define REG_DATA_2_HIGH     0x06 // PM2.5 concentration high byte (CF=1, standard particle)
#define REG_DATA_2_LOW      0x07 // PM2.5 concentration low byte
#define REG_DATA_3_HIGH     0x08 // PM10 concentration high byte (CF=1, standard particle)
#define REG_DATA_3_LOW      0x09 // PM10 concentration low byte
#define REG_DATA_4_HIGH     0x0A // PM1.0 concentration high byte (under atmospheric environment)
#define REG_DATA_4_LOW      0x0B // PM1.0 concentration low byte
#define REG_DATA_5_HIGH     0x0C // PM2.5 concentration high byte (under atmospheric environment)
#define REG_DATA_5_LOW      0x0D // PM2.5 concentration low byte
#define REG_DATA_6_HIGH     0x0E // PM10 concentration high byte (under atmospheric environment)
#define REG_DATA_6_LOW      0x0F // PM10 concentration low byte
#define REG_DATA_7_HIGH     0x10 // Number of particles > 0.3 μm in 0.1L of air high byte
#define REG_DATA_7_LOW      0x11 // Number of particles > 0.3 μm in 0.1L of air low byte
#define REG_DATA_8_HIGH     0x12 // Number of particles > 0.5 μm in 0.1L of air high byte
#define REG_DATA_8_LOW      0x13 // Number of particles > 0.5 μm in 0.1L of air low byte
#define REG_DATA_9_HIGH     0x14 // Number of particles > 1.0 μm in 0.1L of air high byte
#define REG_DATA_9_LOW      0x15 // Number of particles > 1.0 μm in 0.1L of air low byte
#define REG_DATA_10_HIGH    0x16 // Number of particles > 2.5 μm in 0.1L of air high byte
#define REG_DATA_10_LOW     0x17 // Number of particles > 2.5 μm in 0.1L of air low byte

// Fixed Values
#define START_CHAR_1_VALUE  0x42 // Fixed value for Start Character 1
#define START_CHAR_2_VALUE  0x4D // Fixed value for Start Character 2


typedef struct PMSAQIdata {
  I2C_HandleTypeDef *i2cHandle; ///< I2C Handle
  uint16_t framelen;       ///< How long this data chunk is
  uint16_t pm10_standard,  ///< Standard PM1.0
      pm25_standard,       ///< Standard PM2.5
      pm100_standard;      ///< Standard PM10.0
  uint16_t pm10_env,       ///< Environmental PM1.0
      pm25_env,            ///< Environmental PM2.5
      pm100_env;           ///< Environmental PM10.0
  uint16_t particles_03um, ///< 0.3um Particle Count
      particles_05um,      ///< 0.5um Particle Count
      particles_10um,      ///< 1.0um Particle Count
      particles_25um,      ///< 2.5um Particle Count
      particles_50um,      ///< 5.0um Particle Count
      particles_100um;     ///< 10.0um Particle Count
  uint16_t unused;         ///< Unused
  uint16_t checksum;       ///< Packet checksum
} PMSA003I;


uint8_t PMSA003I_Init(I2C_HandleTypeDef *i2cHandle , PMSA003I *dev);

// DATA ACQUISITION
HAL_StatusTypeDef pmsa003i_ReadData(PMSA003I *dev);

//LOW LEVEL
HAL_StatusTypeDef pmsa003i_ReadRegister(PMSA003I *dev, uint8_t reg, uint8_t *data);

#endif /* INC_PMSA003I_H_ */
