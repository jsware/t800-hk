/**
 * @file t800-hk.cpp
 * @author John Scott
 * @brief Aerial Hunter-Killer Machine
 * @version 1.0
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <Arduino.h>
#include "aerialhk.h"
#include "ahkctrl.h"
#include "ahkfx.h"
#include "pinout.h"
#include "ver_info.h"

void setup() {
  if(Serial) {
    Serial.begin(115200);
  }

  Serial.print(F("\n\nCyberdine Systems (JSWare Division)\nAerial Hunter Killer (HK) Version "));
  Serial.println(F(VER_STRING));
  Serial.println("\nSystem Restart...");

  randomSeed(analogRead(PIN_RANDOMISE));  // Randomise

  setupAHK();
  setupAHKCtrl();
  setupAHKEffects();

  Serial.println(F("\nSystem Restart Complete\n"));
}

void loop() {
  loopAHK();
  loopAHKCtrl();
  loopAHKEffects();
}
