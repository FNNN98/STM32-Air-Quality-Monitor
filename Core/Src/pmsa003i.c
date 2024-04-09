/*
 * pmsa003i.c
 *
 *  Created on: Apr 7, 2024
 *      Author: axaro1
 */
#include "stm32f4xx_hal.h" // Include the appropriate STM32 HAL header file
#include <string.h>
#include <stdbool.h>
#include "pmsa003i.h"

extern I2C_HandleTypeDef hi2c2;
#define PMSA003I_ADDRESS 0x12

uint8_t PMSA003I_Init(I2C_HandleTypeDef *i2cHandle , PMSA003I *dev){
	uint8_t errorNum = 0;

	dev->i2cHandle	= i2cHandle;
    dev->framelen = 0;            // Initial value for framelen
    dev->pm10_standard = 0;       // Initial value for pm10_standard
    dev->pm25_standard = 0;       // Initial value for pm25_standard
    dev->pm100_standard = 0;      // Initial value for pm100_standard
    dev->pm10_env = 0;            // Initial value for pm10_env
    dev->pm25_env = 0;            // Initial value for pm25_env
    dev->pm100_env = 0;           // Initial value for pm100_env
    dev->particles_03um = 0;      // Initial value for particles_03um
    dev->particles_05um = 0;      // Initial value for particles_05um
    dev->particles_10um = 0;      // Initial value for particles_10um
    dev->particles_25um = 0;      // Initial value for particles_25um
    dev->particles_50um = 0;      // Initial value for particles_50um
    dev->particles_100um = 0;     // Initial value for particles_100um
    dev->unused = 0;              // Initial value for unused
    dev->checksum = 0;            // Initial value for checksum

    return errorNum;

}

// DATA ACQUISITION
HAL_StatusTypeDef pmsa003i_ReadData(PMSA003I *dev) {
    uint8_t data[24]; // Array to store the read data

    // Read registers 0x04 to 0x1B
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(dev->i2cHandle, PMSA003I_ADDRESS, REG_DATA_1_HIGH, I2C_MEMADD_SIZE_8BIT, data, 24, HAL_MAX_DELAY);

    if (status != HAL_OK) {
        // TODO Extra error handling if I2C read fails
        return status;
    }

    // Parse the read data and store it in the device structure
    dev->pm10_standard = (data[0] << 8) | data[1];
    dev->pm25_standard = (data[2] << 8) | data[3];
    dev->pm100_standard = (data[4] << 8) | data[5];
    dev->pm10_env = (data[6] << 8) | data[7];
    dev->pm25_env = (data[8] << 8) | data[9];
    dev->pm100_env = (data[10] << 8) | data[11];
    dev->particles_03um = (data[12] << 8) | data[13];
    dev->particles_05um = (data[14] << 8) | data[15];
    dev->particles_10um = (data[16] << 8) | data[17];
    dev->particles_25um = (data[18] << 8) | data[19];
    dev->particles_50um = (data[20] << 8) | data[21];
    dev->particles_100um = (data[22] << 8) | data[23];

    return HAL_OK;
}


//LOW LEVEL
HAL_StatusTypeDef pmsa003i_ReadRegister(PMSA003I *dev, uint8_t reg, uint8_t *data){
	return HAL_I2C_Mem_Read(dev->i2cHandle, PMSA003I_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

