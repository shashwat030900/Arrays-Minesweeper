#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include <iostream>

SplashScreenManager::SplashScreenManager(sf::RenderWindow* window) {
    game_window = window;
}

SplashScreenManager::~SplashScreenManager() {
}

void SplashScreenManager::initialize() {
    if (!logo_texture.loadFromFile("assets/textures/outscal_logo.png")) {
        std::cerr << "Failed to load logo texture" << std::endl;
    }
    logo_sprite.setTexture(logo_texture);
    logo_sprite.setPosition(getLogoPosition());
}

void SplashScreenManager::update() {
    // Update logic if needed (e.g., animations)
}

void SplashScreenManager::render() {
    game_window->draw(logo_sprite);
}

sf::Vector2f SplashScreenManager::getLogoPosition() {
    float x_position = (game_window->getSize().x - logo_width) / 2.0f;
    float y_position = (game_window->getSize().y - logo_height) / 2.0f;
    return sf::Vector2f(x_position, y_position);
}

void SplashScreenManager::show() {

    initialize();

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < logo_animation_duration) {
        game_window->clear();
        render();
        game_window->display();
    }
}
