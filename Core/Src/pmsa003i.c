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

void PMSA003I_Init(I2C_HandleTypeDef *i2cHandle, PMSA003I *dev){
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
    dev->i2cHandle	= i2cHandle;
}

bool pmsa003i_ReadData(PMSA003I *dev) {
    const uint8_t num_bytes = 32;
    uint8_t buffer[num_bytes];
    HAL_I2C_Master_Receive(dev->i2cHandle, PMSA003I_ADDRESS, buffer, num_bytes, HAL_MAX_DELAY);

    if (buffer[0] != 0x42) {
        return false;
    }

    int16_t sum = 0;
    for (uint8_t i = 0; i < 30; i++) {
        sum += buffer[i];
    }

    uint16_t buffer_u16[15];
    for (uint8_t i = 0; i < 15; i++) {
        buffer_u16[i] = buffer[2 + i * 2 + 1];
        buffer_u16[i] += (buffer[2 + i * 2] << 8);
    }

    memcpy((void *)dev, (void *)buffer_u16, 30);

    if (sum != dev->checksum) {
        return false;
    }

    return true;
}



//LOW LEVEL
HAL_StatusTypeDef pmsa003i_ReadRegister(I2C_HandleTypeDef *i2cHandle, PMSA003I *dev, uint8_t reg, uint8_t *data){
	return HAL_I2C_Mem_Read(&hi2c2, PMSA003I_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

