#include "DevTools.h"

//#include "Arduino.h"
//extern "C" {
//#include "user_interface.h"
//}

// ----- <constructor>
DevTools::DevTools() {}

// ----- <destructor>
DevTools::~DevTools() {/*nothing to destruct*/}

#ifdef SERIAL_MONITOR_PRINT
/* Print hex representation of buffer content to serial monitor */
void DevTools::printBufferToConsole(String title,
                                    char buffer[], 
									                  size_t numberOfChar, 
									                  bool continuous) {
  char printString[200];                                  // Max size of line printed
  
  sprintf(printString, "\n--> Start dump: %s (%d char.) <--", title.c_str(), numberOfChar);
  Serial.println(printString);

  for (int i=0; i<numberOfChar; i++) {
    if (continuous) {
      sprintf(printString, "%02X ", buffer[i]);
      Serial.print(printString);
    }
    else {
      sprintf(printString, "%02d: %02X ", i, buffer[i]);
      Serial.println(printString);
    }
  }

  if (continuous) { Serial.println(); }
  Serial.println("--> End dump <--");
}
#endif // #ifdef SERIAL_MONITOR_PRINT
