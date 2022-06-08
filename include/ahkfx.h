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

/**
 * @brief Aerial Hunter-Killer Sound Effects.
 * 
 */
class AerialHunterKillerEffects
{
  public:
    //
    // Constants...
    //
    static const char *SND_STOP;
    static const char *SND_FLY;
    static const char *SND_FLYMORE;
    static const char *SND_LAND;
    static const char *SND_SCENE_01;
    
    static const int VOL_MIN = 0;
    static const int VOL_CENTRE = 15;
    static const int VOL_MAX = 30;

  public:
    //
    // Constructors...
    //

    /**
     * @brief Construct a new Aerial HK Sound.
     */
    AerialHunterKillerEffects();

  public:
    //
    // Accessors...
    //

    /**
     * @brief Indicate blue front lighting effects lights on/off.
     * 
     * @return true when lights on.
     * @return false when lights off.
     */
    bool isBlueFrontLights();

    /**
     * @brief Indicate red back lighting effects lights on/off.
     * 
     * @return true when lights on.
     * @return false when lights off.
     */
    bool isRedBackLights();

  public:
    //
    // Mutators...
    //

    /**
     * @brief Begin Controlling the AHK Effects.
     * 
     */
    void begin();

    /**
     * @brief Handle AHK Effects.
     * 
     */
    void handle();

    /**
     * @brief Set blue front lighting effects on/off.
     * 
     * @param light true turns on, false turns off.
     */
    void setBlueFrontLights(bool light);

    /**
     * @brief Set red back lighting effects on/off.
     * 
     * @param light true turns on, false turns off.
     */
    void setRedBackLights(bool light);

    /**
     * @brief Toggle blue front lighting effects on/off.
     * 
     */
    void toggleBlueFrontLights() {
      setBlueFrontLights(!isBlueFrontLights());
    };

    /**
     * @brief Toggle red back lighting effects on/off.
     * 
     */
    void toggleRedBackLights() {
      setRedBackLights(!isRedBackLights());
    };

    /**
     * @brief Increase volume.
     * 
     */
    void volUp() {
      setVolume(volume + 5);
    }

    /**
     * @brief Decrease volume.
     * 
     */
    void volDown() {
      setVolume(volume - 5);
    }

    /**
     * @brief Set the volume level.
     * 
     * @param level the volume level to use.
     */
    void setVolume(int level);

    /**
     * @brief Play particular sound
     * 
     * @param sound The SND_* sound to play.
     * @param repeat true to play sound on a loop.
     */
    void play(const char *sound);

    /**
     * @brief Stop playing any sound.
     * 
     */
    void stop() {
      play(SND_STOP);
    };

  private:
    //
    // Helpers...
    //

    /**
     * @brief Read sound card acknowledgement.
     * 
     * @return true 
     * @return false 
     */
    bool readAck();

    /**
     * @brief Send sound card a command.
     * 
     * @param cmd The command (without the AT+ prefix or \r\n newline suffix).
     * @return true If the sound card acknowledged OK.
     * @return false  If the sound card did not acknowledge OK.
     */
    bool atCommand(const char *cmd);

  private:
    //
    // Implementation...
    //

    /**
     * @brief Current volume of sound card.
     * 
     */
    int volume;
};

/**
 * @brief Aerial Hunter Killer Sound Effects.
 * 
 */
extern AerialHunterKillerEffects AHKEffects;

#endif /* INCLUDED_AHKFX_H */
