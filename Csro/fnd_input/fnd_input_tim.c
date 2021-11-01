#include "fnd_input.h"
#include "tim.h"

uint32_t spd_pulse[2];

static void fnd_input_tim_input_capture_init_check(void)
{
    static uint8_t init_flag = 0;
    if (init_flag == 0)
    {
        HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
        HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
        init_flag = 1;
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        spd_pulse[0]++;
    }
    else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
        spd_pulse[1]++;
    }
}

void fnd_input_tim_input_read_speed(uint16_t *values)
{
    fnd_input_tim_input_capture_init_check();
    for (uint8_t i = 0; i < 2; i++)
    {
        values[i] = spd_pulse[i];
        spd_pulse[i] = 0;
    }
}
