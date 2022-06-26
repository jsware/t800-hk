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

void setup() {
  if(Serial) {
    Serial.begin(115200);
  }
  
  setupAHK();
  setupAHKCtrl();
  setupAHKEffects();

  Serial.println(F("Online..."));
}

void loop() {
  loopAHK();
  loopAHKCtrl();
  loopAHKEffects();
}
