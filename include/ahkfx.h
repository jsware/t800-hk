/**
 * @file ahkfx.h
 * @author John Scott
 * @brief Manage Aerial HK effects (mainly sound).
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

    static const int VOL_MIN = 0;
    static const int VOL_CENTER = 15;
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
    bool readAck();

    bool atCommand(const char *cmd);

  private:
    //
    // Implementation...
    //
    int volume;
};

/**
 * @brief Aerial Hunter Killer Sound Effects.
 * 
 */
extern AerialHunterKillerEffects AHKEffects;

#endif /* INCLUDED_AHKFX_H */
