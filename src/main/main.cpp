
#include "components/I2C.hpp"
#include "components/INA232.hpp"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "FuseMonitor.h" 
      
int app_main(int argc, char const *argv[])
{
    

    //Define the INA232 device handle
    i2c_master_dev_handle_t ina232_handle;

    //Setup I2C bus
    ESP_ERROR_CHECK(
        I2C_BUS_INIT()
    );

    //Add INA232 device to I2C bus
    ESP_ERROR_CHECK(
        I2C_add_device( INA232::I2C_ADDR_MODE,
                        INA232::I2C_ADDRESS,
                        INA232::I2C_CLK_SPEED,
                        I2C_getBus(),
                        &ina232_handle)
    );

    //Create INA232 object
    INA232 ina_dev(ina232_handle);

    //I2C config message buffer
    uint8_t config_message[3] = {INA232::CONFIG,(uint8_t)(INA232::DEFAULT_CONFIG >> 8),(uint8_t)(INA232::DEFAULT_CONFIG & 0xFF)};
     
    //Configure the INA232 with default configuration
    i2c_master_transmit(ina232_handle,config_message,3,1000);



    return 0;
}