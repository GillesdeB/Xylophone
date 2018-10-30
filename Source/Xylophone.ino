/* Xylophone.ino
 *  Play xylophone using in-memory music sheet and mallets moved by the servos
 *  
 *  Functions:
 *  - Blink the onboard blue LED as proof of life beacon
 *  - Different music sheet selected by pressing a pushbutton
 *  - Light an external LED when the pushbutton is pressed
 *  - Play the music using 2 arms driven by 2 servos each
 *  
 *  Hardware:
 *  - ESP8266-12
 *  - Internal LED connected on LED_BUILTIN for heartbeat
 *  - Push button to change the song connected on pin D8(yellow), ground(white, black), and +(red)
 *  - External LED for push-button-pressed visual clue connected on pin D6 and ground
 *  - Adafruit servo controller board PCA9685: 
 *    - connected to pins I2C D1(SCL-yellow), D2(SDA-orange), ground(black), +(red)
 *    - servo left horizontal connected to servo 0 pins
 *    - servo left stick connected to servo 4 pins
 *    - servo right horizontal connected to servo 8 pins
 *    - servo right stick connected to servo 12 pins
 *  - Wi-Fi connection from the ESP8266 unused
 *  
 *  Servos:
 *  - Arduino has a built-in function servo.write(degrees) to control servos.
 *  - Not all servos respect the same timings for all positions.
 *  - Usually: 1 ms = 0 degrees, 1.5 ms = 90 degrees, 2 ms = 180 degrees.
 *  - Some servos different ranges.
 *  - For better control, we can use the servo.writeMicroseconds(us) function, 
 *    which takes the exact number of microseconds as a parameter. Remember,
 *    1 millisecond equals 1,000 microseconds.
 *  - Servos do not need to be controlled by PWM pins - any digital pin will work.
 *  
 *  ToDo:
 *  
 *  Updated: 2018-10-06 Gilles de Bordeaux
 */

/* ========= libraries ========== */
#include <ESP8266WiFi.h>
//#include "Arduino.h"
#include "A_config.h"                             // Configuration parameters
#include "ButtonController.h"
#ifdef USE_DEBUG
#include "DevTools.h"                             // Developer tools and utilities
#endif
#include "LEDController.h"                        // Manage internal and external LED
#include "NotesController.h"                      // Servo controller playing the notes
#include "SongController.h"                       // Select and play songs
//#include "Musics.h"                               // Music sheet of the songs

/* ===== run-time variables ===== */
#ifdef USE_DEBUG
DevTools          devTools;                       // Development tools
#endif
ButtonController  pushbutton;                     // Pushbutton to select behavior
LEDController     heartbeatLed;                   // LED for heartbeat
LEDController     pushbuttonLed;                  // LED for button pushed
NotesController   notesController;                // Physically play the notes using servos
SongController    songController;                 // Select and play songs

/* ===== functions ===== */

// ----- Play xylophone music if the time is right 
void playXylophone() {
  uint32_t currentTime = millis();
  static uint32_t lastPlayTime = 0;
                                                  // Play a song at regular intervals
  if ((currentTime - lastPlayTime) > DELAY_BETWEEN_SONGS) {
    lastPlayTime = currentTime;
    songController.executeSong();
  }
  else {
    delay(DELAY_BETWEEN_NOTES_TO_SAVE_ENERGY);    // Sleep to save some energy
  }
}

// ----- Setup
void setup() {
  delay(500);                                     // Time to settle down
  
#ifdef SERIAL_MONITOR_PRINT
  Serial.begin(115200);                           // Serial link for debugging
  while (!Serial) { ; /* wait for serial port to connect. Needed for native USB port only */ }
  Serial.println("==> Starting Xylophone.ino <== ");
  Serial.println(VERSION);
#endif
  
  heartbeatLed.pin(LED_1, LOW);                   // Heartbeat LED parameters
  heartbeatLed.blinkParameters(LED_AUTOBLINK_INTERVAL, LED_AUTOBLINK_DURATION);
  pushbuttonLed.pin(LED_2, HIGH);                 // Button pushed LED parameters
                                                  // Push button parameters
  pushbutton.pin(BUTTON_1_PIN, BUTTON_1_ON_VALUE, BUTTON_1_AUTHORIZED);
   
#ifdef SERIAL_MONITOR_PRINT
  Serial.println("setup() done");
#endif
}

// ----- Loop
void loop(){
  heartbeatLed.autoBlink();                       // Flash internal LED as proof of life       

  if (pushbutton.checkPushButton()) {             // If push button pressed
    songController.incrementSelectedSong();       // Update behavior state
  }

  playXylophone();                                // Continue playing xylophone music
}
