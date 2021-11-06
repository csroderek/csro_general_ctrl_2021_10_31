#include "mb_slave.h"

static const uint8_t crc_hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};

/* Table of CRC values for low-order byte */
static const uint8_t crc_lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40};

static void slave_crc16(modbus_slave *slave, uint8_t *buffer)
{
    slave->crc_hi = 0xFF;
    slave->crc_lo = 0xFF;
    while (slave->buff_len--)
    {
        slave->buff_index = slave->crc_hi ^ *buffer++;
        slave->crc_hi = slave->crc_lo ^ crc_hi[slave->buff_index];
        slave->crc_lo = crc_lo[slave->buff_index];
    }
}

static osStatus_t slave_validate_cmd(modbus_slave *slave)
{
    if (slave->rx_len < 8 || slave->rx_buf[0] != slave->slave_id)
    {
        return osError;
    }
    slave->buff_len = slave->rx_len - 2;
    slave_crc16(slave, slave->rx_buf);
    if ((slave->crc_hi != slave->rx_buf[slave->rx_len - 2]) || (slave->crc_lo != slave->rx_buf[slave->rx_len - 1]))
    {
        return osError;
    }
    return osOK;
}

static void slave_handle_read_discs(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];

    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        uint16_t byte_count = (qty % 8 == 0) ? (qty / 8) : (qty / 8 + 1);
        uint8_t byte_data = 0;
        slave->tx_buf[slave->tx_len++] = slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = byte_count;

        for (uint16_t i = 0; i < byte_count * 8; i++)
        {
            if (i % 8 == 0)
            {
                byte_data = 0x00;
            }
            if (i < qty)
            {
                byte_data = (slave->regs->discs[addr + i] == 1) ? (byte_data >> 1 | 0x80) : (byte_data >> 1 & 0x7F);
            }
            else
            {
                byte_data = byte_data >> 1 & 0x7F;
            }
            if ((i + 1) % 8 == 0)
            {
                slave->tx_buf[slave->tx_len++] = byte_data;
            }
        }
    }
}

static void slave_handle_read_coils(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];

    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        uint16_t byte_count = (qty % 8 == 0) ? (qty / 8) : (qty / 8 + 1);
        uint8_t byte_data = 0;
        slave->tx_buf[slave->tx_len++] = slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = byte_count;

        for (uint16_t i = 0; i < byte_count * 8; i++)
        {
            if (i % 8 == 0)
            {
                byte_data = 0x00;
            }
            if (i < qty)
            {
                byte_data = (slave->regs->coils[addr + i] == 1) ? (byte_data >> 1 | 0x80) : (byte_data >> 1 & 0x7F);
            }
            else
            {
                byte_data = byte_data >> 1 & 0x7F;
            }
            if ((i + 1) % 8 == 0)
            {
                slave->tx_buf[slave->tx_len++] = byte_data;
            }
        }
    }
}

static void slave_handle_read_input_regs(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave->tx_buf[slave->tx_len++] = slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = qty * 2;
        for (uint16_t i = 0; i < qty; i++)
        {
            slave->tx_buf[slave->tx_len++] = slave->regs->inputs[i + addr] >> 8;
            slave->tx_buf[slave->tx_len++] = slave->regs->inputs[i + addr] & 0xFF;
        }
    }
}

static void slave_handle_read_holding_regs(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave->tx_buf[slave->tx_len++] = slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = qty * 2;
        for (uint16_t i = 0; i < qty; i++)
        {
            slave->tx_buf[slave->tx_len++] = slave->regs->holdings[i + addr] >> 8;
            slave->tx_buf[slave->tx_len++] = slave->regs->holdings[i + addr] & 0xFF;
        }
    }
}

static void slave_compose_write_reply_tx_buffer(modbus_slave *slave)
{
    slave->tx_buf[slave->tx_len++] = slave->rx_buf[1];
    slave->tx_buf[slave->tx_len++] = slave->rx_buf[2];
    slave->tx_buf[slave->tx_len++] = slave->rx_buf[3];
    slave->tx_buf[slave->tx_len++] = slave->rx_buf[4];
    slave->tx_buf[slave->tx_len++] = slave->rx_buf[5];
}

static void slave_handle_write_single_coil(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + 1 > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave_compose_write_reply_tx_buffer(slave);
        slave->regs->coils[addr] = (slave->rx_buf[4] == 0xFF) ? 1 : 0;
    }
}

static void slave_handle_write_multi_coils(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave_compose_write_reply_tx_buffer(slave);
        for (uint16_t i = 0; i < qty; i++)
        {
            slave->regs->coils[addr + i] = (slave->rx_buf[7 + i / 8] >> (i % 8)) & 0x01;
        }
    }
}

static void slave_handle_write_single_holding_reg(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + 1 > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave_compose_write_reply_tx_buffer(slave);
        slave->regs->holdings[addr] = slave->rx_buf[4] * 256 + slave->rx_buf[5];
    }
}

