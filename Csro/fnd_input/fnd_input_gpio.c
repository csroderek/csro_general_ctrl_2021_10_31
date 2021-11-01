#include "fnd_input.h"
#include "gpio.h"

GPIO_TypeDef *gpio_input_port[4] = {DI_01_GPIO_Port, DI_02_GPIO_Port, DI_03_GPIO_Port, DI_04_GPIO_Port};
uint16_t gpio_input_pin[4] = {DI_01_Pin, DI_02_Pin, DI_03_Pin, DI_04_Pin};

void fnd_input_gpio_read_di(uint8_t *values)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        values[i] = (HAL_GPIO_ReadPin(gpio_input_port[i], gpio_input_pin[i]) == GPIO_PIN_SET) ? 1 : 0;
    }
}

void fnd_input_gpio_read_id(uint8_t *values)
{
    HAL_GPIO_WritePin(ID_LD_GPIO_Port, ID_LD_Pin, GPIO_PIN_RESET);
    osDelay(1);
    HAL_GPIO_WritePin(ID_LD_GPIO_Port, ID_LD_Pin, GPIO_PIN_SET);
    values[7] = HAL_GPIO_ReadPin(ID_DATA_GPIO_Port, ID_DATA_Pin) == GPIO_PIN_SET ? 1 : 0;

    for (uint8_t i = 0; i < 7; i++)
    {
        HAL_GPIO_WritePin(ID_CLK_GPIO_Port, ID_CLK_Pin, GPIO_PIN_RESET);
        osDelay(1);
        HAL_GPIO_WritePin(ID_CLK_GPIO_Port, ID_CLK_Pin, GPIO_PIN_SET);
        values[6 - i] = HAL_GPIO_ReadPin(ID_DATA_GPIO_Port, ID_DATA_Pin) == GPIO_PIN_SET ? 1 : 0;
    }
}