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
#define IR_SMALLD_NEC
#include <IRsmallDecoder.h>
#include "aerialhk.h"
#include "ahkctrl.h"
#include "ahkfx.h"
#include "pinout.h"

//
// Control inputs...
//
#define CTL_POWER '*' ///< Power On/off.
#define CTL_VOLUP '+' ///< Volume up.
#define CTL_VOLDN '-' ///< Volume down.
#define CTL_PLAYP '|' ///< Play/Pause.
#define CTL_REWND '<' ///< Rewind.
#define CTL_FASTF '>' ///< Fast Forward.
#define CTL_MOVDN 'V' ///< Move Down.
#define CTL_MOVUP '^' ///< Move Up.
#define CTL_FNSTP '!' ///< Func/Stop.
#define CTL_EQUAL '=' ///< EQ.
#define CTL_STRPT '/' ///< ST/REPT.

IRsmallDecoder irDecoder(PIN_IR_RECEIVER);
irSmallD_t irData;


//
// Timed effects...
//
AsyncTimer ATimer(40); ///< Asynchronous Timer.

struct AsyncTiming {
  void (*callback)();
  unsigned long start;
  unsigned long repeat;
};

// Macros for AsyncTimings
#define AT_TIME(START, FN) {FN, START, 0}
#define AT_THEN_EVERY(START, REPEAT, FN) {FN, START, REPEAT}
#define END_TIMINGS {0,0,0}

static const struct AsyncTiming POWER_ON[] PROGMEM = {
  AT_TIME(0, tailLightsOn),
  AT_TIME(500, playTakeoff),
  AT_TIME(550, landingLightsOnOff),
  AT_TIME(5500, searchLightsOn),
  AT_THEN_EVERY(15000, 30000, playFlyMore),
  END_TIMINGS
};

const struct AsyncTiming POWER_OFF[] PROGMEM = {
  AT_TIME(0, playLanding),
  AT_TIME(500, tiltLevel),
  AT_TIME(1000, landingLightsOnOff),
  AT_TIME(1500, turnCentre),
  AT_TIME(2000, searchLightsOff),
  AT_TIME(3500, thrustHover),
  AT_TIME(10000, tailLightsOff),
  END_TIMINGS
};

const struct AsyncTiming CUT_SCENE_01[] PROGMEM = {
  AT_TIME(0, tailLightsOn),
  AT_TIME(0, playScene01),
  AT_TIME(2000, landingLightsOnOff),
  AT_TIME(6000, tiltForward),
  AT_TIME(9200, blueFrontLightsFlash),
  AT_TIME(9300, redBackLightsFlash),
  AT_TIME(13000, searchLightsOn),
  AT_TIME(13000, tiltBackward),
  AT_TIME(14000, turnRight),
  AT_TIME(16500, blueFrontLightsFlash),
  AT_TIME(18000, redBackLightsFlash),
  AT_TIME(20000, tiltForward),
  AT_TIME(22000, plasmaGunOn200),
  AT_TIME(22000, blueFrontLightsFlash),
  AT_TIME(22700, blueFrontLightsFlash),
  AT_TIME(23060, redBackLightsFlash),
  AT_TIME(24000, turnLeft),
  AT_TIME(28000, tiltLevel),
  AT_TIME(32000, turnRight),
  AT_TIME(36000, tiltForward),
  AT_TIME(38600, redBackLightsFlash),
  AT_TIME(40500, blueFrontLightsFlashOn),
  END_TIMINGS
};


