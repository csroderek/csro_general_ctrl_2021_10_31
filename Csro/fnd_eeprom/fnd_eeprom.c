#include "fnd_eeprom.h"
#include "i2c.h"
#include "fnd_com.h"

#define EEPROM_I2C hi2c3
#define EEPROM_ADDR 0xA0
#define EEPROM_TIMEOUT 100

uint32_t read_count = 0;
uint32_t write_count = 0;

int16_t fnd_eeprom_read_int16(uint16_t idx)
{
    read_count++;
    uint8_t data[2];
    if (HAL_I2C_IsDeviceReady(&EEPROM_I2C, EEPROM_ADDR, 2, EEPROM_TIMEOUT) != HAL_OK)
    {
        MX_I2C3_Init();
        return HAL_ERROR;
    }
    if (HAL_I2C_Mem_Read(&EEPROM_I2C, EEPROM_ADDR, 2 * idx, I2C_MEMADD_SIZE_16BIT, data, 2, EEPROM_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }
    return (int16_t)((data[0] << 8) + data[1]);
}

void fnd_eeprom_write_int16(uint16_t idx, int16_t value)
{
    write_count++;
    uint8_t data[2] = {value >> 8, value};
    if (HAL_I2C_IsDeviceReady(&EEPROM_I2C, EEPROM_ADDR, 2, EEPROM_TIMEOUT) != HAL_OK)
    {
        MX_I2C3_Init();
        return;
    }
    HAL_I2C_Mem_Write(&EEPROM_I2C, EEPROM_ADDR, 2 * idx, I2C_MEMADD_SIZE_16BIT, data, 2, EEPROM_TIMEOUT);
    osDelay(5);
}
