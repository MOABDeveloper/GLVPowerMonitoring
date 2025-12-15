#ifndef _INA236_HPP_
#define _INA236_HPP_

#include <stdint.h>
#include "driver/i2c_master.h"

class INA236{
    public:
        explicit INA236
    (i2c_master_dev_handle_t handle) : dev_handle(handle) {}
        i2c_master_dev_handle_t get_handle(){return dev_handle;}
        //Set up the configuration register for the INA236
    

        esp_err_t ina236_configure(uint16_t config_value){};

        //REGISTERS - INA236 DATASHEET SECTION 7.6.1
        static constexpr uint8_t CONFIG       = 0x0;
        static constexpr uint8_t SHUNT        = 0x1;
        static constexpr uint8_t BUS          = 0x2;
        static constexpr uint8_t POWER        = 0x3;
        static constexpr uint8_t CURRENT      = 0x4;
        static constexpr uint8_t CALIBRATION  = 0x5;
        static constexpr uint8_t ENABLE       = 0x6;
        static constexpr uint8_t ALERT        = 0x7;
        static constexpr uint8_t MANUFACTURER = 0x3E;
        static constexpr uint16_t DEFAULT_CONFIG = 0x4727;   //0b0100011100100111;

        // I2C settings
        static constexpr uint16_t          I2C_ADDRESS    = 0x40;            // A0 = GND
        static constexpr uint32_t          I2C_CLK_SPEED  = 400000;          // 400Khz
        static constexpr i2c_addr_bit_len_t I2C_ADDR_MODE = I2C_ADDR_BIT_LEN_7;

    private:
        i2c_master_dev_handle_t dev_handle;
};


#endif // ina236_HPP
