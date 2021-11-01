#include "fnd_input.h"
#include "i2c.h"

#define SHT_ADDR (0x44 << 1)
#define I2C_TIMEOUT 100

I2C_HandleTypeDef *sht_i2c[2] = {&hi2c1, &hi2c3};

static HAL_StatusTypeDef sht_write_cmd(I2C_HandleTypeDef *hi2c, uint16_t cmd)
{
    uint8_t buff[2] = {cmd >> 8, cmd};
    return HAL_I2C_Master_Transmit(hi2c, SHT_ADDR, buff, 2, I2C_TIMEOUT);
}

static uint8_t calculate_crc(const uint8_t *data, size_t length)
{
    uint8_t crc = 0xff;
    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (size_t j = 0; j < 8; j++)
        {
            if ((crc & 0x80u) != 0)
            {
                crc = (uint8_t)((uint8_t)(crc << 1u) ^ 0x31u);
            }
            else
            {
                crc <<= 1u;
            }
        }
    }
    return crc;
}

HAL_StatusTypeDef fnd_input_i2c_read_sht_temp_humi(uint8_t idx, float *values)
{
    uint8_t buff[6] = {0};

    if (HAL_I2C_IsDeviceReady(sht_i2c[idx], SHT_ADDR, 10, I2C_TIMEOUT) != HAL_OK)
    {
        if (idx == 0)
        {
            MX_I2C1_Init();
        }
        else if (idx == 1)
        {
            MX_I2C3_Init();
        }
        return HAL_ERROR;
    }

    if (sht_write_cmd(sht_i2c[idx], 0x240B) != HAL_OK)
    {
        return HAL_ERROR;
    }

    osDelay(50);

    if (HAL_I2C_Master_Receive(sht_i2c[idx], SHT_ADDR | 0x01, buff, 6, I2C_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (calculate_crc(buff, 2) == buff[2] && calculate_crc(&buff[3], 2) == buff[5])
    {
        uint16_t temp_value = ((uint16_t)buff[0] << 8) | buff[1];
        values[0] = -45 + 175 * ((float)temp_value / 65535);

        uint16_t humi_value = ((uint16_t)buff[3] << 8) | buff[4];
        values[1] = 100 * ((float)humi_value / 65535);
        return HAL_OK;
    }
    return HAL_ERROR;
}
