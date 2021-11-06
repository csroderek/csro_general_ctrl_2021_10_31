#ifndef __MB_MASTER_H
#define __MB_MASTER_H

#define MB_MASTER_BUFFER_LENGTH 512
#define MB_MASTER_REQUEST_TIMEOUT 500

#include "mb_config.h"

typedef struct
{
    modbus_port *uart_port;
    uint8_t slave_id;
    uint8_t func_code;

    uint8_t crc_hi;
    uint8_t crc_lo;
    uint16_t buff_len;
    uint16_t buff_index;

    uint8_t rx_buf[MB_MASTER_BUFFER_LENGTH];
    uint16_t rx_len;
    uint8_t tx_buf[MB_MASTER_BUFFER_LENGTH];
    uint16_t tx_len;

    osSemaphoreId_t idle_sem;
    osTimerId_t idle_timer;
    uint8_t idle_timer_flag;

    osStatus_t com_status;
    uint32_t com_err_cnt;
} modbus_master;

void master_init(modbus_master *master, modbus_port *port, uint16_t slave_id);
void master_uart_idle(modbus_master *master);
void master_set_tx_rx(modbus_master *master, uart_tx_rx_enum dir);

osStatus_t master_read_discs(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *result);
osStatus_t master_read_coils(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *result);
osStatus_t master_read_input_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *result);
osStatus_t master_read_holding_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *result);
osStatus_t master_write_single_coil(modbus_master *master, uint16_t addr, uint8_t value);
osStatus_t master_write_multi_coils(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *value);
osStatus_t master_write_single_holding_reg(modbus_master *master, uint16_t addr, int16_t value);
osStatus_t master_write_multi_holding_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *value);

#endif
