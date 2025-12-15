#include "I2C.hpp"


static bool I2C_INITED = false;
static i2c_master_bus_handle_t i2c_bus;



esp_err_t I2C_BUS_INIT(void){

    if(I2C_INITED){return;}
    int i2c_master_port = 0;

    //Set the configure I2C bus
    i2c_master_bus_config_t i2c_bus_conf = {
        .i2c_port = I2C_PORT,
        .sda_io_num = I2C_MASTER_SDA,
        .scl_io_num = I2C_MASTER_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = I2C_GLITCH_ALLOWANCE,
        .flags={.enable_internal_pullup = true},
    };

    //Initalize the bus    
    esp_err_t error;
    error = i2c_new_master_bus(&i2c_bus_conf,&i2c_bus);
    if(error != ESP_OK){
        printf("ERROR: FAILED TO INITIALIZE I2C BUS");
        return error;
    }
    
    I2C_INITED = true;
    return ESP_OK;
}

esp_err_t I2C_add_device(i2c_addr_bit_len_t device_address_length,
                         uint16_t device_address, 
                         uint32_t device_clock_speed, 
                         i2c_master_bus_handle_t i2c_bus_handle,
                         i2c_master_dev_handle_t *i2c_device_handle){

    i2c_device_config_t add_dev = {
        .dev_addr_length = device_address_length,
        .device_address = device_address,
        .scl_speed_hz = device_clock_speed,
    };

    esp_err_t error;
    error = i2c_master_bus_add_device(i2c_bus_handle,&add_dev,i2c_device_handle);

    if(error != ESP_OK){
        printf("ERROR: FAILED TO ADD DEVICE TO I2C BUS");
        return error;
    }
    
    return ESP_OK;
}

i2c_master_bus_handle_t I2C_getBus(void) {
    return i2c_bus;
}

bool I2C_isInited(void) {
    return I2C_INITED;
}