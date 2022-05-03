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

auto plasmaLed = JLed(PIN_PLASMA_GUN).Blink(50, 50).Forever();

// Definition of singleton AerialHK.
AerialHunterKiller AerialHK;


AerialHunterKiller::
AerialHunterKiller()
: tiltDegrees(AerialHunterKiller::TILT_CENTER)
, turnDegrees(AerialHunterKiller::TURN_CENTER)
, plasmaGun(false)
{
  // NOP
}

void AerialHunterKiller::
begin()
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
  thrustServoL.attach(PIN_THRUST_SERVO_L, THRUST_CENTER);
  thrustServoL.setSpeed(THRUST_SPEED);
  
  thrustServoR.attach(PIN_THRUST_SERVO_R, 180-THRUST_CENTER);
  thrustServoR.setSpeed(THRUST_SPEED);

  turnServo.attach(PIN_TURN_SERVO, turnDegrees);
  turnServo.setEasingType(EASE_QUADRATIC_IN_OUT);
  turnServo.setSpeed(TURN_SPEED);

  tiltServo.attach(PIN_TILT_SERVO, tiltDegrees);
  tiltServo.setSpeed(TILT_SPEED);
}


void AerialHunterKiller::
handle()
{
  if(plasmaGun) {
    Serial.println("Plasma Gun");
    plasmaLed.Update();
  }
}


bool AerialHunterKiller::
isLandingLights()
{
  return digitalRead(PIN_LANDING_LIGHTS);
}


bool AerialHunterKiller::
isPlasmaGun()
{
  return plasmaGun;
}


bool AerialHunterKiller::
isTailLights()
{
  return digitalRead(PIN_TAIL_LIGHTS);
}


bool AerialHunterKiller::
isSearchLights()
{
  return digitalRead(PIN_SEARCH_LIGHTS);
}


void AerialHunterKiller::
thrustBack()
{
  int thrust = THRUST_CENTER - THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


void AerialHunterKiller::
thrustTo(int thrust)
{
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


void AerialHunterKiller::
thrustForward()
{
  int thrust = THRUST_CENTER + THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}


void AerialHunterKiller::
thrustLeft()
{
  int thrust = THRUST_CENTER - THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(thrust);
}


void AerialHunterKiller::
thrustRight()
{
  int thrust = THRUST_CENTER + THRUST_OFFSET;
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(thrust);
}


void AerialHunterKiller::
tiltTo(int degrees)
{
  if(degrees < TILT_MIN) {
    degrees = TILT_MIN;
  } else if(degrees > TILT_MAX) {
    degrees = TILT_MAX;
  }

  if(degrees > tiltDegrees) {
    thrustForward();
  } else if(degrees < tiltDegrees) {
    thrustBack();
  } else if(degrees == TILT_MAX) {
    thrustTo(THRUST_MAX);
  } else {
    thrustTo(THRUST_CENTER);
  }

  tiltServo.startEaseTo(degrees);
  tiltDegrees = degrees;
}


void AerialHunterKiller::
setLandingLights(bool light)
{
  digitalWrite(PIN_LANDING_LIGHTS, light);
}


void AerialHunterKiller::
setPlasmaGun(bool light)
{
  plasmaGun = light;
  if(!light) {
    digitalWrite(PIN_PLASMA_GUN, light);
  } else {
    plasmaLed.Update();
  }
}


void AerialHunterKiller::
setSearchLights(bool light)
{
  digitalWrite(PIN_SEARCH_LIGHTS, light);
}


void AerialHunterKiller::
setTailLights(bool light)
{
  digitalWrite(PIN_TAIL_LIGHTS, light);
}


void AerialHunterKiller::
turnTo(int degrees)
{
  if(degrees < TURN_MIN) {
    degrees = TURN_MIN;
  } else if(degrees > TURN_MAX) {
    degrees = TURN_MAX;
  }

  if(degrees > turnDegrees) {
    thrustLeft();
  } else if(degrees < turnDegrees) {
    thrustRight();
  } else {
    thrustTo(THRUST_CENTER);
  }

  turnServo.startEaseTo(degrees);
  turnDegrees = degrees;
}
