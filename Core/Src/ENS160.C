/*
 * ENS160.C
 *
 *  Created on: Apr 5, 2024
 *      Author: axaro1
 */
#include "../Inc/ens160.h"

#include "stm32f4xx_it.h"
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c2;

uint16_t ENS160_CONCAT_BYTES(uint8_t msb, uint8_t lsb) {
    // Combine MSB and LSB into a single uint16_t number
    uint16_t combined = (uint16_t)msb << 8 | lsb;
    return combined;
}


void write_reg_spi(uint8_t reg, const void* pBuf, size_t size) {
    if (pBuf == NULL) {
        // Handle NULL pointer error
        return;
    }

    const uint8_t *data_buffer = (const uint8_t *)pBuf;
    reg = (reg << 1) | 0x00;
    // Begin SPI transaction
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, &(reg), 1, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        // Handle SPI transmission error
        return;
    }

    // Transmit data bytes
    status = HAL_SPI_Transmit(&hspi1, (uint8_t *)data_buffer, size, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        // Handle SPI transmission error
        return;
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

size_t read_reg_spi(uint8_t reg, void* pBuf, size_t size) {
    if (pBuf == NULL) {
        // Handle NULL pointer error
        return 0;
    }

    uint8_t *data_buffer = (uint8_t *)pBuf;
    size_t count = 0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(1);
    // Begin SPI transaction
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        // Handle SPI transmission error
        return 0;
    }

    // Receive data bytes
    while (size--) {
        status = HAL_SPI_Receive(&hspi1, data_buffer++, 1, HAL_MAX_DELAY);
        if (status != HAL_OK) {
            // Handle SPI reception error
            return count;
        }
        count++;
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    return count;
}


/*
void read_reg_spi(uint8_t reg, void* buffer, size_t buffer_size) {
    uint8_t *data_buffer = (uint8_t *)buffer;
    uint8_t tx_data[1]; // Transmit buffer (contains register address)
    uint8_t rx_data; // Receive buffer (single byte)

    // Prepare the transaction with register address
    tx_data[0] = reg | 0x80; // Set the read control bit

    // Lower PA4
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    // Transmit the register address to initiate read
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, tx_data, 1, HAL_MAX_DELAY);

    if (status != HAL_OK) {
        // Transmission error occurred
    }

    // Receive data
    for (size_t i = 0; i < buffer_size; i++) {
        // Transmit dummy byte to receive data
    HAL_StatusTypeDef status2 = HAL_SPI_Receive(&hspi1, &rx_data, 1, HAL_MAX_DELAY);
        // Store received data in buffer
    if (status2 != HAL_OK) {
        // Transmission error
    }
        *data_buffer++ = rx_data;
    }

    // Raise PA4
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}


void write_reg_spi(uint8_t reg, uint8_t* buffer, size_t buffer_size) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // CSn low to select device

    // Send the register address
    uint8_t address_byte = (reg & 0x7F) | 0x00; // Address with RW bit set to 0
    HAL_SPI_Transmit(&hspi1, &address_byte, 1, HAL_MAX_DELAY);

    // Send data bytes
    HAL_SPI_Transmit(&hspi1, buffer, buffer_size, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // CSn high to end Write sequence
}
*/

void i2c_writeReg(uint16_t reg, const void* pBuf, size_t size)
{
    if (pBuf == NULL) {
        // Handle error: null pointer
        return;
    }

    uint8_t * _pBuf = (uint8_t *)pBuf;
    /*
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c2, (SLAVE_ADDR << 1), reg, I2C_MEMADD_SIZE_8BIT, _pBuf, size, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        // Handle error: I2C write error
        return;
    }
    */
    uint16_t devAddr = (SLAVE_ADDR << 1); // Shift the slave address left by 1 to make room for the R/W bit (0)

    // Send Slave Address and R/W Bit (0)
    if (HAL_I2C_Master_Transmit(&hi2c2, devAddr, NULL, 0, HAL_MAX_DELAY) != HAL_OK) {
        // Handle error: I2C write error
        return;
    }

    // Send Register Address
    if (HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)reg, (uint8_t*)&reg, sizeof(reg), HAL_MAX_DELAY) != HAL_OK) {
        // Handle error: I2C write error
        return;
    }

    // Send Data Bytes
    if (HAL_I2C_Master_Transmit(&hi2c2, devAddr | 0x01, _pBuf, size, HAL_MAX_DELAY) != HAL_OK) {
        // Handle error: I2C write error
        return;
    }
}

