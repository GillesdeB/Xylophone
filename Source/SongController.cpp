/* 
 *  SongController.cpp
 */

#include "SongController.h"

// ----- <constructor>
SongController::SongController() { }

// ----- <destructor>
SongController::~SongController() { /*nothing to destruct*/ }

// ----- Select the next song
void SongController::incrementSelectedSong() {
  if (++selectedSong >= SONG_BEHAVIOR_ENUM_SIZE) {
    selectedSong = 0;
  }
#ifdef SERIAL_MONITOR_PRINT
  Serial.print("selectedSong = "); Serial.println(selectedSong);
#endif
}

// ----- Behavior - Just move servos for debug purpose
void SongController::playMoveServos() {             // ToDo: REMOVE WHEN MUSIC PLAYS CORrECTLY
  notesController.allServosToPlayPosition();
  delay(500);
  notesController.allServosToWaitPosition();
  delay(1000);
}

// ----- Behavior - Play all notes, one arm at a time
void SongController::playAllNotesSetup() {
  int tempo = 1.05;
  for (int thisNote = 0; thisNote < _allNotesSetupSize; thisNote++) {
    int noteDuration = (SongAllNotesSetup[thisNote].duration);
    notesController.play2Notes(SongAllNotesSetup[thisNote]);
#ifdef SERIAL_MONITOR_PRINT
    Serial.print("; Note duration =  "); Serial.println(noteDuration);
#endif
    delay(noteDuration);
  }
}


// ----- Behavior - Play "Jingle Bells"
void SongController::playJingleBells() {
  int tempo = 1.05;                                 // tempo is 1.05; increase to play it slower TODO: MAKE IT A GLOBAL VARIABLE
  for (int thisNote = 0; thisNote < _JingleBellsNotesSize; thisNote++) {
    int noteDuration = (SongJingleBells[thisNote].duration); //convert duration to time delay TODO: USE PREDEFINED DURATIONS 1/2, 1/4, ...
    notesController.play2Notes(SongJingleBells[thisNote]);
#ifdef SERIAL_MONITOR_PRINT
    Serial.print("; Note duration =  "); Serial.println(noteDuration);
#endif
    delay(noteDuration);                            // TODO: USE millis() TO DO PRECISE TIMING
  }
}

// ----- Behavior - Play "He is a Pirate"
void SongController::playPirates() {
  int tempo = 1.05;
  for (int thisNote = 0; thisNote < _piratesNotesSize; thisNote++) {
    int noteDuration = (SongPirates[thisNote].duration);
    notesController.play2Notes(SongPirates[thisNote]);
#ifdef SERIAL_MONITOR_PRINT
    Serial.print("; Note duration =  "); Serial.println(noteDuration);
#endif
    delay(noteDuration);
  }
}
/*
// ----- Behavior - Play "Crazy Frog"
void SongController::playCrazyFrog() {
  for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {
    int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
    //tone(8, CrazyFrog_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;  //Here 1.30 is tempo, decrease to play it faster
    //delay(pauseBetweenNotes);
    //noTone(8); //stop music on pin 8 
    }
}

// ----- Behavior - Play "Mario UnderWorld"
void SongController::playMarioUW() {
  for (int thisNote = 0; thisNote < (sizeof(MarioUW_note)/sizeof(int)); thisNote++) {
    int noteDuration = 1000 / MarioUW_duration[thisNote];//convert duration to time delay
    //tone(8, MarioUW_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.80;
    //delay(pauseBetweenNotes);
    //noTone(8); //stop music on pin 8 
  }
}

// ----- Behavior - Play "Titanic"
void SongController::playTitanic() {
  for (int thisNote = 0; thisNote < (sizeof(Titanic_note)/sizeof(int)); thisNote++) {
    int noteDuration = 1000 / Titanic_duration[thisNote];//convert duration to time delay
    //tone(8, Titanic_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 2.70;
    //delay(pauseBetweenNotes);
    //noTone(8); //stop music on pin 8 
  }
}
*/
void SongController::executeSong(int song) {
#ifdef SERIAL_MONITOR_PRINT
  Serial.print("SongController::executeSong() - songBehavior = "); Serial.println(song);
#endif

  switch (song) {
/*
    case _MoveServos:
      playMoveServos();
      break;
*/

    case _AllNotesSetup:
      playAllNotesSetup();
      break;
    case _Pirates:
      playPirates();
      break;
    case _JingleBells:
      playJingleBells();
      break;
/*
    case _CrazyFrog:
      playCrazyFrog();
      break;
    case _MarioUW:
      playMarioUW();
      break;        
    case _Titanic:
      playTitanic();
      break;
*/
    default:
#ifdef SERIAL_MONITOR_PRINT
      Serial.println("WARNING: behavior not recognized");
#endif
      break;
    }
}

void SongController::executeSong() {
  executeSong(selectedSong);
}
