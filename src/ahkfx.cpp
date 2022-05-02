/**
 * @file ahksound.cpp
 * @author John Scott
 * @brief Aerial Hunter-Killer (AHK) Sound Effects
 * @version 1.0
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ahkfx.h"
#include "aerialhk.h"
#include "pinout.h"

// Definition of singleton AHKController.
AerialHunterKillerEffects AHKEffects;

// Serial port to DFPlayer Pro.
SoftwareSerial DFSerial(PIN_SOUND_RX, PIN_SOUND_TX);  //RX  TX


const char *AerialHunterKillerEffects::SND_STOP = "/stop.mp3";
const char *AerialHunterKillerEffects::SND_FLY = "/fly.mp3";
const char *AerialHunterKillerEffects::SND_FLYMORE = "/flymore.mp3";
const char *AerialHunterKillerEffects::SND_LAND = "/land.mp3";


AerialHunterKillerEffects::
AerialHunterKillerEffects()
: volume(VOL_CENTER)
{
  // NOP
}


void AerialHunterKillerEffects::
begin()
{
  DFSerial.begin(115200);

  atCommand("PLAYMODE=3");
  stop();
  setVolume(VOL_CENTER);

  Serial.println(F("\nSound Effects Online"));
}


void AerialHunterKillerEffects::
handle()
{

}

bool AerialHunterKillerEffects::
readAck() {
  String str = "";
  char c = '\0';
  long ms = millis();

  while (millis() - ms < 1000) {
    if(DFSerial.available()) {
      c = DFSerial.read();
      if(isprint(c)) {
        str += c;
      }
    }

    if(c == '\n') break;
  }

  Serial.println(str);
  if(str == "OK") {
    return true;
  } else {
    return false;
  }
}

bool AerialHunterKillerEffects::
atCommand(const char *cmd) {
  if(cmd) {
    Serial.print("AT+");
    Serial.println(cmd);

    DFSerial.print("AT+");
    DFSerial.print(cmd);
    DFSerial.print("\r\n");
  } else {
    DFSerial.print("AT\r\n");    
  }

  return readAck();
}

void AerialHunterKillerEffects::
play(const char *sound) {
  String cmd = "PLAYFILE=";

  cmd += sound;
  atCommand(cmd.c_str());
}

void AerialHunterKillerEffects::
setVolume(int level) {
  String cmd = "VOL=";

  if(level < VOL_MIN) {
    level = VOL_MIN;
  } else if(level > VOL_MAX) {
    level = VOL_MAX;
  }

  cmd += level;
  atCommand(cmd.c_str());
  volume = level;
}
