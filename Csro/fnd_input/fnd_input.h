#ifndef FND_INPUT_H_
#define FND_INPUT_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

// fnd_input_gpio.c
void fnd_input_gpio_read_di(uint8_t *values);
void fnd_input_gpio_read_id(uint8_t *values);

// fnd_input_adc.c
void fnd_input_adc_read_dp(float *values);
void fnd_input_adc_read_ntc(float *values);
void fnd_input_adc_read_val_fb(float *values);

// fnd_input_i2c.c
void fnd_input_i2c_read_sht(float *values);

// fnd_input_tim.c
void fnd_input_tim_input_read_speed(uint16_t *values);

#endif