static char translateIR(long value) {
  char cmd='\0';

  switch(value) {
    case 0xFFFFFFFF: // Ignore Repeat
      Serial.println(value);
      break;  

    case 0x45: // Power On/Off
      cmd = CTL_POWER;
      break;
      
    case 0x47: // Func/Stop
      cmd = CTL_FNSTP;
      break;

    case 0x19: // EQ
      cmd = CTL_EQUAL;
      break;

    case 0xD: // ST/REPT
      cmd = CTL_STRPT;
      break;

    case 0x46: // Vol +
      cmd = CTL_VOLUP;
      break;

    case 0x15: // Vol -
      cmd = CTL_VOLDN;
      break;
  
    case 0x44: // |<< (Rewind)
      cmd = CTL_REWND;
      break;

    case 0x40: // >|| (Play/Pause)
      cmd = CTL_PLAYP;
      break;

    case 0x43: // >>| (Fast Forward)
      cmd = CTL_FASTF;
      break;

    case 0x7: // V (Down)
      cmd = CTL_MOVDN;
      break;

    case 0x9: // ^ (Up)
      cmd = CTL_MOVUP;
      break;

    case 0x16:
      cmd = '0';
      break;

    case 0xC:
      cmd = '1';
      break;

    case 0x18:
      cmd = '2';
      break;

    case 0x5E:
      cmd = '3';
      break;

    case 0x8:
      cmd = '4';
      break;

    case 0x1C:
      cmd = '5';
      break;

    case 0x5A:
      cmd = '6';
      break;

    case 0x42:
      cmd = '7';
      break;

    case 0x52:
      cmd = '8';
      break;

    case 0x4A:
      cmd = '9';
      break;

    default:
      Serial.print(F("IR? "));
      Serial.println(value, HEX);
  }

  return cmd;
}


//
// Setup timings for given list of timings.
//
void setTimings(const struct AsyncTiming timings[]) {
  struct AsyncTiming t;
  int i = 0;

  ATimer.cancelAll();

  do {
    memcpy_P(&t, &timings[i], sizeof(t));

    if(t.callback) {
      ATimer.setTimeout(t.callback, t.start);

      if(t.repeat) {
        ATimer.delay(ATimer.setInterval(t.callback,t.repeat),t.start);
      }
    }
    ++i;
  } while(t.callback);
}


void resetAHKCtrl() {
  stopPlaying();
  blueFrontLightsOff();
  redBackLightsOff();

  tiltLevel();
  turnCentre();
  thrustHover();
  
  tailLightsOff();
  landingLightsOff();
  searchLightsOff();
  plasmaGunOff();
}


void setupAHKCtrl() {
  // NOP
}


void loopAHKCtrl() {
  char cmd = '\0';

  ATimer.handle();

  if(Serial.available()) {
    cmd = toupper(Serial.read());
  } else if (irDecoder.dataAvailable(irData) && !irData.keyHeld) {
    cmd = translateIR(irData.cmd); // Translate to one of the CMD_* values.
  }

  switch(cmd) {
    case CTL_POWER: // Power on/off sequences.
      if(!isTailLights()) {
        setTimings(POWER_ON);
      } else {
        setTimings(POWER_OFF);
      }
      break;

    case CTL_VOLUP: // Increase sound volume.
      volumeUp();
      break;

    case CTL_VOLDN: // Decrease sound volume.
      volumeDown();
      break;

    case CTL_PLAYP: // Play/Pause == centre model.
      tiltLevel();
      turnCentre();
      thrustHover();
      break;

    case CTL_REWND: // Rewind == turn left.
      turnLeft();
      // AerialHK.turnTo(AerialHunterKiller::TURN_MAX);
      break;

    case CTL_FASTF: // Fast forward == turn right.
      turnRight();
      // AerialHK.turnTo(AerialHunterKiller::TURN_MIN);
      break;

    case CTL_MOVDN: // Move down == tilt forward.
      if(getTilt() < AHK_TILT_CENTRE) {
        tiltLevel();
      } else {
        tiltForward();
      }
      break;

    case CTL_MOVUP: // Move up == tilt backwards.
      if(getTilt() > AHK_TILT_CENTRE) {
        tiltLevel();
      } else {
        tiltBackward();
      }
      break;

    case CTL_FNSTP: // Function/stop == landinglights on/off.
      if(isLandingLights()) {
        landingLightsOff();
      } else {
        landingLightsOn();
      }
      break;

    case CTL_EQUAL: // Equal (EQ) == Plasma gun on/off.
      if(isPlasmaGun()) {
        plasmaGunOff();
      } else {
        plasmaGunOn();
      }
      break;

    case CTL_STRPT: // ST/RPT == Search lights on/off.
      if(isSearchLights()) {
        searchLightsOff();
      } else {
        searchLightsOn();
      }
      break;

    case '0': // 0 To stop sound effects.
      stopPlaying();
      break;

    case '1': // 1 to play cut scene 01.
      resetAHKCtrl();
      setTimings(CUT_SCENE_01);
      break;
  }
}
