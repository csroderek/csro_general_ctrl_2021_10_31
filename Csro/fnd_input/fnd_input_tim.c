#include "fnd_input.h"
#include "tim.h"

uint16_t spd_pulse[2];

void fnd_input_tim_input_capture_init(void)
{
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
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

void fnd_input_tim_input_read_pulses(uint16_t *values)
{
    values[0] = spd_pulse[0];
    values[1] = spd_pulse[1];
}
