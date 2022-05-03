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
    static const int THRUST_CENTER = 95;
    static const int THRUST_OFFSET = 25;
    static const int THRUST_MIN = 40;
    static const int THRUST_MAX = 170;

    static const int TILT_CENTER = 100;
    static const int TILT_MIN = 80;
    static const int TILT_MAX = 180;

    static const int TURN_CENTER = 85;
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
     * @brief Get the Tilt angle
     * 
     * @return the current tilt angle.
     */
    int getTilt() {
      return tiltDegrees;
    }

    /**
     * @brief Get the Turn angle
     * 
     * @return the current turn angle.
     */
    int getTurn() {
      return turnDegrees;
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
     * @brief Begin the AerialHK.
     * 
     */
    void begin();

    /**
     * @brief Handle the AHK.
     * 
     */
    void handle();

    /**
     * @brief Set landing lights on/off.
     * 
     * @param light true turns on, false turns off.
     */
    void setLandingLights(bool light);

    /**
     * @brief Set plasma gun on/off.
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
    void thrustForward();
    void thrustLeft();
    void thrustRight();

    /**
     * @brief Thrust to specific position.
     * 
     * @param thrust Angle of thrust.
     */
    void thrustTo(int thrust);
    
    /**
     * @brief Absolute tilt.
     * 
     * @param degrees Angle of tilt.
     */
    void tiltTo(int degrees = TILT_CENTER);

    /**
     * @brief Absolute Turn.
     * 
     * @param degrees Angle of turn.
     */
    void turnTo(int degrees = TURN_CENTER);

  private:
    //
    // Helpers...
    //

  private:
    //
    // Implementation...
    //
    int tiltDegrees;
    int turnDegrees;
    bool plasmaGun;
};

/**
 * @brief Aerial Hunter Killer Controller.
 * 
 */
extern AerialHunterKiller AerialHK;

#endif /* INCLUDED_AERIALHK_H */