size_t i2c_readReg(uint16_t reg, void* pBuf, size_t size)
{
    if (pBuf == NULL || size == 0) {
        return 0;
    }

    uint16_t devAddr = SLAVE_ADDR << 1;
    uint8_t regAddrMSB = (reg >> 8) & 0xFF;
    uint8_t regAddrLSB = reg & 0xFF;

    // Start condition
    if (HAL_I2C_Master_Transmit(&hi2c2, devAddr, NULL, 0, HAL_MAX_DELAY) != HAL_OK) {
        // Handle error: I2C write error
        return 0;
    }

    // Send the address of the first register to read
    if (HAL_I2C_Master_Transmit(&hi2c2, regAddrMSB, &regAddrLSB, sizeof(regAddrLSB), HAL_MAX_DELAY) != HAL_OK) {
        // Handle error: I2C write error
        return 0;
    }

    // Restart condition
    HAL_Delay(1);

    // Send the 7-bit slave address with the R/W bit set to 1 (read)
    devAddr |= 0x01;

    // Read data bytes from sequential registers
    size_t bytesRead = 0;
    if (HAL_I2C_Master_Receive(&hi2c2, devAddr, pBuf, size, HAL_MAX_DELAY) == HAL_OK) {
        bytesRead = size;
    } else {
        // Handle error: I2C read error
    }

    return bytesRead;
}


void ens160_Init()
{
    // Functionless I2C init:
    uint8_t opmode_standard = OPMODE_STANDARD;
    uint8_t config_zero = 0x00;

    i2c_writeReg(OPMODE, &opmode_standard, sizeof(opmode_standard));
    i2c_writeReg(CONFIG, &config_zero, sizeof(config_zero));

    // Set other parameters if necessary
    // set_opmode(OPMODE_STANDARD);
    // set_int(0x00);
    HAL_Delay(20);
    setTempAndHum(25.0, 50.0);
}

uint16_t read_part_id() {
    uint8_t buffer[2];

    // Read the data from the PART_ID register (addresses 0 and 1)
    read_reg_spi(0, buffer, sizeof(buffer));

    // Concatenate the bytes to form the complete PART_ID value
    uint16_t part_id = ENS160_CONCAT_BYTES(buffer[0], buffer[1]);

    return part_id;
}

// FUNZIONA
void set_opmode(uint8_t mode) {
	//write_reg_spi(OPMODE, &mode, sizeof(mode));
    HAL_Delay(20); // Give it some time to switch mode
}

// FUNZIONA
void set_int(uint8_t mode) {
	i2c_readReg(CONFIG, &mode, sizeof(mode));
	//write_reg_spi(CONFIG, &mode, sizeof(mode));
    HAL_Delay(20); // Give it some time to switch mode
}


uint8_t read_data_aqi(){
	uint8_t data = 0;
	i2c_readReg(DATA_AQI, &data, sizeof(data));
	//read_reg_spi(DATA_AQI, &data, sizeof(data));
	return data;
}

uint16_t read_data_tvoc(){
	uint8_t buffer[2];
	i2c_readReg(DATA_TVOC , buffer, sizeof(buffer));
	//read_reg_spi(DATA_TVOC , buffer, sizeof(buffer));
	uint16_t data_tvoc = ENS160_CONCAT_BYTES(buffer[0], buffer[1]);
	return data_tvoc;
}

uint16_t read_data_eco2(){
	uint8_t buffer[2];
	i2c_readReg(DATA_ECO2 , buffer, sizeof(buffer));
    uint16_t data_eco2 = ENS160_CONCAT_BYTES(buffer[0], buffer[1]);
    return data_eco2;
}

void read_firmware_version(uint8_t* major, uint8_t* minor, uint8_t* release) {
    // Write command to clear the GPRs
    write_reg_spi(COMMAND, (uint8_t*)COMMAND_CLRGPR, sizeof(COMMAND_CLRGPR));
    HAL_Delay(10);

    // Write command to get the application version
    write_reg_spi(COMMAND, (uint8_t*)COMMAND_GET_APPVER, sizeof(COMMAND_GET_APPVER));
    HAL_Delay(10);

    // Declare a buffer to store the firmware version data
    uint8_t buffer[3];

    // Read the firmware version from GPRs 4, 5, and 6
    read_reg_spi(GPR_READ(4), buffer, 3);

    // Extract the major, minor, and release version from the buffer
    *major = buffer[0];
    *minor = buffer[1];
    *release = buffer[2];
}


uint8_t read_opmode() {
    uint8_t opmode = 0;
    read_reg_spi(OPMODE, &opmode, sizeof(opmode));
    return opmode;
}
void setTempAndHum(float ambientTemp, float relativeHumidity){
	  uint16_t temp = (ambientTemp + 273.15) * 64;
	  uint16_t rh = relativeHumidity * 512;
	  uint8_t buf[4];

	  buf[0] = temp & 0xFF;
	  buf[1] = (temp & 0xFF00) >> 8;
	  buf[2] = rh & 0xFF;
	  buf[3] = (rh & 0xFF00) >> 8;
	  //write_reg_spi(TEMP_IN, buf, sizeof(buf));
	  i2c_writeReg(TEMP_IN, buf, sizeof(buf));

}

uint8_t get_ENS160Status(void){

	uint8_t ENS160Status;
	read_reg_spi(DEVICE_STATUS, &ENS160Status, sizeof(ENS160Status));
	return ENS160Status;
}
