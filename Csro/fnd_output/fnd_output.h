#ifndef FND_OUTPUT_H_
#define FND_OUTPUT_H_

#include "stm32f4xx_hal.h"

typedef enum
{
    STOP = 0,
    UP_EXCITE = 1,
    UP = 2,
    DOWN_EXCITE = 3,
    DOWN = 4
} stepper_mode;

typedef struct
{
    GPIO_TypeDef *gpio_port[4];
    uint16_t gpio_pin[4];

    stepper_mode mode;

    uint16_t up_excite_cnt;
    uint16_t down_excite_cnt;

    uint16_t target_pos;
    uint16_t current_pos;

    uint16_t phase;

} stepper_motor;

// fnd_output_gpio.c
void fnd_output_gpio_write_do(uint8_t *values);

// fnd_output_pwm.c
void fnd_output_pwm_write_value(uint16_t *values);

// fnd_output_stepper.c
void fnd_output_stepper_set_position(uint16_t *values);
void fnd_output_stepper_10ms_tick(void);

#endif
