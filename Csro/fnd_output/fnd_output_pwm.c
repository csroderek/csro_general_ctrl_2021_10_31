#include "fnd_output.h"
#include "tim.h"

static void fnd_output_pwm_check_init(void)
{
    static uint8_t init_flag = 0;
    if (init_flag == 0)
    {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
        init_flag = 1;
    }
}

void fnd_output_pwm_write_value(uint16_t *values)
{
    fnd_output_pwm_check_init();
    if (values[0] < 1000)
    {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t)(values[0] / 1));
    }

    if (values[1] < 1000)
    {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint16_t)(values[1] / 1));
    }

    if (values[2] < 1000)
    {
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (uint16_t)(values[2] / 1));
    }
}