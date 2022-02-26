#ifndef FND_COM_H_
#define FND_COM_H_

#include "stm32f4xx_hal.h"
#include "mb_slave.h"
#include "mb_master.h"

#define INPUT_DP_START 0
#define INPUT_NTC_START 3
#define INPUT_VAL_FB_START 9

#define INPUT_DI_START 10
#define INPUT_ID_START 14

#define INPUT_SHT1_START 22
#define INPUT_SHT2_START 24

#define OUTPUT_DO_START 100
#define OUTPUT_PWM_START 106
#define OUTPUT_STEPPER_START 109

extern modbus_regs sys_regs;
extern modbus_slave slaves[2];

void fnd_com_modbus_rtu_init(void);
void fnd_com_modbus_rtu_uart_idle_irq(UART_HandleTypeDef *huart);
void fnd_com_modbus_rtu_master1_read_write(void);
void fnd_com_modbus_rtu_slave1_wait(void);
void fnd_com_modbus_rtu_slave2_wait(void);

#endif
