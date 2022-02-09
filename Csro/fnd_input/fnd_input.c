#include "fnd_input.h"
#include "fnd_com.h"

#define DP_START_CH 0
#define DP_END_CH 2

#define NTC_START_CH 3
#define NTC_END_CH 8

#define VAL_FB_START_CH 9
#define VAL_FB_END_CH 9

static float calculate_ntc_temperature(double res_value, double res_ref, double b_value)
{
    return (float)(1 / (((log(res_value / res_ref)) / b_value) + (1 / (273.15 + 25))) - 273.15);
}

void fnd_input_init(void)
{
    fnd_input_adc_init();
    fnd_input_tim_input_capture_init();
}

void fnd_input_update(void)
{
    float adc_values[10];
    fnd_input_adc_read_values(adc_values);
    for (uint8_t i = 0; i < (DP_END_CH - DP_START_CH + 1); i++)
    {
        sys_regs.inputs[INPUT_DP_START + i] = adc_values[DP_START_CH + i];
    }
    for (uint8_t i = 0; i < (NTC_END_CH - NTC_START_CH + 1); i++)
    {
        float ntc_resister_value = (float)10.0 * adc_values[NTC_START_CH + i] / (4095.1 - adc_values[NTC_START_CH + i]);
        sys_regs.inputs[INPUT_NTC_START + i] = calculate_ntc_temperature(ntc_resister_value, 10.0, 3950);
    }
    for (uint8_t i = 0; i < (VAL_FB_END_CH - VAL_FB_START_CH + 1); i++)
    {
        sys_regs.inputs[INPUT_VAL_FB_START + i] = adc_values[VAL_FB_START_CH + i];
    }

    uint8_t di_values[4];
    fnd_input_gpio_read_di(di_values);
    for (uint8_t i = 0; i < 4; i++)
    {
        sys_regs.inputs[INPUT_DI_START + i] = di_values[i];
    }

    uint8_t id_values[8];
    fnd_input_gpio_read_id(id_values);
    for (uint8_t i = 0; i < 8; i++)
    {
        sys_regs.inputs[INPUT_ID_START + i] = id_values[i];
    }
}

void fnd_input_i2c_read_sht(void)
{
    float sht1_values[2] = {0};
    float sht2_values[2] = {0};
    HAL_StatusTypeDef status = fnd_input_i2c_read_sht_temp_humi(0, sht1_values);
    for (uint8_t i = 0; i < 2; i++)
    {
        sys_regs.inputs[INPUT_SHT1_START + i] = (status == HAL_OK) ? (int16_t)(sht1_values[i] * 10) : (-1);
    }
    status = fnd_input_i2c_read_sht_temp_humi(1, sht2_values);
    for (uint8_t i = 0; i < 2; i++)
    {
        sys_regs.inputs[INPUT_SHT2_START + i] = (status == HAL_OK) ? (int16_t)(sht2_values[i] * 10) : (-1);
    }
}