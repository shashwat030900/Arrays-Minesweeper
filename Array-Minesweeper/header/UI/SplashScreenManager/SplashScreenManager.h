#ifndef SPLASHSCREENMANAGER_H
#define SPLASHSCREENMANAGER_H

#include <SFML/Graphics.hpp>

namespace UI {
    class SplashScreenManager {
    private:
        sf::RenderWindow* gameWindow;
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        const float logoWidth = 600.f;
        const float logoHeight = 134.f;
        const float logoAnimationDuration = 2.0f;

        sf::Vector2f GetLogoPosition();

    public:
        SplashScreenManager(sf::RenderWindow* window);
        ~SplashScreenManager();

        void Initialize();
        void Update();
        void Render();
        void Show();
    };
}

#endif