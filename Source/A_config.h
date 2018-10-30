/*
 * Global configuration parameters
 */

#ifndef Config_h
#define Config_h

// =========== LIBRARIES =========== //

// ======== COMPILE SETTINGS ======= //
#define VERSION "v1.0.4 - Oct. 25, 2018."

// ========== LED CONFIG =========== //
/* Uncomment the type of LED used. One defined at a time */
#define DIGITAL_LED
// #define RGB_LED
// #define NEOPIXEL_LED
/* Adjust settings to match your setup */
#define LED_1 LED_BUILTIN            // Heartbeat light
#define LED_AUTOBLINK_INTERVAL 5000  // in milliseconds
#define LED_AUTOBLINK_DURATION 50    // in milliseconds
#define LED_2 D6                     // Light on when button pushed

// ========== BUTTON CONFIG ======== //
/* Uncomment if push-button used */
#define USE_BUTTON
/* Adjust settings to match your setup */
#define BUTTON_DEBOUNCING 80         // Button debouncing time in milliseconds
#define BUTTON_DEBOUNCE_DELAY 5      // Button debouncing loop delay in milliseconds
#define BUTTON_1_PIN D8              // Push-button to change the behavior
#define BUTTON_1_ON_VALUE HIGH       // Connected to: ground=LOW, 5V=HIGH
#define BUTTON_1_AUTHORIZED true     // true=button used, false=button use denied

// ===== MUSIC SEQUENCER CONFIG ==== //
/* Adjust settings to match your setup */
//#define ATTACK_DELAY 100             // Repeat beacon attack delay in milliseconds
/* Timer delays in ms */
#define TEMPO 120                    // 120 quarters-notes fit into one minute of time. Tempo at discretion of musician
#define QUARTER_NOTE_TIME 60/TEMPO   // For tempo = 120, 1 quarter note = 500 milliseconds
#define DELAY_BETWEEN_NOTES_TO_SAVE_ENERGY 5
#define DELAY_BETWEEN_SONGS 10000    // Delay in milliseconds before playing the next song

// ======= DEV TOOLS CONFIG ======== //
#define USE_DEBUG                    // Uncomment to get debug messages in serial monitor
#define SERIAL_MONITOR_PRINT         // Uncomment to get debug prints in Serial Monitor

// ======= SERVOS ======== //
/* Adjust settings to match your setup */
#define MAX_SERVOS  16               // Max number of servos on the Adafruit servo controller
#define NUMBER_OF_ARMS 2             // Left arm + right arm
#define NUMBER_OF_SERVOS 4           // 2 left arm servos + 2 right arm servos
#define ARM_LEFT_SERVO_NUMBER 0      // Servo number for left arm
#define ARM_RIGHT_SERVO_NUMBER 4     // Servo number for right arm
#define STICK_LEFT_SERVO_NUMBER 8   // Servo number for left stick arm
#define STICK_RIGHT_SERVO_NUMBER 12   // Servo number for right stick arm
#define DELAY_BETWEEN_NOTES 200      // Delay in milliseconds before playing the next note
#define DELAY_SERVO_FIND_NOTE 100    // Delay in milliseconds to allow the servo to move above the note
#define DELAY_NOTE_STICK_DOWN 100    // Delay in milliseconds to allow the stick to play the note

#endif // ifndef Config_h
