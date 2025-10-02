#pragma once
#include <stdint.h>


struct INA232_REG{
    
    static const uint8_t CONFIG = 0x0;
    static const uint8_t SHUNT = 0x1;
    static const uint8_t BUS = 0x2;    
    static const uint8_t POWER = 0x3;
    static const uint8_t CURRENT = 0x4; 
    static const uint8_t CALIBRATION = 0x5;
    static const uint8_t ENABLE = 0x6;
    static const uint8_t ALERT = 0x7;
    static const uint8_t MANUFACTURER = 0x3E;
    static const uint8_t I2C_ADD = 0x40;
};
