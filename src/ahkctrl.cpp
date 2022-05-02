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
#include <IRremote.hpp>
#include "ahkctrl.h"
#include "ahkfx.h"
#include "aerialhk.h"
#include "pinout.h"

// Definition of singleton AHKController.
AerialHunterKillerController AHKController;

// Asynchronous Timer.
AsyncTimer ATimer;


AerialHunterKillerController::
AerialHunterKillerController()
{
  // NOP
}


void AerialHunterKillerController::
begin()
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

  IrReceiver.begin(PIN_IR_RECEIVER, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.println(F("Infra-Red Control Online"));
}


void AerialHunterKillerController::
handle()
{
  char cmd = '\0';

  ATimer.handle();

  if(Serial.available()) {
    cmd = toupper(Serial.read());
  } else if(IrReceiver.decode()) {
    cmd = translateIR();
    IrReceiver.resume(); // Receive the next value
  }

  switch(cmd) {
    case CTL_POWER:
      AerialHK.toggleTailLights();
      break;

    case CTL_VOLUP:
      AHKEffects.volUp();
      break;

    case CTL_VOLDN:
      AHKEffects.volDown();
      break;

    case CTL_PLAYP:
      AerialHK.tiltTo(AerialHunterKiller::TILT_CENTER);
      AerialHK.turnTo(AerialHunterKiller::TURN_CENTER);
      break;

    case CTL_REWND:
      AerialHK.turnTo(AerialHunterKiller::TURN_MAX);
      break;

    case CTL_FASTF:
      AerialHK.turnTo(AerialHunterKiller::TURN_MIN);
      break;

    case CTL_MOVDN:
      AerialHK.tiltTo(AerialHunterKiller::TILT_MAX);
      break;

    case CTL_MOVUP:
      AerialHK.tiltTo(AerialHunterKiller::TILT_MIN);
      break;

    case CTL_FNSTP:
      AerialHK.toggleLandingLights();
      break;

    case CTL_EQUAL:
      AerialHK.togglePlasmaGun();
      break;

    case CTL_STRPT:
      AerialHK.toggleSearchLights();
      break;

    case '0':
      AHKEffects.stop();
      break;

    case '1':
      AHKEffects.play(AerialHunterKillerEffects::SND_FLY);
      break;

    case '2':
      AHKEffects.play(AerialHunterKillerEffects::SND_FLYMORE);
      break;

    case '3':
      AHKEffects.play(AerialHunterKillerEffects::SND_LAND);
      break;
  }
}


char AerialHunterKillerController::
translateIR()
{
  char cmd='\0';

  switch(IrReceiver.decodedIRData.decodedRawData) {
    case 0x0: // Repeat
      break;  

    case 0xBA45FF00: // Power On/Off
      cmd = CTL_POWER;
      break;
      
    case 0xB847FF00: // Func/Stop
      cmd = CTL_FNSTP;
      break;

    case 0xE619FF00: // EQ
      cmd = CTL_EQUAL;
      break;

    case 0xF20DFF00: // ST/REPT
      cmd = CTL_STRPT;
      break;

    case 0xB946FF00: // Vol +
      cmd = CTL_VOLUP;
      break;

    case 0xEA15FF00: // Vol -
      cmd = CTL_VOLDN;
      break;
  
    case 0xBB44FF00: // |<< (Rewind)
      cmd = CTL_REWND;
      break;

    case 0xBF40FF00: // >|| (Play/Pause)
      cmd = CTL_PLAYP;
      break;

    case 0xBC43FF00: // >>| (Fast Forward)
      cmd = CTL_FASTF;
      break;

    case 0xF807FF00: // V (Down)
      cmd = CTL_MOVDN;
      break;

    case 0xF609FF00: // ^ (Up)
      cmd = CTL_MOVUP;
      break;

    case 0xE916FF00:
      cmd = '0';
      break;

    case 0xF30CFF00:
      cmd = '1';
      break;

    case 0xE718FF00:
      cmd = '2';
      break;

    case 0xA15EFF00:
      cmd = '3';
      break;

    case 0xF708FF00:
      cmd = '4';
      break;

    case 0xE31CFF00:
      cmd = '5';
      break;

    case 0xA55AFF00:
      cmd = '6';
      break;

    case 0xBD42FF00:
      cmd = '7';
      break;

    case 0xAD52FF00:
      cmd = '8';
      break;

    case 0xB54AFF00:
      cmd = '9';
      break;

    default: 
      Serial.println("Ignore Unknown:");
      IrReceiver.printIRResultAsCVariables(&Serial);
      break;
  }

  return cmd;
}
