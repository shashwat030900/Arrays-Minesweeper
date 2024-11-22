#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include <iostream>

namespace UI {
    SplashScreenManager::SplashScreenManager(sf::RenderWindow* window) {
        gameWindow = window;
        Initialize();
    }

    SplashScreenManager::~SplashScreenManager() {
    }

    void SplashScreenManager::Initialize() {
        if (!logoTexture.loadFromFile("assets/textures/outscal_logo.png")) {
            std::cerr << "Failed to load logo texture" << std::endl;
        }
        logoSprite.setTexture(logoTexture);
        logoSprite.setPosition(GetLogoPosition());
    }

    void SplashScreenManager::Update() {
    }

    void SplashScreenManager::Render() {
        Show();
    }

    sf::Vector2f SplashScreenManager::GetLogoPosition() {
        float x_position = (gameWindow->getSize().x - logoWidth) / 2.0f;
        float y_position = (gameWindow->getSize().y - logoHeight) / 2.0f;
        return sf::Vector2f(x_position, y_position);
    }

    void SplashScreenManager::Show() {
        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < logoAnimationDuration) {
            gameWindow->clear();
            gameWindow->draw(logoSprite);
            gameWindow->display();
        }
    }

}
