#include "../../header/UI/MainMenu/MainMenuManager.h"
#include <iostream>

MainMenuManager::MainMenuManager(sf::RenderWindow* window) {
    game_window = window;
}

MainMenuManager::~MainMenuManager() {
}

void MainMenuManager::initialize() {
    initializeBackground();
    initializeButtons();
    initialized = true;
}

void MainMenuManager::initializeBackground() {
    if (!background_texture.loadFromFile("assets/textures/minesweeper_bg.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    background_sprite.setTexture(background_texture);
    background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
}

void MainMenuManager::initializeButtons() {
    if (!play_button_texture.loadFromFile("assets/textures/play_button.png")) {
        std::cerr << "Failed to load play button texture" << std::endl;
    }
    play_button_sprite.setTexture(play_button_texture);
    play_button_sprite.setScale(button_width / play_button_texture.getSize().x, button_height / play_button_texture.getSize().y);
    play_button_sprite.setPosition(getButtonPosition(0.f, play_button_y_position));

    if (!quit_button_texture.loadFromFile("assets/textures/quit_button.png")) {
        std::cerr << "Failed to load quit button texture" << std::endl;
    }
    quit_button_sprite.setTexture(quit_button_texture);
    quit_button_sprite.setScale(button_width / quit_button_texture.getSize().x, button_height / quit_button_texture.getSize().y);
    quit_button_sprite.setPosition(getButtonPosition(0.f, quit_button_y_position));
}


sf::Vector2f MainMenuManager::getButtonPosition(float offsetX, float offsetY) {
    float x_position = (game_window->getSize().x - button_width) / 2.0f + offsetX;
    float y_position = offsetY;
    return sf::Vector2f(x_position, y_position);
}

void MainMenuManager::update() {
    // Update logic if needed (e.g., animations)
}

void MainMenuManager::render() {
    game_window->draw(background_sprite);
    game_window->draw(play_button_sprite);
    game_window->draw(quit_button_sprite);
}

void MainMenuManager::show() {
    initialize();
    render();
}

//void MainMenuManager::handleEvent(const sf::Event& event, bool& startGame, bool& quitGame) {
//    if (event.type == sf::Event::MouseButtonPressed) {
//        sf::Vector2i mouse_position = sf::Mouse::getPosition(*game_window);
//
//        if (play_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
//            startGame = true;
//        }
//
//        if (quit_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
//            quitGame = true;
//        }
//    }
//}