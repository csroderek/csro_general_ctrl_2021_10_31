#include "fnd_output.h"
#include "fnd_com.h"

void fnd_output_init(void)
{
    fnd_output_pwm_init();
    fnd_output_stepper_init();
}

void fnd_output_update(void)
{
    uint8_t do_value[6] = {0};
    for (uint8_t i = 0; i < 6; i++)
    {
        do_value[i] = sys_regs.inputs[OUTPUT_DO_START + i] == 0 ? 0 : 1;
    }
    fnd_output_gpio_write_do(do_value);

    uint16_t pwm_value[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        pwm_value[i] = (uint16_t)sys_regs.inputs[OUTPUT_PWM_START + i];
    }
    fnd_output_pwm_write_value(pwm_value);

    uint16_t stepper_value[4];
    for (uint8_t i = 0; i < 4; i++)
    {
        stepper_value[i] = (uint16_t)sys_regs.inputs[OUTPUT_STEPPER_START + i];
    }
    fnd_output_stepper_set_position(stepper_value);
}