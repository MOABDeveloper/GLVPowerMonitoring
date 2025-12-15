
#include "components/I2C.hpp"
#include "components/INA236.hpp"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "FuseMonitor.h" 
      
int app_main(int argc, char const *argv[])
{
    

    //Define the ina236 device handle
    i2c_master_dev_handle_t ina236_handle;

    //Setup I2C bus
    ESP_ERROR_CHECK(
        I2C_BUS_INIT()
    );

    //Add ina236 device to I2C bus
    ESP_ERROR_CHECK(
        I2C_add_device( INA236::I2C_ADDR_MODE,
                        INA236::I2C_ADDRESS,
                        INA236::I2C_CLK_SPEED,
                        I2C_getBus(),
                        &ina236_handle)
    );

    //Create ina236 object
    INA236 ina_dev(ina236_handle);

    //I2C config message buffer
    uint8_t config_message[3] = {INA236::CONFIG,(uint8_t)(INA236::DEFAULT_CONFIG >> 8),(uint8_t)(INA236::DEFAULT_CONFIG & 0xFF)};
     
    //Configure the ina236 with default configuration
    i2c_master_transmit(ina236_handle,config_message,3,1000);



    return 0;
}