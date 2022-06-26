/**
 * @file ahkfx.h
 * @author John Scott
 * @brief Manage Aerial HK effects (mainly sound and base lights).
 * @version 1.0
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_AHKFX_H
#define INCLUDED_AHKFX_H

void setupAHKEffects();
void loopAHKEffects();

bool isBlueFrontLights();
void blueFrontLightsOn();
void blueFrontLightsOff();
void blueFrontLightsFlash();
void blueFrontLightsFlashOn();

bool isRedBackLights();
void redBackLightsOn();
void redBackLightsOff();
void redBackLightsFlash();

void volumeUp();
void volumeCentre();
void volumeDown();

void playTakeoff();
void playFlyMore();
void playLanding();
void playScene01();
void stopPlaying();

#endif /* INCLUDED_AHKFX_H */
