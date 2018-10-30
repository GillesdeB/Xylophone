/* 
 *  LEDController.cpp
 */
#include "LEDController.h"

// ----- <constructor>
LEDController::LEDController() { }

// ----- <destructor>
LEDController::~LEDController() {/*nothing to destruct*/}

// ----- Set pin and LED-on level
void LEDController::pin(byte pin, uint8_t onType){
#ifdef SERIAL_MONITOR_PRINT
  Serial.print("Start LEDController::pin() - Pin: "); Serial.print(pin); Serial.print(", onType: "); Serial.println(onType);
#endif
  _ledPin = pin;
  pinMode(_ledPin, OUTPUT);
  
  if (onType == HIGH) {
    _ledOn = HIGH;
    _ledOff = LOW;
  }
  else {
    _ledOn = LOW;
    _ledOff = HIGH;
  }
}

// ----- Set blink parameters
void LEDController::blinkParameters(unsigned long interval, unsigned long duration){
#ifdef SERIAL_MONITOR_PRINT
  Serial.print("LEDController::blinkParameters() - interval: "); Serial.print(interval); Serial.print(", duration: "); Serial.println(duration);
#endif
  _blinkInterval = interval;
  _blinkDuration = duration;
}

// ----- Turn the LED on
void LEDController::on(){
#ifdef SERIAL_MONITOR_PRINT
//  Serial.print("LEDController::on() - _ledPin: "); Serial.println(_ledPin);
#endif
  digitalWrite(_ledPin, _ledOn);        // Set the pin HIGH and thus turn LED on
  _mode = LED_MODE::ON;
  _actualDelay = _blinkDuration;
}
 
// ----- Turn the LED off
void LEDController::off(){
#ifdef SERIAL_MONITOR_PRINT
//  Serial.print("LEDController::off() - _ledPin: "); Serial.println(_ledPin);
#endif
  digitalWrite(_ledPin, _ledOff);       // Set the pin LOW and thus turn LED off
  _mode = LED_MODE::OFF;
  _actualDelay = _blinkInterval;
}
 
// ----- Blink the LED a number of times equal to the repeat paramterer
void LEDController::blink(int repeat){
  for (int i=0; i<repeat; i++) {
    on();                               //turn LED on
    delay(_blinkDuration);              //wait the wanted period
    off();                              //turn LED off
    delay(_blinkInterval);              //wait the wanted period
  }
}

// ----- Automatic blinking according to parameters
void LEDController::autoBlink() {
  unsigned long _currentTime = millis();
  
  if((_currentTime - _previousBlink) >= _actualDelay) {
    _previousBlink = _currentTime;   
    if (_mode == LED_MODE::OFF) {
      on();
    }
    else {
      off();
    }
  }
}
