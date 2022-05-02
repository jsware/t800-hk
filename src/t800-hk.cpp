#include <Arduino.h>
#include "aerialhk.h"
#include "ahkctrl.h"
#include "ahkfx.h"
#include "ver_info.h"

void setup() {
  if(Serial) Serial.begin(115200);
  Serial.print(F("\n\nCyberdine Systems (JSWare Division)\nAerial Hunter Killer\nMark 8 Version "));
  Serial.println(F(VER_STRING));
  Serial.println("\nSystem Restart...");

  randomSeed(analogRead(0)); // Init random number generator.

  AerialHK.begin();
  AHKController.begin();
  AHKEffects.begin();

  Serial.println(F("\nSystem Restart Complete\n"));
}

void loop() {
  AerialHK.handle();
  AHKController.handle();
  AHKEffects.handle();
}
