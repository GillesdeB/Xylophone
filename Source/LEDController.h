/*
   LEDController.h
   This file manages internal and external LEDs.
 */
#ifndef LEDController_h
#define LEDController_h

#include "Arduino.h"
#include "A_config.h"
//extern "C" {
//  #include "user_interface.h"
//}

class LEDController {
  public:
    enum LED_MODE { OFF = 0, ON = 1 };
    enum LED_ONOFF { REGULAR = 0, REVERSED = 1 };
    
    LEDController();                            // Constructor
    ~LEDController();                           // Destructor
    
    void pin(byte pin, uint8_t onType);         // Assign pin and level
    void blinkParameters(unsigned long interval, unsigned long duration);
    void on();                                  // Set LED on
    void off();                                 // Set LED off
    void blink(int time);                       // Blink LED n times
    void autoBlink();                           // Blink LED on predefined elapsed time

  private:
    byte _ledPin;
    uint8_t _ledOn = HIGH;
    uint8_t _ledOff = LOW;
    uint8_t _mode = LED_MODE::OFF;
    
    unsigned long _blinkInterval = 0;           // In milliseconds
    unsigned long _blinkDuration = 0;           // In milliseconds
    unsigned long _actualDelay = 0;             // In milliseconds
    unsigned long _previousBlink = 0;           // In milliseconds

    int led_State = LOW;
};

#endif // ifndef LEDController_h
