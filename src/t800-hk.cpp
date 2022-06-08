/**
 * @file t800-hk.cpp
 * @author John Scott
 * @brief Aerial Hunter-Killer Machine
 * @version 1.0
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022 John Scott.
 * 
 */
#include <Arduino.h>
#include "aerialhk.h"
#include "ahkctrl.h"
#include "ahkfx.h"
#include "ver_info.h"

/**
 * @brief Called by Arduino once to setup components.
 * 
 */
void setup() {
  if(Serial) {
    Serial.begin(115200);
  }
  
  Serial.print(F("\n\nCyberdine Systems (JSWare Division)\nAerial Hunter Killer\nMark 8 Version "));
  Serial.println(F(VER_STRING));
  Serial.println(F("\nSystem Restart..."));

  randomSeed(analogRead(0)); // Init random number generator.

  AerialHK.setup();
  AHKController.setup();
  AHKEffects.begin();

  Serial.println(F("\nSystem Restart Complete\n"));
}

/**
 * @brief Called repeatedly in a loop to control things.
 * 
 */
void loop() {
  AerialHK.loop();
  AHKController.loop();
  AHKEffects.handle();
}
