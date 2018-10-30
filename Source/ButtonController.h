/*
   ButtonController.h
   This file manages a pushbutton.
 */
#ifndef ButtonController_h
#define ButtonController_h
/*
   This file manages buttons.
 */
#include "Arduino.h"
#include "A_config.h"
#include "LEDController.h"

//extern "C" {
//  #include "user_interface.h"
//}
extern LEDController pushbuttonLed;             // LED used when button pushed

class ButtonController {
  public:    
    ButtonController();                         // Constructor
    ~ButtonController();                        // Destructor

    void pin(int pin, int onValue, bool buttonAuthorized);  // Assign pin and level
    bool checkPushButton();                     // Change behavioral state if pushbutton pressed
    
  private:
    int _pin;                                   // Pin assigned to the button
    int _onValue;                               // Value when button pressed (HIGH or LOW)
    bool _buttonAuthorized;                     // true=button used, false=button denied
};

#endif // ifndef ButtonController_h
