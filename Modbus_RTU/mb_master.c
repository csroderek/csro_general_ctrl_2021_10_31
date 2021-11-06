#include "mb_master.h"

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

static void master_crc16(modbus_master *master, uint8_t *buffer)
{
    master->crc_hi = 0xFF;
    master->crc_lo = 0xFF;
    while (master->buff_len--)
    {
        master->buff_index = master->crc_hi ^ *buffer++;
        master->crc_hi = master->crc_lo ^ crc_hi[master->buff_index];
        master->crc_lo = crc_lo[master->buff_index];
    }
}

static osStatus_t master_validate_reply(modbus_master *master)
{
    if (master->rx_len < 5)
    {
        return osError;
    }
    master->buff_len = master->rx_len - 2;
    master_crc16(master, master->rx_buf);
    if ((master->crc_hi != master->rx_buf[master->rx_len - 2]) || (master->crc_lo != master->rx_buf[master->rx_len - 1]))
    {
        return osError;
    }
    if ((master->rx_buf[0] != master->slave_id) || (master->rx_buf[1] != master->func_code))
    {
        return osError;
    }
    return osOK;
}

static osStatus_t master_request(modbus_master *master, uint16_t timeout)
{
    master->buff_len = master->tx_len;
    master_crc16(master, master->tx_buf);
    master->tx_buf[master->tx_len++] = master->crc_hi;
    master->tx_buf[master->tx_len++] = master->crc_lo;

    osSemaphoreAcquire(master->idle_sem, 0);
    HAL_UART_Receive_DMA(master->uart_port->uart, master->rx_buf, MB_MASTER_BUFFER_LENGTH);

    master_set_tx_rx(master, tx);
    HAL_UART_Transmit_DMA(master->uart_port->uart, master->tx_buf, master->tx_len);
    while (osSemaphoreAcquire(master->idle_sem, timeout) == osOK)
    {
        if (master->idle_timer_flag == 0)
        {
            osTimerStart(master->idle_timer, 2);
        }
        else if (master->idle_timer_flag == 1)
        {
            HAL_UART_DMAStop(master->uart_port->uart);
            if (master_validate_reply(master) == osOK)
            {
                master->com_status = osOK;
                return osOK;
            }
            master->com_status = osErrorParameter;
            master->com_err_cnt++;
            return osError;
        }
    }
    HAL_UART_DMAStop(master->uart_port->uart);
    master->com_err_cnt++;
    master->com_status = osErrorTimeout;
    return osError;
}

static void ostimer_callback(void *args)
{
    modbus_master *master = args;
    if (master->rx_len == (MB_MASTER_BUFFER_LENGTH - master->uart_port->uart->hdmarx->Instance->NDTR))
    {
        master->idle_timer_flag = 1;
        osSemaphoreRelease(master->idle_sem);
    }
}

void master_init(modbus_master *master, modbus_port *port, uint16_t slave_id)
{
    master->idle_sem = osSemaphoreNew(1, 0, NULL);
    master->idle_timer = osTimerNew(ostimer_callback, osTimerOnce, (void *)master, NULL);
    master->uart_port = port;
    master->slave_id = slave_id;
    __HAL_UART_ENABLE_IT(master->uart_port->uart, UART_IT_IDLE);
}

