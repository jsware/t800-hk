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
// Cut scene controllers.
//
static unsigned long cutSceneTimer = 0;
static unsigned short cutSceneStep = 0;
static unsigned short cutSceneControllerId = 0;
void cutScene01Controller(); ///< Control main cut scene 01.

static unsigned short turnControllerId = 0;
void startTurnRightRandom();
void stopTurning();


//
// Timed effects...
//
AsyncTimer ATimer; ///< Asynchronous Timer.

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
  AT_TIME(250, blueLightsOff),
  AT_TIME(250, redLightsOff),
  AT_TIME(500, tiltLevel),
  AT_TIME(1000, landingLightsOnOff),
  AT_TIME(1500, turnCentre),
  AT_TIME(2000, searchLightsOff),
  AT_TIME(3500, thrustHover),
  AT_TIME(10000, tailLightsOff),
  END_TIMINGS
};

const struct AsyncTiming CUT_SCENE_01_CTL[] PROGMEM = {
  AT_TIME(0, tailLightsOn),
  AT_TIME(0, playScene01),
  AT_THEN_EVERY(0,10,cutScene01Controller),
  END_TIMINGS
};

const struct AsyncTiming CUT_SCENE_01[] PROGMEM = {
  AT_TIME(2000, landingLightsOnOff),
  AT_TIME(5500, searchLightsOn),

  AT_TIME(6000, thrustForward),
  AT_TIME(6000, tiltForward),
  AT_TIME(9232, blueLightsFlashOn),
  AT_TIME(9332, blueLightsOff),
  AT_TIME(9300, redLightsFlashOn),
  AT_TIME(9375, redLightsOff),

  AT_TIME(13000, thrustHover),
  AT_TIME(13000, tiltBackward),

  AT_TIME(14000, thrustRight),
  AT_TIME(14000, turnRight),
  AT_TIME(16000, thrustHover),
  AT_TIME(16500, blueLightsFlashOn),
  AT_TIME(16575, blueLightsOff),
  AT_TIME(18000, redLightsFlashOn),
  AT_TIME(18075, redLightsOff),
  AT_TIME(18575, blueLightsFlashOn),
  AT_TIME(18650, blueLightsOff),
  AT_TIME(19250, redLightsFlashOn),
  AT_TIME(19325, redLightsOff),
  AT_TIME(19575, blueLightsFlashOn),
  AT_TIME(19650, blueLightsOff),

  AT_TIME(20000, thrustForward),
  AT_TIME(20000, tiltForward),
  AT_TIME(21700, blueLightsFlashOn),
  AT_TIME(21800, blueLightsOff),
  AT_TIME(22700, redLightsFlashOn),
  AT_TIME(22775, redLightsOff),
  AT_TIME(23060, redLightsFlashOn),
  AT_TIME(23135, redLightsOff),

  AT_TIME(24000, thrustLeft),
  AT_TIME(24000, turnLeft),
  AT_TIME(26000, thrustForward),

  AT_TIME(28000, thrustHover),
  AT_TIME(28000, tiltLevel),

  AT_TIME(32000, thrustRight),
  AT_TIME(32000, turnRight),
  AT_TIME(34000, thrustHover),

  AT_TIME(36000, thrustForward),
  AT_TIME(36000, tiltForward),
  AT_TIME(38600, redLightsFlashOn),
  AT_TIME(38675, redLightsOff),

  AT_TIME(40000, thrustHover),
  AT_TIME(40000, tiltBackward),

  AT_TIME(40000, startTurnRightRandom),
  AT_TIME(40500, blueLightsFlashOn),
  AT_TIME(41470, blueLightsOff),
  AT_TIME(41900, redLightsFlashOn),
  AT_TIME(42500, redLightsOff),
  AT_TIME(42660, blueLightsFlashOn),
  AT_TIME(43000, blueLightsOff),
  AT_TIME(44400, blueLightsFlashOn),
  AT_TIME(44500, redLightsFlashOn),
  AT_TIME(45500, blueLightsOff),
  AT_TIME(45700, redLightsOff),
  AT_TIME(45700, blueLightsFlashOn),
  AT_TIME(46700, blueLightsOff),
  AT_TIME(46700, redLightsFlashOn),
  AT_TIME(48300, redLightsOff),
  AT_TIME(49000, blueLightsFlashOn),
  AT_TIME(49000, redLightsOn),
  AT_TIME(49750, redLightsOff),
  AT_TIME(50000, blueLightsOff),
  AT_TIME(50000, redLightsFlashOn),
  AT_TIME(50700, blueLightsFlashOn),
  AT_TIME(51300, blueLightsOff),
  AT_TIME(51700, blueLightsFlashOn),
  AT_TIME(52600, blueLightsOff),
  AT_TIME(52600, redLightsOn),
  AT_TIME(52600, blueLightsOn),
  AT_TIME(53000, stopTurning),
  AT_TIME(55000, redLightsOff),
  AT_TIME(55000, blueLightsOff),
  AT_TIME(56000, thrustForward),
  AT_TIME(56000, tiltForward),

  AT_TIME(60000, thrustHover),
  AT_TIME(60000, tiltBackward),
  AT_TIME(63400, blueLightsFlashOn),
  AT_TIME(63700, blueLightsOff),
  AT_TIME(63700, redLightsOn),
  AT_TIME(64500, redLightsOff),
  AT_TIME(67200, redLightsOn),
  AT_TIME(68500, blueLightsOn),
  AT_TIME(69000, startTurnRightRandom),
  AT_TIME(69500, redLightsOff),
  AT_TIME(70000, blueLightsOff),
  AT_TIME(70000, redLightsFlashOn),
  AT_TIME(71100, redLightsOn),
  AT_TIME(71100, blueLightsOn),
  AT_TIME(72000, redLightsOff),
  AT_TIME(72000, blueLightsOff),
  AT_TIME(73000, redLightsFlashOn),
  AT_TIME(75700, blueLightsFlashOn),
  AT_TIME(77000, blueLightsOff),
  AT_TIME(78000, blueLightsFlashOn),
  AT_TIME(80000, redLightsOff),
  AT_TIME(80200, blueLightsOff),
  AT_TIME(80400, redLightsOn),
  AT_TIME(80400, blueLightsOn),
  AT_TIME(81800, blueLightsOff),
  AT_TIME(83700, redLightsOff),
  AT_TIME(83800, blueLightsFlashOn),
  AT_TIME(85900, blueLightsOff),
  AT_TIME(85900, redLightsOn),
  AT_TIME(87000, stopTurning),
  AT_TIME(87300, redLightsOff),

  AT_TIME(87300, tiltForward),
  AT_TIME(87400, turnLeft),
  AT_TIME(87500, thrustMin),
  AT_TIME(87500, searchLightsOff),
  AT_TIME(88500, tailLightsOff),
  AT_TIME(89000, redLightsOn),
  AT_TIME(89000, blueLightsOn),
  AT_TIME(91000, redLightsOff),
  AT_TIME(91500, blueLightsOff),

  AT_TIME(91500, thrustBack),
  AT_TIME(91500, tiltLevel),
  AT_TIME(91500, tailLightsOn),
  AT_TIME(91500, landingLightsOnOff),
  AT_TIME(93000, turnCentre),
  AT_TIME(93000, thrustHover),
  AT_TIME(93500, searchLightsOn),

  AT_TIME(95000, thrustLeft),
  AT_TIME(95500, turnLeft),
  AT_TIME(97000, thrustHover),
  AT_TIME(99000, thrustForward),
  AT_TIME(99250, tiltForward),
  AT_TIME(100000, blueLightsOn),
  AT_TIME(100000, redLightsOn),

  AT_TIME(102000, thrustRight),
  AT_TIME(102000, turnRight),
  AT_TIME(104500, thrustForward),

  AT_TIME(106000, thrustLeft),
  AT_TIME(106000, turnLeft),
  AT_TIME(108500, thrustForward),

  AT_TIME(110000, thrustRight),
  AT_TIME(110000, turnRight),
  AT_TIME(112500, thrustForward),

  AT_TIME(114000, thrustLeft),
  AT_TIME(114000, turnLeft),
  AT_TIME(116500, thrustForward),

  AT_TIME(118000, thrustRight),
  AT_TIME(118000, turnRight),
  AT_TIME(120500, thrustForward),

  AT_TIME(121000, blueLightsOff),
  AT_TIME(121000, redLightsOff),
  AT_TIME(121500, tiltLevel),
  AT_TIME(121500, landingLightsOnOff),
  AT_TIME(122000, stopTurning),
  AT_TIME(122500, turnCentre),
  AT_TIME(123500, thrustHover),
  AT_TIME(124000, searchLightsOff),
  AT_TIME(130000, tailLightsOff),
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
      Serial.print(F("IR Code Error: "));
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
  cutSceneStep = 0;
  cutSceneTimer = millis();

  do {
    memcpy_P(&t, &timings[i], sizeof(t));

    if(t.callback) {
      ATimer.setTimeout(t.callback, t.start);

      if(t.repeat) {
        ATimer.delay(cutSceneControllerId = ATimer.setInterval(t.callback,t.repeat),t.start);
      }
    }
    ++i;
  } while(t.callback);
}


