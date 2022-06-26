/**
 * @file aerielhk.h
 * @author John Scott
 * @brief Aerial Hunter Killer
 * @version 1.0
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_AERIALHK_H
#define INCLUDED_AERIALHK_H

#define AHK_THRUST_CENTRE 110
#define AHK_THRUST_SPEED 125
#define AHK_THRUST_OFFSET 25
#define AHK_THRUST_MIN 40
#define AHK_THRUST_MAX 170

#define AHK_TILT_CENTRE 120
#define AHK_TILT_MIN 80
#define AHK_TILT_MAX 180
#define AHK_TILT_SPEED 50

#define AHK_TURN_CENTRE 85
#define AHK_TURN_MIN 35
#define AHK_TURN_MAX 135
#define AHK_TURN_SPEED 25

void setupAHK(); ///< Setup the AHK. Called by main setup.
void loopAHK(); ///< Handle the AHK. Called from main loop to run the HK.

bool isTailLights(); ///< Tail lights on/off.
void tailLightsOn(); ///< Tail lights on.
void tailLightsOff(); ///< Tail lights off.

bool isLandingLights(); ///< Landing lights on/off.
void landingLightsOn(); ///< Landing lights on.
void landingLightsOnOff(); ///< Landing lights on then off.
void landingLightsOff(); ///< Landing lights off.

bool isSearchLights();
void searchLightsOn(); ///< Search lights on.
void searchLightsOff(); ///< Search lights off.

bool isPlasmaGun(); ///< Plasma gun firing/not.
void plasmaGunOn(); ///< Start firing.
void plasmaGunOn200(); ///< Start firing for 200ms.
void plasmaGunOff(); ///< Stop firing.

int getTilt();
void tiltForward();
void tiltLevel();
void tiltBackward();

int getTurn();
void turnLeft();
void turnCentre();
void turnRight();

void thrustBack(); ///< Thrust backwards.
void thrustHover(); ///< Thrust to hover position.
void thrustForward(); ///< Thrust forwards.
void thrustLeft(); ///< Thrust left. One thruster backwards, the other forwards.
void thrustRight(); ///< Thrust right. One thruster forwards, the other backwards.

#endif /* INCLUDED_AERIALHK_H */
