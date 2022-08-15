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


//
// Base LEDs...
//
auto blueLed = JLed(PIN_BLUE_FRONT).Off();
auto redLed = JLed(PIN_RED_BACK).Off();


//
// Sounds...
//
#define VOL_MIN 0
#define VOL_CENTRE 15
#define VOL_MAX 30
static int volume = VOL_CENTRE;

// Sound commands.
#define SND_PLAYMODE F("AT+PLAYMODE=3\r\n")
#define SND_VOLUME F("AT+VOL=")
#define SND_VOLUME_END F("\r\n")
#define SND_STOP F("AT+PLAYFILE=/stop.mp3\r\n")
#define SND_FLY F("AT+PLAYFILE=/fly.mp3\r\n")
#define SND_FLYMORE F("AT+PLAYFILE=/flymore.mp3\r\n")
#define SND_LAND F("AT+PLAYFILE=/land.mp3\r\n")
#define SND_SCENE_01 F("AT+PLAYFILE=/cut01.mp3\r\n")

// Serial port to DFPlayer Pro.
SoftwareSerial DFSerial(PIN_SOUND_RX, PIN_SOUND_TX);  //RX  TX

static void readAck() {
  char str[81];
  int i = 0;
  char c = '\0';
  long ms = millis();

  while (millis() - ms < 1000) {
    if(DFSerial.available()) {
      c = DFSerial.read();
      if(isprint(c)) {
        str[i++] = c;
      }
    }

    if(c == '\n' || i >= (int)(sizeof(str)-1)) break;
  }

  str[i]='\0';
  if(strcmp(str, "OK")) {
    Serial.print("FX? ");
    Serial.println(str);
  }
}


void setupAHKEffects() {
  DFSerial.begin(115200);

  DFSerial.print(SND_PLAYMODE); readAck();
  stopPlaying();
  volumeCentre();

  pinMode(PIN_BLUE_FRONT, OUTPUT);
  blueLightsOff();

  pinMode(PIN_RED_BACK, OUTPUT);
  redLightsOff();
}


void loopAHKEffects() {
  blueLed.Update();
  redLed.Update();
}


//
// Blue/Red LEDs...
//

void blueLightsOn() {
  blueLed.Reset().On().Forever().Update();
}

void blueLightsFlashOn() {
  blueLed.Reset().Blink(50,50).Forever().Update();
  plasmaGunOn();
}

void blueLightsOff() {
  blueLed.Reset().Off().Forever().Update();
  plasmaGunOff();
}

void redLightsOn() {
  redLed.Reset().On().Forever().Update();
}

void redLightsFlashOn() {
  redLed.Reset().Blink(50,50).Forever().Update();
}

void redLightsOff() {
  redLed.Reset().Off().Forever().Update();
}


//
// Sound Effects
//

static void setVolume(int level) {
  if(level < VOL_MIN) {
    level = VOL_MIN;
  } else if(level > VOL_MAX) {
    level = VOL_MAX;
  }

  DFSerial.print(SND_VOLUME);
  DFSerial.print(level);
  DFSerial.print(SND_VOLUME_END);
  readAck();

  volume = level;
}

void volumeUp() {
  setVolume(volume + 1);
}

void volumeCentre() {
  setVolume(VOL_CENTRE);
}

void volumeDown() {
  setVolume(volume - 1);
}

void stopPlaying() {
  DFSerial.print(SND_STOP); readAck();
}

void playTakeoff() {
  DFSerial.print(SND_FLY); readAck();
}

void playLanding() {
  DFSerial.print(SND_LAND); readAck();
}

void playFlyMore() {
  DFSerial.print(SND_FLYMORE); readAck();
}

void playScene01() {
  Serial.print(SND_SCENE_01);
  DFSerial.print(SND_SCENE_01); readAck();
}