void resetAHKCtrl() {
  stopPlaying();
  blueLightsOff();
  redLightsOff();

  tiltLevel();
  turnCentre();
  thrustHover();
  
  tailLightsOff();
  landingLightsOff();
  searchLightsOff();
  plasmaGunOff();
}


void setupAHKCtrl() {
  Serial.println(F("AHK Controller Online"));
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
        Serial.println(F("Power on"));
        setTimings(POWER_ON);
      } else {
        Serial.println(F("Power off"));
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
      Serial.println(F("Levelling off"));

      tiltLevel();
      turnCentre();
      thrustHover();
      break;

    case CTL_REWND: // Rewind == turn left.
      Serial.println(F("Bank left"));
      thrustLeft();
      turnLeft();
      break;

    case CTL_FASTF: // Fast forward == turn right.
      Serial.println(F("Bank left"));
      thrustRight();
      turnRight();
      break;

    case CTL_MOVDN: // Move down == tilt forward.
      if(getTilt() < AHK_TILT_CENTRE) {
        Serial.println(F("Hover"));
        thrustForward();
        tiltLevel();
      } else if (getTilt() < AHK_TILT_MAX) {
        Serial.println(F("Fly forward"));
        thrustForward();
        tiltForward();
      } else {
        Serial.println(F("Pursuite Mode"));
        thrustMax();
      }
      break;

    case CTL_MOVUP: // Move up == tilt backwards.
      thrustBack();
      if(getTilt() > AHK_TILT_CENTRE) {
        Serial.println(F("Hover"));
        tiltLevel();
      } else {
        tiltBackward();
      }
      break;

    case CTL_FNSTP: // Function/stop == landinglights on/off.
      if(isLandingLights()) {
        Serial.println(F("Landing lights deactivate"));
        landingLightsOff();
      } else {
        Serial.println(F("Landing lights activate"));
        landingLightsOn();
      }
      break;

    case CTL_EQUAL: // Equal (EQ) == Plasma gun on/off.
      if(isPlasmaGun()) {
        Serial.println(F("Cease fire"));
        plasmaGunOff();
      } else {
        Serial.println(F("Commence firing"));
        plasmaGunOn();
      }
      break;

    case CTL_STRPT: // ST/RPT == Search lights on/off.
      if(isSearchLights()) {
        Serial.println(F("Suspend search mode"));
        searchLightsOff();
      } else {
        Serial.println(F("Search mode activated"));
        searchLightsOn();
      }
      break;

    case '0': // 0 To stop sound effects.
      stopPlaying();
      break;

    case '1': // 1 to play cut scene 01.
      Serial.println(F("Program 01: Search and destroy"));
      resetAHKCtrl();
      setTimings(CUT_SCENE_01_CTL);
      break;
  }
}


void cutScene01Controller() {
  unsigned long now = millis() - cutSceneTimer;
  struct AsyncTiming t;

  do {
    memcpy_P(&t, &CUT_SCENE_01[cutSceneStep], sizeof(t));

    if(t.callback) {
      if(now >= t.start) {
        t.callback();
        cutSceneStep++;
      }
    } else {
      ATimer.cancel(cutSceneControllerId);
    }
  } while(t.callback && now >= t.start);
}

void startTurnRightRandom() {
  stopTurning();
  turnControllerId = ATimer.setInterval(turnRightRandom, AHK_TURN_INTERVAL);
}

void stopTurning() {
  if(turnControllerId) {
    ATimer.cancel(turnControllerId);
    turnControllerId = 0;
  }
}