static void slave_handle_write_multi_holding_regs(modbus_slave *slave)
{
    uint16_t addr = slave->rx_buf[2] * 256 + slave->rx_buf[3];
    uint16_t qty = slave->rx_buf[4] * 256 + slave->rx_buf[5];
    slave->tx_len = 0;
    slave->tx_buf[slave->tx_len++] = slave->slave_id;
    if (addr + qty > MODBUS_REG_LENGTH)
    {
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x02;
    }
    else
    {
        slave_compose_write_reply_tx_buffer(slave);
        for (uint16_t i = 0; i < qty; i++)
        {
            slave->regs->holdings[addr + i] = slave->rx_buf[7 + 2 * i] * 256 + slave->rx_buf[8 + 2 * i];
        }
    }
}

static void slave_response(modbus_slave *slave)
{
    if (slave_validate_cmd(slave) != osOK)
    {
        return;
    }
    slave->func_code = slave->rx_buf[1];
    if (slave->func_code == MODBUS_FC_READ_DISCRETE_INPUTS)
    {
        slave_handle_read_discs(slave);
    }
    else if (slave->func_code == MODBUS_FC_READ_COILS)
    {
        slave_handle_read_coils(slave);
    }
    else if (slave->func_code == MODBUS_FC_READ_INPUT_REGISTERS)
    {
        slave_handle_read_input_regs(slave);
    }
    else if (slave->func_code == MODBUS_FC_READ_HOLDING_REGISTERS)
    {
        slave_handle_read_holding_regs(slave);
    }
    else if (slave->func_code == MODBUS_FC_WRITE_SINGLE_COIL)
    {
        slave_handle_write_single_coil(slave);
    }
    else if (slave->func_code == MODBUS_FC_WRITE_MULTIPLE_COILS)
    {
        slave_handle_write_multi_coils(slave);
    }
    else if (slave->func_code == MODBUS_FC_WRITE_SINGLE_REGISTER)
    {
        slave_handle_write_single_holding_reg(slave);
    }
    else if (slave->func_code == MODBUS_FC_WRITE_MULTIPLE_REGISTERS)
    {
        slave_handle_write_multi_holding_regs(slave);
    }
    else
    {
        slave->tx_len = 0;
        slave->tx_buf[slave->tx_len++] = slave->slave_id;
        slave->tx_buf[slave->tx_len++] = 0x80 + slave->rx_buf[1];
        slave->tx_buf[slave->tx_len++] = 0x01;
    }
    slave->buff_len = slave->tx_len;
    slave_crc16(slave, slave->tx_buf);
    slave->tx_buf[slave->tx_len++] = slave->crc_hi;
    slave->tx_buf[slave->tx_len++] = slave->crc_lo;
    slave_set_tx_rx(slave, tx);
    HAL_UART_Transmit_DMA(slave->uart_port->uart, slave->tx_buf, slave->tx_len);
}

static void ostimer_callback(void *args)
{
    modbus_slave *slave = args;
    if (slave->rx_len == (MB_SLAVE_BUFFER_LENGTH - slave->uart_port->uart->hdmarx->Instance->NDTR))
    {
        slave->idle_timer_flag = 1;
        osSemaphoreRelease(slave->idle_sem);
    }
}

void slave_init(modbus_slave *slave, modbus_port *port, uint16_t slave_id, modbus_regs *regs_ptr)
{
    slave->idle_sem = osSemaphoreNew(1, 0, NULL);
    slave->idle_timer = osTimerNew(ostimer_callback, osTimerOnce, (void *)slave, NULL);
    slave->uart_port = port;
    slave->slave_id = slave_id;
    slave->regs = regs_ptr;
    __HAL_UART_ENABLE_IT(slave->uart_port->uart, UART_IT_IDLE);
}

void slave_uart_idle(modbus_slave *slave)
{
    if (((READ_REG(slave->uart_port->uart->Instance->SR) & USART_SR_IDLE) != RESET) && ((READ_REG(slave->uart_port->uart->Instance->CR1) & USART_CR1_IDLEIE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(slave->uart_port->uart);
        slave->rx_len = MB_SLAVE_BUFFER_LENGTH - slave->uart_port->uart->hdmarx->Instance->NDTR;
        slave->idle_timer_flag = 0;
        osSemaphoreRelease(slave->idle_sem);
    }
}

void slave_set_tx_rx(modbus_slave *slave, uart_tx_rx_enum dir)
{
    HAL_GPIO_WritePin(slave->uart_port->gpio_port, slave->uart_port->gpio_pin, (dir == tx) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void slave_wait_request(modbus_slave *slave)
{
    while (osSemaphoreAcquire(slave->idle_sem, osWaitForever) == osOK)
    {
        if (slave->idle_timer_flag == 0)
        {
            osTimerStart(slave->idle_timer, 2);
        }
        else if (slave->idle_timer_flag == 1)
        {
            HAL_UART_DMAStop(slave->uart_port->uart);
            slave_response(slave);
            HAL_UART_Receive_DMA(slave->uart_port->uart, slave->rx_buf, MB_SLAVE_BUFFER_LENGTH);
        }
    }
}
