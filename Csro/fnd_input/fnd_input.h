#ifndef FND_INPUT_H_
#define FND_INPUT_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

void fnd_input_init(void);
void fnd_input_update(void);

// fnd_input_gpio.c
void fnd_input_gpio_read_di(uint8_t *values);
void fnd_input_gpio_read_id(uint8_t *values);

// fnd_input_adc.c
void fnd_input_adc_init(void);
void fnd_input_adc_read_values(float *values);

// fnd_input_i2c.c
HAL_StatusTypeDef fnd_input_i2c_read_sht_temp_humi(uint8_t idx, float *values);
void fnd_input_i2c_read_sht(void);

// fnd_input_tim.c
void fnd_input_tim_input_capture_init(void);
void fnd_input_tim_input_read_pulses(uint16_t *values);

#endif
