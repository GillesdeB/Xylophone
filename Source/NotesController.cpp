/*
 * NotesController.cpp
 */
#include "NotesController.h"

// ----- <constructor>
NotesController::NotesController() {                          // Attach the servos to their pins
#ifdef SERIAL_MONITOR_PRINT
    Serial.println("NotesController()");
#endif
  servo.begin();
}

// ----- <destructor>
NotesController::~NotesController() {                         // Detach the servos
#ifdef SERIAL_MONITOR_PRINT
    Serial.println("~NotesController()");
#endif
}

// ----- Play up to 2 notes simultaneously. Move the servos so the hammer hits the expected notes on the xylophone
void NotesController::play2Notes(NOTES notes) {
#ifdef SERIAL_MONITOR_PRINT
    Serial.print("play2Notes(): ");
    Serial.print(" noteLeft "); Serial.print(notes.noteLeft);
    Serial.print(", noteRight "); Serial.print(notes.noteRight);
    Serial.print(", duration "); Serial.print(notes.duration);
#endif
//  uint8_t _arm;
  uint8_t _angle;
  
  if (notes.noteLeft != NO_NOTE) {                            // Position above note to play with the left arm
//    _arm = _notesMap[notes.noteLeft].armName;
    _angle = _notesMap[notes.noteLeft].angle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Left arm "); Serial.print(ARM_LEFT_SERVO_NUMBER); Serial.print(", Angle "); Serial.print(_angle);
#endif
    servo.moveServo(ARM_LEFT_SERVO_NUMBER, _angle);
  }
  
  if (notes.noteRight != NO_NOTE) {                            // Position note to play with the right arm
//    _arm = _notesMap[notes.noteRight].armName;
    _angle = _notesMap[notes.noteRight].angle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Right arm "); Serial.print(ARM_RIGHT_SERVO_NUMBER); Serial.print(", Angle "); Serial.print(_angle);
#endif
    servo.moveServo(ARM_RIGHT_SERVO_NUMBER, _angle);
  }

  delay(DELAY_SERVO_FIND_NOTE);                               //Allow the servo to move above the note

  if (notes.noteLeft != NO_NOTE) {                            // Play note with the left stick
//    _arm = _notesMap[notes.noteLeft].armName;
    _angle = _servoState[LEFT_ARM].playAngle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Left arm "); Serial.print(STICK_LEFT_SERVO_NUMBER);
    Serial.print(", Angle "); Serial.print(_angle);
    Serial.print(", Left stick down ");
#endif
    servo.moveServo(STICK_LEFT_SERVO_NUMBER, _angle);
  }
  
  if (notes.noteRight != NO_NOTE) {                            // Play note with the right stick
//    _arm = _notesMap[notes.noteRight].armName;
    _angle = _servoState[RIGHT_ARM].playAngle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Right arm "); Serial.print(STICK_RIGHT_SERVO_NUMBER);
    Serial.print(", Angle "); Serial.print(_angle);
    Serial.print(", Right stick down ");
#endif
    servo.moveServo(STICK_RIGHT_SERVO_NUMBER, _angle);
  }
  
  delay(DELAY_NOTE_STICK_DOWN);

  if (notes.noteLeft != NO_NOTE) {                            // Release left arm stick
//    _arm = LEFT_ARM;
    _angle = _servoState[LEFT_ARM].waitAngle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Left arm "); Serial.print(STICK_LEFT_SERVO_NUMBER);
    Serial.print(", Angle "); Serial.print(_angle);
    Serial.print(", Left stick up ");
#endif
    servo.moveServo(STICK_LEFT_SERVO_NUMBER, _angle);
  }
  
  if (notes.noteRight != NO_NOTE) {                            // Release right arm stick
//    _arm = RIGHT_ARM;
    _angle = _servoState[RIGHT_ARM].waitAngle;
#ifdef SERIAL_MONITOR_PRINT
    Serial.print(" Right arm "); Serial.print(STICK_RIGHT_SERVO_NUMBER);
    Serial.print(", Angle "); Serial.print(_angle);
    Serial.print(", Right stick up ");
#endif
    servo.moveServo(STICK_RIGHT_SERVO_NUMBER, _angle);
  }
}

// ----- Play up to 8 notes simultaneously. The hammers hit their respective notes on the xylophone
void NotesController::play8Notes(uint8_t eightNotes) {
  // TEST: Drive all servos one at a time
#ifdef SERIAL_MONITOR_PRINT
    Serial.println("play8Notes()");
#endif
  for (uint8_t servonum = 0; servonum < MAX_SERVOS; servonum++) {
    for (uint8_t i = 0; i < 255; i++) {
      servo.moveServo(servonum, i);
    }
    delay(200);
    for (uint8_t i = 254; i > 0; i--) {
      servo.moveServo(servonum, i);
    }
    delay(200);
  }
  /*
  uint8_t _servoNumber;
  SERVO_POSITION _servoPosition;
  
  switch (eightNotes) {
    case NOTE_C3:
      _servoNumber = 0;
      _servoPosition = PLAY_NOTE;
      Servo1.write(_servoState[_servoNumber].playAngle);
      break;
    case NOTE_D3:
      _servoNumber = 0;
      _servoPosition = PLAY_NOTE;
      Servo2.write(_servoState[_servoNumber].playAngle);
      break;
    case NOTE_E3:
      _servoNumber = 0;
      _servoPosition = PLAY_NOTE;
      Servo3.write(_servoState[_servoNumber].playAngle);
      break;
    case 0:                                 // No note
      allServosToResetPosition();
      _servoNumber = 99;
      break;
    default:                                // Unknown note
      allServosToResetPosition();
      _servoNumber = 99;
  }
  if (_servoNumber < NUMBER_OF_SERVOS) {
    _servoState[_servoNumber].state = _servoPosition;
    _servoState[_servoNumber].notePlayedAt = millis();
  }
  */
  /*
  // NEED TO CYCLE EACH BIT AND ACTIVATE OR RESET EACH CORRESPONDING SERVO
  Servo1.write(_servoState[0].playAngle);
  Servo1.write(_servoState[0].resetAngle);

  for(int i=0; i<NUMBER_OF_SERVOS; i++) {
    _servoState[i].state = RESET;
  }*/

  delay(DELAY_BETWEEN_NOTES);
}

// ----- All servos go to their individual play position
void NotesController::allServosToPlayPosition() {
  play8Notes(B11111111);
}

// ----- All servos go to their individual reset position
void NotesController::allServosToWaitPosition() {
  play8Notes(B00000000);
}
