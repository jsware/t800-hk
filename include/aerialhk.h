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

/**
 * @brief Aerial Hunter-Killer.
 * 
 */
class AerialHunterKiller
{
  public:
    //
    // Constants...
    //
    static const int THRUST_CENTRE = 110;
    static const int THRUST_OFFSET = 25;
    static const int THRUST_MIN = 40;
    static const int THRUST_MAX = 170;

    static const int TILT_CENTRE = 120;
    static const int TILT_MIN = 80;
    static const int TILT_MAX = 180;

    static const int TURN_CENTRE = 85;
    static const int TURN_MIN = 35;
    static const int TURN_MAX = 135;

  public:
    //
    // Constructors...
    //

    /**
     * @brief Construct a new Aerial HK.
     */
    AerialHunterKiller();

  public:
    //
    // Accessors...
    //

    /**
     * @brief Get the Tilt angle.
     * 
     * @return the current tilt angle.
     */
    int getTilt() {
      return tiltAngle;
    }

    /**
     * @brief Get the Turn angle.
     * 
     * @return the current turn angle.
     */
    int getTurn() {
      return turnAngle;
    }

    /**
     * @brief Indicate landing lights on/off.
     * 
     * @return true when lights on.
     * @return false when lights off.
     */
    bool isLandingLights();

    /**
     * @brief Indicate plasma gun on/off.
     * 
     * @return true when gun on.
     * @return false when gun off.
     */
    bool isPlasmaGun();

    /**
     * @brief Indicate if the tail lights are on.
     * 
     * @return true when lights on.
     * @return false when lights off.
     */
    bool isTailLights();

    /**
     * @brief Indicate if the search lights are on.
     * 
     * @return true when lights on.
     * @return false when lights off.
     */
    bool isSearchLights();

  public:
    //
    // Mutators...
    //

    /**
     * @brief Handle the AHK. Called from main loop to run the HK.
     * 
     */
    void loop();

    /**
     * @brief Set landing lights on/off.
     * 
     * @param light true turns on, false turns off.
     */
    void setLandingLights(bool light);

    /**
     * @brief Set plasma gun on/off. Gun will flash when on.
     * 
     * @param light true turns on, false turns off.
     */
    void setPlasmaGun(bool light);

    /**
     * @brief Set search lights on/off
     * 
     * @param light true turns on, false turns off.
     */
    void setSearchLights(bool light);

    /**
     * @brief Set tail lights on/off.
     * 
     * @param light true turns on, false turns off.
     */
    void setTailLights(bool light);
    
    /**
     * @brief Initialise the AerialHK. Called from main setup.
     * 
     */
    void setup();

    /**
     * @brief Toggle landing lights on/off.
     * 
     */
    void toggleLandingLights() {
      setLandingLights(!isLandingLights());
    };

    /**
     * @brief Toggle plasma gun on/off.
     * 
     */
    void togglePlasmaGun() {
      setPlasmaGun(!isPlasmaGun());
    };

    /**
     * @brief Toggle search lights on/off.
     * 
     */
    void toggleSearchLights() {
      setSearchLights(!isSearchLights());
    };

    /**
     * @brief Toggle tail lights on/off.
     * 
     */
    void toggleTailLights() {
      setTailLights(!isTailLights());
    };

    /**
     * @brief Thrust backwards.
     * 
     */
    void thrustBack();

    /**
     * @brief Thrust forwards.
     * 
     */
    void thrustForward();

    /**
     * @brief Thrust left. One thruster backwards, the other forwards.
     * 
     */
    void thrustLeft();

    /**
     * @brief Thrust right. One thruster forwards, the other backwards.
     * 
     */
    void thrustRight();

    /**
     * @brief Thrust to specific position.
     * 
     * @param angle Angle of thrust. Default is to centre.
     */
    void thrustTo(int angle);
    
    /**
     * @brief Tilt to specific position.
     * 
     * @param degrees Angle of tilt. Default is to centre.
     */
    void tiltTo(int angle);

    /**
     * @brief Absolute Turn.
     * 
     * @param degrees Angle of turn. Default is to centre.
     */
    void turnTo(int angle);

  private:
    //
    // Helpers...
    //

  private:
    //
    // Implementation...
    //

    /**
     * @brief The current angle of tilt.
     * 
     */
    int tiltAngle;

    /**
     * @brief The current angle of turn.
     * 
     */
    int turnAngle;


    /**
     * @brief Indicate if landing lights are on.
     * 
     */
    bool landingLights;

    /**
     * @brief Indicats whether plasma gun is on (flashing) or off.
     * 
     */
    bool plasmaGun;
};

/**
 * @brief Single Aerial Hunter Killer.
 * 
 */
extern AerialHunterKiller AerialHK;

#endif /* INCLUDED_AERIALHK_H */
