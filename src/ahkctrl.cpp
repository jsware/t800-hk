/**
 * @file ahkctrl.cpp
 * @author John Scott
 * @brief Aerial Hunter-Killer (AHK) Controller
 * @version 1.0
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <AsyncTimer.h>
#include "IRLibRecvPCI.h"
#include "IRLibDecodeBase.h"
#include "IRLib_P01_NEC.h"
#include "ahkctrl.h"
#include "ahkfx.h"
#include "aerialhk.h"
#include "pinout.h"

// Definition of singleton AHKController.
AerialHunterKillerController AHKController;

// Asynchronous Timer.
AsyncTimer ATimer;

// Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(PIN_IR_RECEIVER);

// Create a decoder object 
IRdecodeNEC myDecoder;


/**
 * @brief Async timings.
 * 
 */
struct AsyncTiming {
  void (*callback)();
  unsigned long start;
  unsigned long repeat;
};

// Macros for AsyncTimings
#define AT_TIME(START, FN) {AerialHunterKillerController::FN, START, 0}
#define AT_THEN_EVERY(START, REPEAT, FN) {AerialHunterKillerController::FN, START, REPEAT}
#define END_TIMINGS {0,0,0}


//
// AHK Controller Constructor.
//
AerialHunterKillerController::
AerialHunterKillerController()
{
  // NOP
}


//
// Setup function.
//
void AerialHunterKillerController::
setup()
{
  Serial.println(F("\nSerial Control Online:"));
  Serial.print(CTL_VOLUP); Serial.println(F(": Volume Up"));
  Serial.print(CTL_VOLDN); Serial.println(F(": Volume Down"));
  Serial.print(CTL_POWER); Serial.println(F(": Tail Lights"));
  Serial.print(CTL_FNSTP); Serial.println(F(": Landing Lights"));
  Serial.print(CTL_STRPT); Serial.println(F(": Spot Lights"));
  Serial.print(CTL_MOVDN); Serial.println(F(": Forward"));
  Serial.print(CTL_MOVUP); Serial.println(F(": Reverse"));
  Serial.print(CTL_REWND); Serial.println(F(": Left"));
  Serial.print(CTL_PLAYP); Serial.println(F(": Center"));
  Serial.print(CTL_FASTF); Serial.println(F(": Right"));

  Serial.println(F("\nStarting Infra-Red Control"));
  myReceiver.enableIRIn();
  Serial.println(F("Infra-Red Control Online"));
}


//
// Loop handler.
//
void AerialHunterKillerController::
loop()
{
  char cmd = '\0';

  ATimer.handle();

  if(Serial.available()) {
    cmd = toupper(Serial.read());
  } else if (myReceiver.getResults()) {
    myDecoder.decode(); // Decode it
    cmd = translateIR(); // Translate to one of the CMD_* values.
    myReceiver.enableIRIn(); // Restart receiver for next code.
  }

  switch(cmd) {
    case CTL_POWER: // Power on/off sequences.
      if(!AerialHK.isTailLights()) {
        setTimings(POWER_ON);
      } else {
        setTimings(POWER_OFF);
      }
      break;

    case CTL_VOLUP: // Increase sound volume.
      AHKEffects.volUp();
      break;

    case CTL_VOLDN: // Decrease sound volume.
      AHKEffects.volDown();
      break;

    case CTL_PLAYP: // Play/Pause == centre model.
      AerialHK.tiltTo(AerialHunterKiller::TILT_CENTRE);
      AerialHK.turnTo(AerialHunterKiller::TURN_CENTRE);
      AerialHK.thrustTo(AerialHunterKiller::THRUST_CENTRE);
      break;

    case CTL_REWND: // Rewind == turn left.
      AerialHK.turnTo(AerialHunterKiller::TURN_MAX);
      break;

    case CTL_FASTF: // Fast forward == turn right.
      AerialHK.turnTo(AerialHunterKiller::TURN_MIN);
      break;

    case CTL_MOVDN: // Move down == tilt forward.
      if(AerialHK.getTilt() < AerialHunterKiller::TILT_CENTRE) {
        AerialHK.tiltTo(AerialHunterKiller::TILT_CENTRE);        
      } else {
        AerialHK.tiltTo(AerialHunterKiller::TILT_MAX);
      }
      break;

    case CTL_MOVUP: // Move up == tilt backwards.
      if(AerialHK.getTilt() > AerialHunterKiller::TILT_CENTRE) {
        AerialHK.tiltTo(AerialHunterKiller::TILT_CENTRE);        
      } else {
        AerialHK.tiltTo(AerialHunterKiller::TILT_MIN);
      }
      break;

    case CTL_FNSTP: // Function/stop == landinglights on/off.
      AerialHK.toggleLandingLights();
      break;

    case CTL_EQUAL: // Equal (EQ) == Plasma gun on/off.
      AerialHK.togglePlasmaGun();
      break;

    case CTL_STRPT: // ST/RPT == Search lights on/off.
      AerialHK.toggleSearchLights();
      break;

    case '0': // 0 To stop sound effects.
      AHKEffects.stop();
      break;

    case '1': // 1 to play cut scene 01.
      reset();
      setTimings(CUT_SCENE_01);
      break;
  }
}