void master_set_tx_rx(modbus_master *master, uart_tx_rx_enum dir)
{
    HAL_GPIO_WritePin(master->uart_port->gpio_port, master->uart_port->gpio_pin, (dir == tx) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void master_uart_idle(modbus_master *master)
{
    if (((READ_REG(master->uart_port->uart->Instance->SR) & USART_SR_IDLE) != RESET) && ((READ_REG(master->uart_port->uart->Instance->CR1) & USART_CR1_IDLEIE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(master->uart_port->uart);
        master->rx_len = MB_MASTER_BUFFER_LENGTH - master->uart_port->uart->hdmarx->Instance->NDTR;
        master->idle_timer_flag = 0;
        osSemaphoreRelease(master->idle_sem);
    }
}

static void master_compose_tx_buffer(modbus_master *master, uint16_t addr, uint8_t fc)
{
    master->tx_len = 0;
    master->func_code = fc;
    master->tx_buf[master->tx_len++] = master->slave_id;
    master->tx_buf[master->tx_len++] = master->func_code;
    master->tx_buf[master->tx_len++] = addr >> 8;
    master->tx_buf[master->tx_len++] = addr & 0xFF;
}

osStatus_t master_read_discs(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *result)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_READ_DISCRETE_INPUTS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if (master->rx_buf[2] != ((qty % 8 == 0) ? (qty / 8) : (qty / 8 + 1)))
        {
            return osError;
        }
        for (uint16_t i = 0; i < qty; i++)
        {
            result[i] = 0x01 & ((master->rx_buf[3 + i / 8]) >> (i % 8));
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_read_coils(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *result)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_READ_COILS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if (master->rx_buf[2] != ((qty % 8 == 0) ? (qty / 8) : (qty / 8 + 1)))
        {
            return osError;
        }
        for (uint16_t i = 0; i < qty; i++)
        {
            result[i] = 0x01 & ((master->rx_buf[3 + i / 8]) >> (i % 8));
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_read_input_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *result)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_READ_INPUT_REGISTERS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if (master->rx_buf[2] != qty * 2)
        {
            return osError;
        }
        for (uint16_t i = 0; i < qty; i++)
        {
            result[i] = master->rx_buf[3 + i * 2] * 256 + master->rx_buf[4 + i * 2];
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_read_holding_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *result)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_READ_HOLDING_REGISTERS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if (master->rx_buf[2] != qty * 2)
        {
            return osError;
        }
        for (uint16_t i = 0; i < qty; i++)
        {
            result[i] = master->rx_buf[3 + i * 2] * 256 + master->rx_buf[4 + i * 2];
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_write_single_coil(modbus_master *master, uint16_t addr, uint8_t value)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_WRITE_SINGLE_COIL);
    master->tx_buf[master->tx_len++] = value ? 0xFF : 0x00;
    master->tx_buf[master->tx_len++] = 0x00;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if ((master->rx_buf[2] * 256 + master->rx_buf[3] != addr) || (master->rx_buf[4] * 256 + master->rx_buf[5] != (value ? 0xFF00 : 0x0000)))
        {
            return osError;
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_write_multi_coils(modbus_master *master, uint16_t addr, uint16_t qty, uint8_t *value)
{
    uint8_t data_count = (qty % 8 == 0) ? (qty / 8) : (qty / 8 + 1);
    uint8_t data[32];
    for (uint8_t i = 0; i < data_count * 8; i++)
    {
        if (i < qty)
        {
            data[i / 8] = (value[i] == 1) ? ((data[i / 8] >> 1) | 0x80) : ((data[i / 8] >> 1) & 0x7F);
        }
        else
        {
            data[i / 8] = data[i / 8] >> 1;
        }
    }

    master_compose_tx_buffer(master, addr, MODBUS_FC_WRITE_MULTIPLE_COILS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    master->tx_buf[master->tx_len++] = data_count;

    for (uint8_t i = 0; i < data_count; i++)
    {
        master->tx_buf[master->tx_len++] = data[i];
    }

    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if ((master->rx_buf[2] * 256 + master->rx_buf[3] != addr) || (master->rx_buf[4] * 256 + master->rx_buf[5] != qty))
        {
            return osError;
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_write_single_holding_reg(modbus_master *master, uint16_t addr, int16_t value)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_WRITE_SINGLE_REGISTER);
    master->tx_buf[master->tx_len++] = value >> 8;
    master->tx_buf[master->tx_len++] = value & 0xFF;
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if ((master->rx_buf[2] * 256 + master->rx_buf[3] != addr) || (master->rx_buf[4] * 256 + master->rx_buf[5] != value))
        {
            return osError;
        }
        return osOK;
    }
    return osError;
}

osStatus_t master_write_multi_holding_regs(modbus_master *master, uint16_t addr, uint16_t qty, int16_t *value)
{
    master_compose_tx_buffer(master, addr, MODBUS_FC_WRITE_MULTIPLE_REGISTERS);
    master->tx_buf[master->tx_len++] = qty >> 8;
    master->tx_buf[master->tx_len++] = qty & 0xFF;
    master->tx_buf[master->tx_len++] = qty * 2;
    for (uint16_t i = 0; i < qty; i++)
    {
        master->tx_buf[master->tx_len++] = value[i] >> 8;
        master->tx_buf[master->tx_len++] = value[i] & 0xFF;
    }
    if (master_request(master, MB_MASTER_REQUEST_TIMEOUT) == osOK)
    {
        if ((master->rx_buf[2] * 256 + master->rx_buf[3] != addr) || (master->rx_buf[4] * 256 + master->rx_buf[5] != qty))
        {
            return osError;
        }
        return osOK;
    }
    return osError;
}
