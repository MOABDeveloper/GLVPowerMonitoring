#include "driver/i2c_master.h"
#include "driver/i2c.h"

#include "esp_check.h"
#include <stdio.h>
#include <INA232.hpp>

static const i2c_port_num_t     I2C_PORT = I2C_NUM_0;                   //There are two ports for i2c, in the esp32
static const gpio_num_t         I2C_SDA_PIN = GPIO_NUM_6;               //GPIO number for SDA
static const gpio_num_t         I2C_SCL_PIN = GPIO_NUM_3;               //GPIO number for SCL
static const uint8_t            I2C_GLITCH_IGNORE_CNT = 7;              //represents number of i2c glitches to ignore
static const uint32_t           SLEEP_TIME_MS = 1000;                   //1000 ms sleep time delay




void I2C_Setup(){
    esp_err_t esp_ret; //esp return variable -> esp_err_t is the standard return type for ESP-IDF function
    i2c_master_bus_handle_t i2c_bus; //i2c bus handle (pointer-reference to i2c bus)
    i2c_master_dev_handle_t INA232_dev; //handle for i2c device on bus
    unint8_t reg; //Holds register address we are working with
    uint8_t data[2]; //Buffer for two bytes worth of data

    //Important to note youtube video i watched points to registers as so....

    unint16_t shunt_reg; // register data
    unint16_t bus_reg; // register data
    unint16_t curr_reg; // register data
    unint16_t pow_reg; // register data
    unint16_t alert_reg; //register data

    i2c_master_bus_config_t bus_config = { //bus_config struct
        .i2c_port = i2c_port, //esp32 has mutiple i2c controllers(ports) this variable selects one
        .sda_io_num = i2c_sda_pin, //variable sets the sda gpio pin number
        .scl_io_num = i2c_sda_pin, //variable sets the scl gpio pin number
        .clk_source = I2C_CLK_SRC_DEFAULT //chooses clock source for i2c timing -> usually left as default
        .glithc_ignore_cnt = i2c_glithc_ignore_cnt, //i2c lines are sensitive to short noise pulses (glitches), this tells the i2c controller to ignore glitches for up to 7 cycles
        .flags.enable_internal_pullup = false, //i2c requires pu's this enables esp32 internal pu on the pins
        //usually better to use external PU resistors ^
        //uint32_t allow_pd <- is it worth using this feature
        //the . before the struct points initalizes the variable to that struct field
        //an initalizer is when you decalre a varaiable and give it an inital value right away
    };

    //Initialize i2c bus 
        esp_ret = i2c_new_master(*bus_config, &i2c_bus);//points to configuration struct and new bus created by the driver
    //The built in funciton i2c_new_master does the following 
    // 1) allocates resources for the bus (driver data structures, buffers, etc)
    // 2)Configures the ESP32's hardeware i2c peripheral according to the bus_config struct
    // 3) Returns a handle (i2c_bus that you'll use to manage the i2c bus)

    //Initalization verification 
    if (esp_ret != ESP_OK){ 
        printf("Error: Failed to initialize I2C bus\r\n");
        abort();
    }

    //Set I2C device configuration
    i2c_device_config_t dev_config = {
        .dev_addr_length = 0, //7-bit address      
        .device_address = INA232_addr,                   
        .scl_speed_hz = INA232_scl_speed_hz ,               
    };

    //Initalize the INA232 i2c bus on the device 
    esp_ret = i2c_master_bus_add_device(i2c_bus, &dev_config, &INA232_addr)
    if (esp_ret != ESP_OK){ 
        printf("Error: Failed to initialize I2C bus\r\n");
        abort();
    }

    void CONFIG_INITALIZE(I2C_ADD ,CONFIG){

        esp_ret = i2c_master_transmit(i2c_bus, I2C_ADD, 1)

        if (esp_ret != ESP_OK){ 
            printf("Error: Failed to initialize I2C bus\r\n");
            abort();
        }
        esp_ret = i2c_master_transmit(i2c_bus, CONFIG, 1)

        if (esp_ret != ESP_OK){ 
            printf("Error: Failed to initialize I2C bus\r\n");
            abort();    
        }
        unint8_t MSB = 01001011
        unint8_t LSB = 00100111
        
         esp_ret = i2c_master_transmit(i2c_bus, CONFIG, 1)

        if (esp_ret != ESP_OK){ 
            printf("Error: Failed to initialize I2C bus\r\n");
            abort();
        }
        esp_ret = i2c_master_transmit(i2c_bus, CONFIG, 1)

        if (esp_ret != ESP_OK){ 
            printf("Error: Failed to initialize I2C bus\r\n");
            abort();
        }
        i2c_master_write_to_device()
    }
}

    } //..............................// <- made by Boots
    //Initialize the CONFIG Register..............

    

}