void AerialHunterKillerController::blueFrontLightsOff() {
  AHKEffects.setBlueFrontLights(false);
}

void AerialHunterKillerController::blueFrontLightsOn() {
  AHKEffects.setBlueFrontLights(true);
}


void AerialHunterKillerController::landingLightsOff() {
  AerialHK.setLandingLights(false);
}

void AerialHunterKillerController::landingLightsOn() {
  AerialHK.setLandingLights(true);
}

void AerialHunterKillerController::playFlyMore() {
  AHKEffects.play(AerialHunterKillerEffects::SND_FLYMORE);
}

void AerialHunterKillerController::playLanding() {
  AHKEffects.play(AerialHunterKillerEffects::SND_LAND);
}

void AerialHunterKillerController::playScene01() {
  AHKEffects.play(AerialHunterKillerEffects::SND_SCENE_01);
}

void AerialHunterKillerController::playTakeOff() {
  AHKEffects.play(AerialHunterKillerEffects::SND_FLY);
}


void AerialHunterKillerController::redBackLightsOff() {
  AHKEffects.setRedBackLights(false);
}

void AerialHunterKillerController::redBackLightsOn() {
  AHKEffects.setRedBackLights(true);
}


void AerialHunterKillerController::
reset() {
  AHKEffects.stop();
  AHKEffects.setBlueFrontLights(false);
  AHKEffects.setRedBackLights(false);

  AerialHK.tiltTo(AerialHunterKiller::TILT_CENTRE);
  AerialHK.turnTo(AerialHunterKiller::TURN_CENTRE);
  AerialHK.thrustTo(AerialHunterKiller::THRUST_CENTRE);
  AerialHK.setLandingLights(false);
  AerialHK.setPlasmaGun(false);
  AerialHK.setSearchLights(false);
  AerialHK.setTailLights(false);
}

void AerialHunterKillerController::tailLightsOff() {
  AerialHK.setTailLights(false);
}

void AerialHunterKillerController::tailLightsOn() {
  AerialHK.setTailLights(true);
}

void AerialHunterKillerController::takeOff() {
  AerialHK.thrustForward();
  AerialHK.tiltTo(AerialHunterKiller::TILT_MAX);
}

