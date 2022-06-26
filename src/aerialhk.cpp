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

// Servos...
ServoEasing thrustServoL;
ServoEasing thrustServoR;
ServoEasing turnServo;
ServoEasing tiltServo;

auto plasmaLed = JLed(PIN_PLASMA_GUN).Off();
auto landingLed = JLed(PIN_LANDING_LIGHTS).Off();

static int tiltAngle = AHK_TILT_CENTRE;
static int turnAngle = AHK_TURN_CENTRE;


//
// AHK setup.
//
void setupAHK() {
  // HK lights...
  pinMode(PIN_LANDING_LIGHTS, OUTPUT);
  landingLightsOff();

  pinMode(PIN_SEARCH_LIGHTS, OUTPUT);
  searchLightsOff();

  pinMode(PIN_TAIL_LIGHTS, OUTPUT);
  tailLightsOff();

  pinMode(PIN_PLASMA_GUN, OUTPUT);
  plasmaGunOff();

  // HK thrusters...
  thrustServoL.attach(PIN_THRUST_SERVO_L, AHK_THRUST_CENTRE);
  thrustServoL.setSpeed(AHK_THRUST_SPEED);
  
  thrustServoR.attach(PIN_THRUST_SERVO_R, 180-AHK_THRUST_CENTRE);
  thrustServoR.setSpeed(AHK_THRUST_SPEED);

  turnServo.attach(PIN_TURN_SERVO, turnAngle);
  turnServo.setEasingType(EASE_QUADRATIC_IN_OUT);
  turnServo.setSpeed(AHK_TURN_SPEED);

  tiltServo.attach(PIN_TILT_SERVO, tiltAngle);
  tiltServo.setSpeed(AHK_TILT_SPEED);
}


//
// AHK Loop Handler...
//
void loopAHK() {
  plasmaLed.Update();
  landingLed.Update();
}


//
// Tail Lights...
//
bool isTailLights() {
  return digitalRead(PIN_TAIL_LIGHTS);
}

void tailLightsOn() {
  digitalWrite(PIN_TAIL_LIGHTS, true);
}

void tailLightsOff() {
  digitalWrite(PIN_TAIL_LIGHTS, false);
}


//
// Landing Lights...
//
bool isLandingLights() {
  return digitalRead(PIN_LANDING_LIGHTS);
}

void landingLightsOn() {
  if(!isLandingLights()) {
    landingLed.Reset().FadeOn(1500).Repeat(1).Update();
  }
}

void landingLightsOnOff() {
  if(!isLandingLights()) {
    landingLed.Reset().Breathe(1500,7000,1500).Repeat(1).Update();
  }
}

void landingLightsOff() {
  if(isLandingLights()) {
    landingLed.Reset().FadeOff(1500).Repeat(1).Update();
  }
}


//
// Search Lights...
//
bool isSearchLights() {
  return digitalRead(PIN_SEARCH_LIGHTS);
}

void searchLightsOn() {
  digitalWrite(PIN_SEARCH_LIGHTS, true);
}

void searchLightsOff() {
  digitalWrite(PIN_SEARCH_LIGHTS, false);
}


//
// Plasma Gun...
//
bool isPlasmaGun() {
  return plasmaLed.IsRunning();
}

void plasmaGunOn() {
  plasmaLed.Reset().Blink(50,50).Forever().Update();
}

void plasmaGunOff() {
  plasmaLed.Reset().Off().Repeat(1).Update();
}

void plasmaGunOn200() {
  plasmaLed.Reset().Blink(50,50).Repeat(2).Update();
}

//
// Thruster Servos...
//
void thrustTo(int thrust) {
  thrustServoL.startEaseTo(thrust);
  thrustServoR.startEaseTo(180-thrust);
}

void thrustBack() {
  thrustTo(AHK_THRUST_CENTRE - AHK_THRUST_OFFSET);
}

void thrustHover() {
  thrustTo(AHK_THRUST_CENTRE);
}

void thrustForward() {
  thrustTo(AHK_THRUST_CENTRE + AHK_THRUST_OFFSET);
}

void thrustLeft() {
  int thrustL = AHK_THRUST_CENTRE - AHK_THRUST_OFFSET;
  int thrustR = AHK_THRUST_CENTRE + AHK_THRUST_OFFSET; 
  thrustServoL.startEaseTo(thrustL);
  thrustServoR.startEaseTo(180-thrustR);
}

void thrustRight() {
  int thrustL = AHK_THRUST_CENTRE + AHK_THRUST_OFFSET;
  int thrustR = AHK_THRUST_CENTRE - AHK_THRUST_OFFSET;
  thrustServoL.startEaseTo(thrustL);
  thrustServoR.startEaseTo(180-thrustR);
}


//
// Tilt Servo...
//
int getTilt() {
  return tiltAngle;
}

void tiltTo(int degrees) {
  if(degrees < AHK_TILT_MIN) {
    degrees = AHK_TILT_MIN;
  } else if(degrees > AHK_TILT_MAX) {
    degrees = AHK_TILT_MAX;
  }

  if(degrees > tiltAngle) {
    thrustForward();
  } else if(degrees < tiltAngle) {
    thrustBack();
  }

  tiltServo.startEaseTo(degrees);
  tiltAngle = degrees;
}

void tiltLevel() {
  tiltTo(AHK_TILT_CENTRE);
}

void tiltForward() {
  tiltTo(AHK_TILT_MAX);
}

void tiltBackward() {
  tiltTo(AHK_TILT_MIN);
}


//
// Turn Servo...
//
void turnTo(int degrees) {
  if(degrees < AHK_TURN_MIN) {
    degrees = AHK_TURN_MIN;
  } else if(degrees > AHK_TURN_MAX) {
    degrees = AHK_TURN_MAX;
  }

  if(degrees > turnAngle) {
    thrustLeft();
  } else if(degrees < turnAngle) {
    thrustRight();
  }

  turnServo.startEaseTo(degrees);
  turnAngle = degrees;
}

void turnLeft() {
  turnTo(AHK_TURN_MAX);
}

void turnCentre() {
  turnTo(AHK_TURN_CENTRE);
}

void turnRight() {
  turnTo(AHK_TURN_MIN);
}
