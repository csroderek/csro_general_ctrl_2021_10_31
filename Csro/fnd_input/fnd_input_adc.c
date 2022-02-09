#include "fnd_input.h"
#include "adc.h"
#include "math.h"

#define ADC_TOTAL_CH 13
#define DATA_PER_CH 10

uint32_t fnd_adc_data[ADC_TOTAL_CH * DATA_PER_CH];

static float get_channel_average(uint8_t ch_idx)
{
    float sum = 0;
    for (uint8_t i = 0; i < DATA_PER_CH; i++)
    {
        sum = sum + fnd_adc_data[ch_idx + i * ADC_TOTAL_CH];
    }
    return sum / DATA_PER_CH;
}

void fnd_input_adc_init(void)
{
    HAL_ADC_Start_DMA(&hadc1, fnd_adc_data, ADC_TOTAL_CH * DATA_PER_CH);
}

void fnd_input_adc_read_values(float *values)
{
    for (uint8_t i = 0; i < 10; i++)
    {
        values[i] = get_channel_average(i);
    }
}
