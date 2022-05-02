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
 * @brief Aerial Hunter-Killer.
 * 
 */
class AerialHunterKillerController
{
  public:
    //
    // Constants...
    //
    static const char CTL_POWER = '*';
    static const char CTL_VOLUP = '+';
    static const char CTL_VOLDN = '-';
    static const char CTL_PLAYP = '|';
    static const char CTL_REWND = '<';
    static const char CTL_FASTF = '>';
    static const char CTL_MOVDN = 'V';
    static const char CTL_MOVUP = '^';
    static const char CTL_FNSTP = '!';
    static const char CTL_EQUAL = '=';
    static const char CTL_STRPT = '/';


  public:
    //
    // Constructors...
    //

    /**
     * @brief Construct a new Aerial HK.
     */
    AerialHunterKillerController();

  public:
    //
    // Mutators...
    //

    /**
     * @brief Begin Controlling the AHK.
     * 
     */
    void begin();

    /**
     * @brief Handle AHK Controls.
     * 
     */
    void handle();
    
  private:
    //
    // Helpers...
    //

    /**
     * @brief Translate IR Codes into standard commands.
     * 
     */
    char translateIR();

  private:
    //
    // Implementation...
    //
    int irPin;

};

/**
 * @brief Aerial Hunter Killer Controller.
 * 
 */
extern AerialHunterKillerController AHKController;

#endif /* INCLUDED_AHKCTRL_H */
