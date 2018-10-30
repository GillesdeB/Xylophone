#ifndef DevTools_h
#define DevTools_h
/*
   This file contains developer tools and utilities.
 */
#include "Arduino.h"
#include "A_config.h"
//extern "C" {
//#include "user_interface.h"
//}

class DevTools {
    public:
        DevTools();                                 // Constructor
        ~DevTools();                                // Destructor
        
#ifdef SERIAL_MONITOR_PRINT
        void printBufferToConsole(String title, char buffer[], size_t numberOfChar, bool continuous);
#endif // #ifdef SERIAL_MONITOR_PRINT

    private:
    
};

#endif // ifndef DevTools_h
