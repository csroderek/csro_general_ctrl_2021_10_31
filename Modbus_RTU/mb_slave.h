#ifndef __MB_SLAVE_H
#define __MB_SLAVE_H

#define MB_SLAVE_BUFFER_LENGTH 512

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
    uint8_t rx_buf[MB_SLAVE_BUFFER_LENGTH];
    uint16_t rx_len;
    uint8_t tx_buf[MB_SLAVE_BUFFER_LENGTH];
    uint16_t tx_len;
    osSemaphoreId_t idle_sem;
    osTimerId_t idle_timer;
    uint8_t idle_timer_flag;
    modbus_regs *regs;
} modbus_slave;

void slave_init(modbus_slave *slave, modbus_port *port, uint16_t slave_id, modbus_regs *regs_ptr);
void slave_uart_idle(modbus_slave *slave);
void slave_set_tx_rx(modbus_slave *slave, uart_tx_rx_enum dir);
void slave_wait_request(modbus_slave *slave);

#endif
