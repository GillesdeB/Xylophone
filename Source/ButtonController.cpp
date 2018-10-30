#include "ButtonController.h"

// ----- <constructor>
ButtonController::ButtonController() {}

// ----- <destructor>
ButtonController::~ButtonController() {/*nothing to destruct*/}

// ----- Assign pin and level
void ButtonController::pin(int pin, int onValue, bool buttonAuthorized) {
#ifdef SERIAL_MONITOR_PRINT
  Serial.print("Start ButtonController::pin() - Pin: "); Serial.print(pin);
  Serial.print(", onValue: "); Serial.print(onValue);
  Serial.print(", buttonAuthorized: "); Serial.print(buttonAuthorized);
#endif
  _pin = pin;
  _onValue = onValue;
  _buttonAuthorized = buttonAuthorized;
  
  if (_onValue == HIGH) {
    pinMode(_pin, INPUT_PULLUP);
#ifdef SERIAL_MONITOR_PRINT
    Serial.println(", INPUT_PULLUP");
#endif
  }
  else {
    pinMode(_pin, INPUT);
#ifdef SERIAL_MONITOR_PRINT
    Serial.println(", INPUT");
#endif
  }
}

// ----- Check if the pushbutton is pressed
bool ButtonController::checkPushButton () {
  bool buttonPressed = false;
  unsigned long startTime = millis();

  while ((digitalRead(_pin) == _onValue) && (_buttonAuthorized == true)) {
      pushbuttonLed.on();

      if((millis() - startTime) > BUTTON_DEBOUNCING) {
#ifdef SERIAL_MONITOR_PRINT
  Serial.println("ButtonController::checkPushButton() - button pressed");
#endif
          buttonPressed = true;
          while(digitalRead(_pin) == _onValue) { delay(BUTTON_DEBOUNCE_DELAY); }
      }
   }
   pushbuttonLed.off();
   
   return buttonPressed;
}
