/* NotesController.h
 * 
 * Play up to 2 notes at a time, then release the sticks.
 * After the stick hits the note, it goes back to the wait position.
 * Two arms with 2 servos each, controling the horizontal angle and the stick hitting the xilophone.
 * 
 * Servos managed using Adafruit servo controller board PCA9685.
 * Musical Notes and Their Frequencies and Wavelengths https://www.liutaiomottola.com/formulae/freqtab.htm
 */ 

#ifndef NotesController_h
#define NotesController_h

//#include "Arduino.h"
#include <Wire.h>
#include <servo_PCA9685.h>
#include "A_config.h"
#ifdef USE_DEBUG
#include "DevTools.h"                             // Developer tools and utilities
#endif

enum NOTE_NAME { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NUMBER_OF_NOTE, NO_NOTE }; // Playable notes (C4=261.626 Hz, ... C5=523.251)
                                                  
enum NOTE_DURATIONS { ND16TH,                     // Note duration in 1/16 intervals
                      ND8TH, ND3EIGTH,
                      ND4TH, ND3FOURTH,
                      NDHALF,
                      ND1, ND1POINT5,
                      ND2, ND3,
                      ND4,ND6
                    };
typedef struct {                                  // 2 notes at a time for 2 arms to play, and duration until next note
  NOTE_NAME noteLeft;                             // Name of the note to play with the left arm
  NOTE_NAME noteRight;                            // Name of the note to play with the r9ight arm
  uint8_t duration;                               // Duration before playing the next notes
} NOTES;
    
class NotesController {
  public:
    enum SERVO_POSITION { WAIT_POSITION, PLAY_POSITION };

    typedef struct {                              // State of each arm
      SERVO_POSITION state;                       // State of the stick (WAIT_POSITION = nothing to do; PLAY_POSITION  = note played, need to reset)
      uint8_t waitAngle;                         // Angle in WAIT_POSITION state
      uint8_t playAngle;                          // Angle in PLAY_POSITION state
      unsigned long notePlayedAt;                 // Latest note time of play in milliseconds
    } SERVO_STATE;

    enum ARM_NAME { LEFT_ARM, RIGHT_ARM };
    
    typedef struct {                              // Map each note to an arm and an angle to be on top of the note
      NOTE_NAME noteName;                         // Name of the note for reference. Same as note index in array
      ARM_NAME armName;                           // 2 arms available for up to 2 notes played together
      uint8_t angle;                              // Angle to be on top of the note
    } NOTES_MAP;
    
    NotesController();                            // Constructor
    ~NotesController();                           // Destructor

    void play8Notes(uint8_t eightNotes);          // Play up to 8 notes simultaneously
    void play2Notes(NOTES notes);                 // Play up to 2 notes simultaneously
    void allServosToPlayPosition();               // All servos go to their play position
    void allServosToWaitPosition();               // All servos go to their wait position

  private:
    servo_PCA9685 servo = servo_PCA9685();

    SERVO_STATE _servoState[NUMBER_OF_ARMS] = {   // State of each individual arm
      { WAIT_POSITION, 60 , 90 , 0 },
      { WAIT_POSITION, 100 , 70 , 0 }
    };
//    unsigned long _playNoteDuration = 100;        // Time before moving back to wait position, in milliseconds

    NOTES_MAP _notesMap[NUMBER_OF_NOTE] = {       // Define how to reach each note
      { NOTE_C4, LEFT_ARM, 150 },
      { NOTE_D4, LEFT_ARM, 120 },
      { NOTE_E4, LEFT_ARM, 95 },
      { NOTE_F4, LEFT_ARM, 75 },
      { NOTE_G4, RIGHT_ARM, 90 },
      { NOTE_A4, RIGHT_ARM, 70 },
      { NOTE_B4, RIGHT_ARM, 50 },
      { NOTE_C5, RIGHT_ARM, 25 }
    };
                                                   // Note durations in ms - Keep in sync with enum NOTE_DURATIONS
int noteDurations[12] = { QUARTER_NOTE_TIME / 4,   // D16TH
                        QUARTER_NOTE_TIME / 2,     // D8TH
                        6 * QUARTER_NOTE_TIME / 8, // D3EIGTH
                        QUARTER_NOTE_TIME,         // D4TH
                        6 * QUARTER_NOTE_TIME / 4, // D3FOURTH
                        2 * QUARTER_NOTE_TIME,     // DHALF
                        4 * QUARTER_NOTE_TIME,     // D1
                        6 * QUARTER_NOTE_TIME,     // D1.5
                        8 * QUARTER_NOTE_TIME,     // D2
                        12 * QUARTER_NOTE_TIME,    // D3
                        16 * QUARTER_NOTE_TIME,    // D4
                        24 * QUARTER_NOTE_TIME     // D6
                      };
};

#endif // ifndef NotesController_h
