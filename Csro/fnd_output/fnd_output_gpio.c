#include "fnd_output.h"
#include "gpio.h"

GPIO_TypeDef *relay_port[6] = {RLY_01_GPIO_Port, RLY_02_GPIO_Port, RLY_03_GPIO_Port, RLY_04_GPIO_Port, RLY_05_GPIO_Port, RLY_06_GPIO_Port};
uint16_t relay_pin[6] = {RLY_01_Pin, RLY_02_Pin, RLY_03_Pin, RLY_04_Pin, RLY_05_Pin, RLY_06_Pin};

void fnd_output_gpio_write_do(uint8_t *values)
{
    for (uint8_t i = 0; i < 6; i++)
    {
        HAL_GPIO_WritePin(relay_port[i], relay_pin[i], (values[i] == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
}
