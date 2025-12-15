#pragma once //prevents double inclusion of files 
#include "driver/gpio.h"
#include "esp_attr.h"

//GPIO assignments
#define MAIN_STAT GPIO_NUM_6
#define ACCU_STAT GPIO_NUM_41
#define INV_STAT GPIO_NUM_2
#define FRONT_STAT GPIO_NUM_40
#define REAR_STAT GPIO_NUM_1
#define COOLING_STAT GPIO_NUM_39
#define RECU_STAT GPIO_NUM_38
#define EXTRA1_STAT GPIO_NUM_37
#define EXTRA2_STAT GPIO_NUM_36

//CAN Fault ID
//Temporary ID's
#define CAN_ID_FUSE_MAIN    1
#define CAN_ID_FUSE_ACCU    2
#define CAN_ID_FUSE_INV     3
#define CAN_ID_FUSE_FRONT   4
#define CAN_ID_FUSE_REAR    5
#define CAN_ID_FUSE_COOLING 6
#define CAN_ID_FUSE_RECU    7
#define CAN_ID_FUSE_EXTRA1  8
#define CAN_ID_FUSE_EXTRA2  9


class FuseMonitor {
public: //can be accessed by main  
 
    //constructor object, pass which pin is being watched and which ID is correspondant 
    FuseMonitor(gpio_num_t pin, int canID);

    //Configures the IO pin and attatches the intterupt
    void FuseInit();

    //efficient function that returns 'true' if the fuse blew last time checked (allows main loop to handle event safely)
    bool checkBlown(); // might not need this function -> or can include in the interrupt function   
    
private: //cannot be accessed by main, prevents anyone from changing code (safety precaution) -> mostly best practice  
    
    gpio_num_t _pin; //Remembers the pin
    int _canID; //Remembers the corresponding CAN ID 

    //volatile is requred as the ISR can change the value when the main loop reads it (prevents it from being cached)
    volatile bool _fuseBlownFuse; 

    //This is the interrupt service routine 
    static void IRAM_ATTR isrHandler(void* arg); 
    //void* is a generic memory address, no specific data type
    //IRAM_ATTR forces compiler to put the specific function into an intenral RAM which is accesbile and fast, and is generally a safer place for storage -> is a pre-processor macro not really a directive 
    //The ISR should not send any complex messaging format, just throw a flag indicaating that the event occured
    //ESP32 hardware interupt controller is 

};

// void FuseMonitor get_canID(){
// canID = FuseMonitor.canID;
// }