#ifndef SPLASHSCREENMANAGER_H
#define SPLASHSCREENMANAGER_H

#include <SFML/Graphics.hpp>

class SplashScreenManager {
private:
    sf::RenderWindow* game_window;
    sf::Texture logo_texture;
    sf::Sprite logo_sprite;
    const float logo_width = 600.f;
    const float logo_height = 134.f;
    const float logo_animation_duration = 2.0f;

    void initializeLogo();
    sf::Vector2f getLogoPosition();

public:
    SplashScreenManager(sf::RenderWindow* window);
    ~SplashScreenManager();

    void initialize();
    void update();
    void render();
    void show();
};

#endif