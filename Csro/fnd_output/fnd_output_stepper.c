#include "fnd_output.h"
#include "gpio.h"

#define EXCITE_TICKS 5

stepper_motor motor[4];

GPIO_TypeDef *stepper_port[16] = {STEP_A1_GPIO_Port, STEP_A2_GPIO_Port, STEP_A3_GPIO_Port, STEP_A4_GPIO_Port,
                                  STEP_A5_GPIO_Port, STEP_A6_GPIO_Port, STEP_A7_GPIO_Port, STEP_A8_GPIO_Port,
                                  STEP_B1_GPIO_Port, STEP_B2_GPIO_Port, STEP_B3_GPIO_Port, STEP_B4_GPIO_Port,
                                  STEP_B5_GPIO_Port, STEP_B6_GPIO_Port, STEP_B7_GPIO_Port, STEP_B8_GPIO_Port};

uint16_t stepper_pin[16] = {STEP_A1_Pin, STEP_A2_Pin, STEP_A3_Pin, STEP_A4_Pin,
                            STEP_A5_Pin, STEP_A6_Pin, STEP_A7_Pin, STEP_A8_Pin,
                            STEP_B1_Pin, STEP_B2_Pin, STEP_B3_Pin, STEP_B4_Pin,
                            STEP_B5_Pin, STEP_B6_Pin, STEP_B7_Pin, STEP_B8_Pin};

static void fnd_output_stepper_tick(stepper_motor *motor)
{
    if (motor->current_pos == motor->target_pos)
    {
        motor->mode = STOP;
        motor->up_excite_cnt = 0;
        motor->down_excite_cnt = 0;
    }
    else if (motor->current_pos < motor->target_pos)
    {
        motor->down_excite_cnt = 0;
        if (motor->up_excite_cnt < EXCITE_TICKS)
        {
            motor->mode = UP_EXCITE;
            motor->up_excite_cnt = motor->up_excite_cnt + 1;
        }
        else
        {
            motor->mode = UP;
        }
    }
    else if (motor->current_pos > motor->target_pos)
    {
        motor->up_excite_cnt = 0;
        if (motor->down_excite_cnt < EXCITE_TICKS)
        {
            motor->mode = DOWN_EXCITE;
            motor->down_excite_cnt = motor->down_excite_cnt + 1;
        }
        else
        {
            motor->mode = DOWN;
        }
    }

    if (motor->mode == STOP)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            HAL_GPIO_WritePin(motor->gpio_port[i], motor->gpio_pin[i], GPIO_PIN_RESET);
        }
    }
    else if (motor->mode == UP_EXCITE || motor->mode == DOWN_EXCITE)
    {
        HAL_GPIO_WritePin(motor->gpio_port[0], motor->gpio_pin[0], (motor->phase == 0 || motor->phase == 1 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[1], motor->gpio_pin[1], (motor->phase == 1 || motor->phase == 2 || motor->phase == 3) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[2], motor->gpio_pin[2], (motor->phase == 3 || motor->phase == 4 || motor->phase == 5) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[3], motor->gpio_pin[3], (motor->phase == 5 || motor->phase == 6 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (motor->mode == UP)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            HAL_GPIO_WritePin(motor->gpio_port[i], motor->gpio_pin[i], GPIO_PIN_RESET);
        }
        motor->current_pos = motor->current_pos + 1;
        motor->phase = (motor->phase + 1) % 8;
        HAL_GPIO_WritePin(motor->gpio_port[0], motor->gpio_pin[0], (motor->phase == 0 || motor->phase == 1 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[1], motor->gpio_pin[1], (motor->phase == 1 || motor->phase == 2 || motor->phase == 3) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[2], motor->gpio_pin[2], (motor->phase == 3 || motor->phase == 4 || motor->phase == 5) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[3], motor->gpio_pin[3], (motor->phase == 5 || motor->phase == 6 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (motor->mode == DOWN)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            HAL_GPIO_WritePin(motor->gpio_port[i], motor->gpio_pin[i], GPIO_PIN_RESET);
        }
        motor->current_pos = motor->current_pos - 1;
        motor->phase = (motor->phase + 7) % 8;
        HAL_GPIO_WritePin(motor->gpio_port[0], motor->gpio_pin[0], (motor->phase == 0 || motor->phase == 1 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[1], motor->gpio_pin[1], (motor->phase == 1 || motor->phase == 2 || motor->phase == 3) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[2], motor->gpio_pin[2], (motor->phase == 3 || motor->phase == 4 || motor->phase == 5) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_port[3], motor->gpio_pin[3], (motor->phase == 5 || motor->phase == 6 || motor->phase == 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void fnd_output_stepper_init(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            motor[i].gpio_port[j] = stepper_port[i * 4 + j];
            motor[i].gpio_pin[j] = stepper_pin[i * 4 + j];
        }
        motor[i].current_pos = 1200;
        motor[i].down_excite_cnt = 0;
        motor[i].mode = STOP;
        motor[i].phase = 0;
        motor[i].target_pos = 0;
        motor[i].up_excite_cnt = 0;
    }
}

void fnd_output_stepper_set_position(uint16_t *values)
{
    motor[0].target_pos = values[0];
    motor[1].target_pos = values[1];
    motor[2].target_pos = values[2];
    motor[3].target_pos = values[3];
}

void fnd_output_stepper_10ms_tick(void)
{
    fnd_output_stepper_tick(&motor[0]);
    fnd_output_stepper_tick(&motor[1]);
    fnd_output_stepper_tick(&motor[2]);
    fnd_output_stepper_tick(&motor[3]);
}
