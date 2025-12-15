#ifndef _I2C_HPP_
#define _I2C_HPP_

#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"


static const i2c_port_num_t I2C_PORT = I2C_NUM_0;           //Let ESP-IDF decide the -1.
static const gpio_num_t I2C_MASTER_SDA = GPIO_NUM_44;
static const gpio_num_t I2C_MASTER_SCL = GPIO_NUM_42;
static const int I2C_MASTER_FREQ = 3'000'000;                 
static const uint8_t I2C_GLITCH_ALLOWANCE = 7;             //Allow this many glitches on the I2C bus. ( 7 is typical)


esp_err_t I2C_BUS_INIT(void);

esp_err_t I2C_add_device(i2c_addr_bit_len_t device_address_length,
                         uint16_t device_address, 
                         uint32_t device_clock_speed, 
                         i2c_master_bus_handle_t i2c_bus_handle,
                         i2c_master_dev_handle_t *i2c_device_handle);

i2c_master_bus_handle_t I2C_getBus(void);
bool I2C_isInited(void);

#endif