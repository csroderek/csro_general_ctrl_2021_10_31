#ifndef FND_EEPROM_H_
#define FND_EEPROM_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

extern osMutexId_t i2c1_mutexHandle;

int16_t fnd_eeprom_read_int16(uint16_t idx);
void fnd_eeprom_write_int16(uint16_t idx, int16_t value);

#endif
