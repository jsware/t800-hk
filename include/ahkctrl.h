/**
 * @file ahkctrl.h
 * @author John Scott
 * @brief Class to control the Aerial HK.
 * @version 1.0
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_AHKCTRL_H
#define INCLUDED_AHKCTRL_H

/**
 * @brief Aerial Hunter-Killer Controller.
 * 
 */
class AerialHunterKillerController
{
  public:
    //
    // Constants...
    //
    static const char CTL_POWER = '*'; ///< Power On/off.
    static const char CTL_VOLUP = '+'; ///< Volume up.
    static const char CTL_VOLDN = '-'; ///< Volume down.
    static const char CTL_PLAYP = '|'; ///< Play/Pause.
    static const char CTL_REWND = '<'; ///< Rewind.
    static const char CTL_FASTF = '>'; ///< Fast Forward.
    static const char CTL_MOVDN = 'V'; ///< Move Down.
    static const char CTL_MOVUP = '^'; ///< Move Up.
    static const char CTL_FNSTP = '!'; ///< Func/Stop.
    static const char CTL_EQUAL = '='; ///< EQ.
    static const char CTL_STRPT = '/'; ///< ST/REPT.

  public:
    //
    // Constructors...
    //

    /**
     * @brief Construct a new Aerial HK Controller.
     */
    AerialHunterKillerController();

  public:
    //
    // Mutators...
    //
    void setup(); ///< Setup controller.
    void loop(); ///< Handle AHK Controls.
    
  private:
    //
    // Helpers...
    //
    void reset(); ///< Reset HK - everything off and centre.

    /**
     * @brief Set timed control of the Aerial HK and Aerial HK Effects.
     * 
     * @param timings The array of timings (null terminated).
     */
    void setTimings(const struct AsyncTiming timings[]);

    char translateIR(); ///< Translate IR Codes into standard commands.


  private:
    //
    // Static Helpers (callbacks).
    //
    static void blueFrontLightsFlash(); ///< Blue front lights flashing.
    static void blueFrontLightsOff(); ///< Blue front lights off.
    static void blueFrontLightsOn(); ///< Blue front light on.

    static void plasmaGunOff(); ///< Turn plasma gun off timer callback.
    static void plasmaGunOn(); ///< Turn plasma gun on (flashing) on timer callback.

    static void playFlyMore(); ///< Repeat flying sounds timer callback.
    static void playLanding(); ///< Play landing sounds timer callback.
    static void playScene01(); ///< Play cut scene 01 timer callback.
    static void playTakeOff(); ///< Play take-off sounds timer callback.

    static void redBackLightsFlash(); ///< Red back lights flashing.
    static void redBackLightsOff(); ///< Red back lights off.
    static void redBackLightsOn(); ///< Red back light on.

    static void searchLightsOff(); ///< Turn search lights off timer callback.
    static void searchLightsOn(); ///< Turn search lights on timer callback.

    static void landingLightsOff(); ///< Turn landing lights off timer callback.
    static void landingLightsOn(); ///< Turn landing lights on timer callback.
    
    static void tailLightsOff(); ///< Turn tail lights off timer callback.
    static void tailLightsOn(); ///< Turn tail lights on timer callback.

    static void takeOff();

  private:
    //
    // Implementation...
    //
    static const struct AsyncTiming CUT_SCENE_01[]; ///< Cut scene 1.
    static const struct AsyncTiming POWER_OFF[]; ///< Power off timer sequence.
    static const struct AsyncTiming POWER_ON[]; ///< Power on timer sequence.

    int irPin; ///< IR Remote Control PIN.
};

/**
 * @brief Aerial Hunter Killer Controller.
 * 
 */
extern AerialHunterKillerController AHKController;

#endif /* INCLUDED_AHKCTRL_H */
