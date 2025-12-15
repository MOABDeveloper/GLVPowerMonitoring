//falling edge interrupt
#include "FuseMonitor.h"
#include "esp_log.h"

//initailize object 
//:: -> scope resolution operator
FuseMonitor::FuseMonitor(gpio_num_t pin, int canID) { //constructor is an object containing our pin number and corresponding can ID

    //save pin number and CAN ID to the private variables     
    _pin = pin;  //when a constructor runs it is important to note that 'pin' and 'canID' no longer exist in memory, refer to them using _pin and _canID
    _canID = canID;

    //initalize flags to false
    _fuseBlownFlag = false; 

}

void FuseMonitor::FuseInit(){

//intialzing empty struct, can pass fields within instead... doesn't really matter though
    gpio_config_t io_config = {

        //configure the specific pin using the bitmask shift
        .pin_bit_mask = (1ULL << _pin),

        //configure the pin mode
        .mode = GPIO_MODE_INPUT,

        //disabling the pullup/pulldown resistors of the IO 
        .pull_up_en = GPIO_PULLUP_DISABLE,

        //disabling the pullup/pulldown resistors of the IO 
        .pull_down_en = GPIO_PULLDOWN_DISABLE,

        //configure the interupt type
        .intr_type = GPIO_INTR_NEGEDGE, 

};



    //passing config struct pointer into the config function
    gpio_config(&io_config); //where is function defined ? 

    //sets up your central interrupt control(allows per-pin GPIO interrupt handlers.)
    gpio_install_isr_service(0);

    //Call this function after using gpio_install_isr_service() to install the driver's GPIO ISR handler service.
    gpio_isr_handler_add(_pin, isrHandler, (void*) this); // args -> (pin, ISR function, current objects pointer), 'this' is the pointer to the current cpp object being used

    //does isrHanlder nned to have a return? 
}

/*static void IRAM_ATTR*/ void FuseMonitor::isrHandler(void* arg){

    //taking the passed generic pointer and making it of type FuseMonitor -> why not have FuseMonitor* instead of void*
    
    FuseMonitor* curObject = (FuseMonitor*) arg; //curObject is now a pointer of type FuseMonitor, is this type casting? 

    curObject->_fuseBlownFlag=true; //static functions don't belong to any specific object instance and therefore you must explicitly write field updates to the obj

}
 
bool FuseMonitor::checkBlown(){

    if (_fuseBlownFlag){
        _fuseBlownFlag = false; //resetst the interrupt immediately so we aren't constabtly gettign this interupt 
    //basic if statement exit in cpp
    }
    return false; 
}

