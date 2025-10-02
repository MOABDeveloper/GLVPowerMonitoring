//Initializes the esp32 and the power IC, runs a simple low that reads voltage/current and prints/logs it. 
#include <stdint.h>
#include <INA232.hpp>
#include <I2C_CONFIG.hpp>
#include <driver/i2c.h>                 //lets esp32 act like a controller to talk to i2c devices
#include "freertos/FreeRTOS.h"


extern "C" void app_main(void)
{
    
    
    //superloop
    while(1){
        //delay
        vTaskDelay(SLEEP_TIME_MS/portTICK_PERIOD_MS)//13;35

        //store register address in buffer
        reg = CONFIG_REG;

        esp_ret = i2c_master_transmit_receive(INA232_dev, &reg, 1, data, 2, -1);
        if (esp_ret != ESP_OK){ 
            printf("Error: Failed to initialize I2C bus\r\n");
            abort();
        }
        //Convert data from Binary to Standard Numbers
    }
}

                    