char AerialHunterKillerController::
translateIR()
{
  char cmd='\0';
  // myDecoder.dumpResults(true);  // Now print results (false for less detail).

  switch(myDecoder.value) {
    case 0xFFFFFFFF: // Ignore Repeat
      break;  

    case 0xFFA25D: // Power On/Off
      cmd = CTL_POWER;
      break;
      
    case 0xFFE21D: // Func/Stop
      cmd = CTL_FNSTP;
      break;

    case 0xFF9867: // EQ
      cmd = CTL_EQUAL;
      break;

    case 0xFFB04F: // ST/REPT
      cmd = CTL_STRPT;
      break;

    case 0xFF629D: // Vol +
      cmd = CTL_VOLUP;
      break;

    case 0xFFA857: // Vol -
      cmd = CTL_VOLDN;
      break;
  
    case 0xFF22DD: // |<< (Rewind)
      cmd = CTL_REWND;
      break;

    case 0xFF02FD: // >|| (Play/Pause)
      cmd = CTL_PLAYP;
      break;

    case 0xFFC23D: // >>| (Fast Forward)
      cmd = CTL_FASTF;
      break;

    case 0xFFE01F: // V (Down)
      cmd = CTL_MOVDN;
      break;

    case 0xFF906F: // ^ (Up)
      cmd = CTL_MOVUP;
      break;

    case 0xFF6897:
      cmd = '0';
      break;

    case 0xFF30CF:
      cmd = '1';
      break;

    case 0xFF18E7:
      cmd = '2';
      break;

    case 0xFF7A85:
      cmd = '3';
      break;

    case 0xFF10EF:
      cmd = '4';
      break;

    case 0xFF38C7:
      cmd = '5';
      break;

    case 0xFF5AA5:
      cmd = '6';
      break;

    case 0xFF42BD:
      cmd = '7';
      break;

    case 0xFF4AB5:
      cmd = '8';
      break;

    case 0xFF52AD:
      cmd = '9';
      break;
  }

  return cmd;
}


//
// Search lights OFF.
//
void AerialHunterKillerController::searchLightsOff() {
  AerialHK.setSearchLights(false);
}


//
// Search lights ON.
//
void AerialHunterKillerController::searchLightsOn() {
  AerialHK.setSearchLights(true);
}


//
// Setup timings for given list of timings.
//
void AerialHunterKillerController::
setTimings(const struct AsyncTiming timings[])
{
  ATimer.cancelAll();

  if(timings) {
    for(int i = 0; timings[i].callback; ++i) {
      ATimer.setTimeout(timings[i].callback, timings[i].start);

      if(timings[i].repeat) {
        ATimer.delay(ATimer.setInterval(timings[i].callback,timings[i].repeat),timings[i].start);
      }
    }
  }
}

//
// Definitions of timings for activities.
//
const struct AsyncTiming AerialHunterKillerController::POWER_ON[] = {
  AT_TIME(0, tailLightsOn),
  AT_TIME(500, playTakeOff),
  AT_TIME(550, landingLightsOn),
  AT_TIME(5500, searchLightsOn),
  AT_TIME(6000, landingLightsOff),
  AT_THEN_EVERY(15000, 30000, playFlyMore),
  END_TIMINGS
};

const struct AsyncTiming AerialHunterKillerController::POWER_OFF[] = {
  AT_TIME(0, playLanding),
  AT_TIME(1000, landingLightsOn),
  AT_TIME(2000, searchLightsOff),
  AT_TIME(8000, landingLightsOff),
  AT_TIME(10000, tailLightsOff),
  END_TIMINGS
};

const struct AsyncTiming AerialHunterKillerController::CUT_SCENE_01[] = {
  AT_TIME(0, tailLightsOn),
  AT_TIME(0, playScene01),
  AT_TIME(2000, landingLightsOn),
  AT_TIME(9200, blueFrontLightsOn),
  AT_TIME(9300, redBackLightsOn),
  AT_TIME(9400, blueFrontLightsOff),
  AT_TIME(9500, redBackLightsOff),
  AT_TIME(11000, takeOff),
  AT_TIME(13000, searchLightsOn),
  AT_TIME(13000, landingLightsOff),
  END_TIMINGS
};
