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
#include <jled.h>
#include <SoftwareSerial.h>
#include "ahkfx.h"
#include "aerialhk.h"
#include "pinout.h"

// Definition of singleton AHKController.
AerialHunterKillerEffects AHKEffects;

// Serial port to DFPlayer Pro.
SoftwareSerial DFSerial(PIN_SOUND_RX, PIN_SOUND_TX);  //RX  TX

auto blueFrontLed = JLed(PIN_BLUE_FRONT).Off();
auto redBackLed = JLed(PIN_RED_BACK).Off();

// Sound files.
const char *AerialHunterKillerEffects::SND_STOP = "/stop.mp3";
const char *AerialHunterKillerEffects::SND_FLY = "/fly.mp3";
const char *AerialHunterKillerEffects::SND_FLYMORE = "/flymore.mp3";
const char *AerialHunterKillerEffects::SND_LAND = "/land.mp3";
const char *AerialHunterKillerEffects::SND_SCENE_01 = "/cut01.mp3";


AerialHunterKillerEffects::
AerialHunterKillerEffects()
: volume(VOL_CENTRE)
{
  // NOP
}


void AerialHunterKillerEffects::
begin()
{
  Serial.println(F("\nStarting Sound Effects..."));
  DFSerial.begin(115200);

  atCommand("PLAYMODE=3");
  stop();
  setVolume(VOL_CENTRE);

  Serial.println(F("Sound Effects Online"));

  pinMode(PIN_BLUE_FRONT, OUTPUT);
  setBlueFrontLights(false);

  pinMode(PIN_RED_BACK, OUTPUT);
  setRedBackLights(false);
}


void AerialHunterKillerEffects::
handle()
{
  blueFrontLed.Update();
  redBackLed.Update();
}

bool AerialHunterKillerEffects::
isBlueFrontLights()
{
  return digitalRead(PIN_BLUE_FRONT);
}

bool AerialHunterKillerEffects::
isRedBackLights()
{
  return digitalRead(PIN_RED_BACK);
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
setBlueFrontLights(bool light)
{
  if(light) {
    blueFrontLed.On().Forever().Reset();
  } else {
    blueFrontLed.Off().Forever().Reset();
  }
}

void AerialHunterKillerEffects::
setRedBackLights(bool light)
{
  if(light) {
    redBackLed.Reset().On().Forever().Update();
  } else {
    redBackLed.Reset().Off().Forever().Update();
  }
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
