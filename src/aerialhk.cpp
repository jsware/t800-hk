/**
 * @file aerialhk.cpp
 * @author John Scott
 * @brief Aerial Hunter-Killer (AHK)
 * @version 1.0
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <Arduino.h>
#include <jled.h>
#include <Servo.h>
#include <ServoEasing.hpp> 
#include "aerialhk.h"
#include "pinout.h"

// Thrusters...
ServoEasing thrustServoL;
ServoEasing thrustServoR;
#define THRUST_SPEED 125
#define THRUST_INTERVAL 1000

ServoEasing turnServo;
#define TURN_SPEED 25
#define TURN_INTERVAL 9000

ServoEasing tiltServo;
#define TILT_SPEED 50
#define TILT_INTERVAL 10000

auto plasmaLed = JLed(PIN_PLASMA_GUN).Off();
auto landingLed = JLed(PIN_LANDING_LIGHTS).Off();

// Definition of singleton AerialHK.
AerialHunterKiller AerialHK;


//
// AHK Constructor.
//
AerialHunterKiller::
AerialHunterKiller()
: tiltAngle(AerialHunterKiller::TILT_CENTRE)
, turnAngle(AerialHunterKiller::TURN_CENTRE)
, landingLights(false)
, plasmaGun(false)
{
  // NOP
}


//
// AHK setup.
//
void AerialHunterKiller::
setup()
{
  // HK lights...
  pinMode(PIN_LANDING_LIGHTS, OUTPUT);
  setLandingLights(false);

  pinMode(PIN_SEARCH_LIGHTS, OUTPUT);
  setSearchLights(false);

  pinMode(PIN_TAIL_LIGHTS, OUTPUT);
  setTailLights(false);

  pinMode(PIN_PLASMA_GUN, OUTPUT);
  setPlasmaGun(false);

  // HK thrusters...
  thrustServoL.attach(PIN_THRUST_SERVO_L, THRUST_CENTRE);
  thrustServoL.setSpeed(THRUST_SPEED);
  
  thrustServoR.attach(PIN_THRUST_SERVO_R, 180-THRUST_CENTRE);
  thrustServoR.setSpeed(THRUST_SPEED);

  turnServo.attach(PIN_TURN_SERVO, turnAngle);
  turnServo.setEasingType(EASE_QUADRATIC_IN_OUT);
  turnServo.setSpeed(TURN_SPEED);

  tiltServo.attach(PIN_TILT_SERVO, tiltAngle);
  tiltServo.setSpeed(TILT_SPEED);
}


//
// AHK Loop Handler...
//
void AerialHunterKiller::
loop()
{
  plasmaLed.Update();
  landingLed.Update();
}


//
// Determine landing lights on/off.
//
bool AerialHunterKiller::
isLandingLights()
{
  return landingLights;
}


//
// Determine plasma gun firing/silent.
//
bool AerialHunterKiller::
isPlasmaGun()
{
  return plasmaGun;
}


//
// Determine search lights on/off.
//
bool AerialHunterKiller::
isSearchLights()
{
  return digitalRead(PIN_SEARCH_LIGHTS);
}


//
// Determine tail lights on/off.
//
bool AerialHunterKiller::
isTailLights()
{
  return digitalRead(PIN_TAIL_LIGHTS);
}


//
// Thrust backwards.
//
void AerialHunterKiller::
thrustBack()
{
  int thrust = THRUST_CENTRE - THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


//
// Thrust forward.
//
void AerialHunterKiller::
thrustForward()
{
  int thrust = THRUST_CENTRE + THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


//
// Thrust left.
//
void AerialHunterKiller::
thrustLeft()
{
  int thrustL = THRUST_CENTRE - THRUST_OFFSET;
  int thrustR = THRUST_CENTRE + THRUST_OFFSET; 
  thrustServoL.startEaseTo(thrustL);
  thrustServoR.startEaseTo(180-thrustR);
}


//
// Thrust right.
//
void AerialHunterKiller::
thrustRight()
{
  int thrustL = THRUST_CENTRE + THRUST_OFFSET;
  int thrustR = THRUST_CENTRE - THRUST_OFFSET;
  thrustServoL.startEaseTo(thrustL);
  thrustServoR.startEaseTo(180-thrustR);
}


//
// Thrust to specific angle.
//
void AerialHunterKiller::
thrustTo(int thrust)
{
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


//
// Tilt to specific angle.
//
void AerialHunterKiller::
tiltTo(int degrees)
{
  if(degrees < TILT_MIN) {
    degrees = TILT_MIN;
  } else if(degrees > TILT_MAX) {
    degrees = TILT_MAX;
  }

  if(degrees > tiltAngle) {
    thrustForward();
  } else if(degrees < tiltAngle) {
    thrustBack();
  } else if(degrees == TILT_MAX) {
    thrustTo(THRUST_MAX);
  } else {
    thrustTo(THRUST_CENTRE);
  }

  tiltServo.startEaseTo(degrees);
  tiltAngle = degrees;
}


//
// Turn to specific degrees (thrusting left/right as required).
//
void AerialHunterKiller::
turnTo(int degrees)
{
  if(degrees < TURN_MIN) {
    degrees = TURN_MIN;
  } else if(degrees > TURN_MAX) {
    degrees = TURN_MAX;
  }

  if(degrees > turnAngle) {
    thrustLeft();
  } else if(degrees < turnAngle) {
    thrustRight();
  } else {
    thrustTo(THRUST_CENTRE);
  }

  turnServo.startEaseTo(degrees);
  turnAngle = degrees;
}


//
// Set landing lights on/off.
//
void AerialHunterKiller::
setLandingLights(bool light)
{
  if(light) {
    landingLed.Reset().FadeOn(1500).Repeat(1).Update();
  } else if(landingLights) {
    landingLed.Reset().FadeOff(1500).Repeat(1).Update();
  }

  landingLights = light;
}


//
// Set plasma gun on/off.
//
void AerialHunterKiller::
setPlasmaGun(bool light)
{
  plasmaGun = light;
  if(!light) {
    plasmaLed.Reset().Off().Forever().Update();
  } else {
    plasmaLed.Reset().Blink(50,50).Forever().Update();
  }
}


//
// Set search lights on/off.
//
void AerialHunterKiller::
setSearchLights(bool light)
{
  digitalWrite(PIN_SEARCH_LIGHTS, light);
}


//
// Set tail lights on/off.
//
void AerialHunterKiller::
setTailLights(bool light)
{
  digitalWrite(PIN_TAIL_LIGHTS, light);
}
