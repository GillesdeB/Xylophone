/*
 * SongController.h
 * Song selection and execution.
 * Xylophone songs https://www.bing.com/images/search?q=notes+on+a+xylophone&id=E5D808B19DFC6BFA29BA5E1ECD107899F0D31149&FORM=IQFRBA
 */
#ifndef SongController_h
#define SongController_h
#include "Arduino.h"
#include "A_config.h"
#ifdef USE_DEBUG
#include "DevTools.h"                             // Developer tools and utilities
#endif

#include "NotesController.h"                      // Play the right note using the servos

extern NotesController   notesController;         // Physically play the notes using servos

class SongController {
  public:
    //enum songBehaviors { _MoveServos, _JingleBells, _Pirates, _CrazyFrog, _MarioUW, _Titanic, _max };
    enum songBehaviors { _AllNotesSetup, _Pirates, _JingleBells, _max };
#define SONG_BEHAVIOR_ENUM_SIZE _max              // Number of songs

    SongController();                             // Constructor
    ~SongController();                            // Destructor

    void incrementSelectedSong();
    void playMoveServos();
    void playAllNotesSetup();
    void playJingleBells();
    void playPirates();
    //void playCrazyFrog();
    //void playMarioUW();
    //void playTitanic();
    void executeSong(int song);
    void executeSong();
    
  private:
    int selectedSong = _AllNotesSetup;                  // Next song to play

/*-- "HE IS A PIRATE" song of Pirates of caribbean --*/
    static const int _piratesNotesSize = 29;      // Number of entries
    NOTES SongPirates [_piratesNotesSize] = {
      { NOTE_G4, NO_NOTE, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NO_NOTE, NOTE_A4, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NO_NOTE, NOTE_A4, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NO_NOTE, NOTE_A4, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NO_NOTE, NOTE_A4, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NO_NOTE, NOTE_A4, 1500},
      { NOTE_G4, NO_NOTE, 1000},
      { NOTE_E4, NO_NOTE, 1000},
      { NOTE_G4, NOTE_C5, 1000}
    };
    	
/*-- "Jingle Bells" song --*/
    static const int _JingleBellsNotesSize = 29;  // Number of entries
    NOTES SongJingleBells [_JingleBellsNotesSize] = {
      { NOTE_G4, NO_NOTE, NDHALF},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NO_NOTE, NOTE_A4, 1000},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NO_NOTE, NOTE_A4, 1000},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NO_NOTE, NOTE_A4, 1000},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NO_NOTE, NOTE_A4, 1000},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NO_NOTE, NOTE_A4, 1000},
      { NOTE_G4, NO_NOTE, 500},
      { NOTE_E4, NO_NOTE, 500},
      { NOTE_G4, NOTE_C5, 500}
    };

    // NO_NOTE;
    // LEFT: (NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4);
    // RIGHT: (NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5)

/*-- All notes played, one at a time --*/
    static const int _allNotesSetupSize = 8;       // Number of entries
#define _allNotesSetupDuration 2000
    NOTES SongAllNotesSetup [_allNotesSetupSize] = {
      { NOTE_C4, NO_NOTE, _allNotesSetupDuration},
      { NOTE_D4, NO_NOTE, _allNotesSetupDuration},
      { NOTE_E4, NO_NOTE, _allNotesSetupDuration},
      { NOTE_F4, NO_NOTE, _allNotesSetupDuration},
      { NO_NOTE, NOTE_G4, _allNotesSetupDuration},
      { NO_NOTE, NOTE_A4, _allNotesSetupDuration},
      { NO_NOTE, NOTE_B4, _allNotesSetupDuration},
      { NO_NOTE, NOTE_C5, _allNotesSetupDuration}
    };
 
};
#endif // ifndef SongController_h
