#include "fnd_input.h"
#include "adc.h"
#include "math.h"

#define ADC_TOTAL_CH 13
#define DATA_PER_CH 10

#define DP_START_CH 0
#define DP_END_CH 2

#define NTC_START_CH 3
#define NTC_END_CH 8

#define VAL_FB_START_CH 9
#define VAL_FB_END_CH 9

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

static float calculate_ntc_temperature(double res_value, double res_ref, double b_value)
{
    return (float)(1 / (((log(res_value / res_ref)) / b_value) + (1 / (273.15 + 25))) - 273.15);
}

static void fnd_input_adc_init_check(void)
{
    static uint8_t init_flag = 0;
    if (init_flag == 0)
    {
        HAL_ADC_Start_DMA(&hadc1, fnd_adc_data, ADC_TOTAL_CH * DATA_PER_CH);
        init_flag = 1;
    }
}

void fnd_input_adc_read_dp(float *values)
{
    fnd_input_adc_init_check();
    for (uint8_t i = 0; i < (DP_END_CH - DP_START_CH + 1); i++)
    {
        float dp_adc_value = get_channel_average(i + DP_START_CH);
        values[i] = dp_adc_value;
    }
}

void fnd_input_adc_read_ntc(float *values)
{
    fnd_input_adc_init_check();
    for (uint8_t i = 0; i < (NTC_END_CH - NTC_START_CH + 1); i++)
    {
        float ntc_adc_value = get_channel_average(i + NTC_START_CH);
        float ntc_resister_value = (float)10.0 * ntc_adc_value / (4095.1 - ntc_adc_value);
        values[i] = calculate_ntc_temperature(ntc_resister_value, 10.0, 3950);
    }
}

void fnd_input_adc_read_val_fb(float *values)
{
    fnd_input_adc_init_check();
    for (uint8_t i = 0; i < (VAL_FB_END_CH - VAL_FB_START_CH + 1); i++)
    {
        values[i] = get_channel_average(i + VAL_FB_START_CH);
    }
}
