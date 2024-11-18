#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace Sound
{
    enum class SoundType
    {
        BUTTON_CLICK,
        FLAG,
        EXPLOSION,
        GAME_WON
    };

    class SoundManager
    {
    private:
        static sf::Music backgroundMusic;
        static sf::SoundBuffer bufferButtonClick;
        static sf::SoundBuffer bufferFlagSound;
        static sf::SoundBuffer bufferExplosion;
        static sf::SoundBuffer bufferGameWon;
        static sf::Sound soundEffect;
        static float backgroundMusicVolume;

    public:
        // Initialization and loading functions
        static void Initialize();
        static void PlaySound(SoundType soundType);
        static void PlayBackgroundMusic();

    private:
        static void LoadBackgroundMusicFromFile(const std::string& path);
        static void LoadSoundFromFile(const std::string& button_click_path, const std::string& flag_sound_path,
        const std::string& explosion_sound_path, const std::string& game_won_sound_path);
    };
}
