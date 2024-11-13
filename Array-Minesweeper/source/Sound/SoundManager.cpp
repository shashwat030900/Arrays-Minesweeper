#include "../../header/Sound/SoundManager.h"
#include <iostream>

namespace Sound
{
    sf::Music SoundManager::background_music;
    sf::SoundBuffer SoundManager::buffer_button_click;
    sf::SoundBuffer SoundManager::buffer_flag_sound;
    sf::SoundBuffer SoundManager::buffer_explosion;
    sf::SoundBuffer SoundManager::buffer_game_won;
    sf::Sound SoundManager::sound_effect;
    float SoundManager::background_music_volume = 50.0f; // Default volume

    void SoundManager::Initialize()
    {
        // Update the paths based on the directory structure
        LoadBackgroundMusicFromFile("assets/sounds/background_music.mp3");
        LoadSoundFromFile("assets/sounds/button_click_sound.wav",
            "assets/sounds/flag_sound.wav",
            "assets/sounds/explosion_sound.wav",
            "assets/sounds/game_won_sound.wav");
    }

    void SoundManager::LoadBackgroundMusicFromFile(const std::string& path)
    {
        if (!background_music.openFromFile(path))
            std::cerr << "Error loading background music file: " << path << std::endl;
    }

    void SoundManager::LoadSoundFromFile(const std::string& button_click_path, const std::string& flag_sound_path,
        const std::string& explosion_sound_path, const std::string& game_won_sound_path)
    {
        if (!buffer_button_click.loadFromFile(button_click_path))
            std::cerr << "Error loading sound file: " << button_click_path << std::endl;
        if (!buffer_flag_sound.loadFromFile(flag_sound_path))
            std::cerr << "Error loading sound file: " << flag_sound_path << std::endl;
        if (!buffer_explosion.loadFromFile(explosion_sound_path))
            std::cerr << "Error loading sound file: " << explosion_sound_path << std::endl;
        if (!buffer_game_won.loadFromFile(game_won_sound_path))
            std::cerr << "Error loading sound file: " << game_won_sound_path << std::endl;
    }

    void SoundManager::PlaySound(SoundType soundType)
    {
        switch (soundType)
        {
        case SoundType::BUTTON_CLICK:
            sound_effect.setBuffer(buffer_button_click);
            break;
        case SoundType::FLAG:
            sound_effect.setBuffer(buffer_flag_sound);
            break;
        case SoundType::EXPLOSION:
            sound_effect.setBuffer(buffer_explosion);
            break;
        case SoundType::GAME_WON:
            sound_effect.setBuffer(buffer_game_won);
            break;
        default:
            std::cerr << "Invalid sound type" << std::endl;
            return;
        }

        sound_effect.play();
    }

    void SoundManager::PlayBackgroundMusic()
    {
        background_music.setLoop(true);
        background_music.setVolume(background_music_volume);
        background_music.play();
    }
}
