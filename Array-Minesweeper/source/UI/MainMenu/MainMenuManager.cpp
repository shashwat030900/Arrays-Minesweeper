#include "../../header/UI/MainMenu/MainMenuManager.h"
#include <iostream>

MainMenuManager::MainMenuManager(sf::RenderWindow* window) {
    game_window = window;
}

MainMenuManager::~MainMenuManager() {
    delete play_button;
    delete quit_button;
    
}

void MainMenuManager::initialize() {
    initializeBackground();
    initializeButtons();
}

void MainMenuManager::initializeBackground() {
    if (!background_texture.loadFromFile("assets/textures/minesweeper_bg.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    background_sprite.setTexture(background_texture);
    background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
}

void MainMenuManager::initializeButtons() {
    play_button = new Button("assets/textures/play_button.png", getButtonPosition(0.f, play_button_y_position), sf::Vector2f(button_width, button_height));
    quit_button = new Button("assets/textures/quit_button.png", getButtonPosition(0.f, quit_button_y_position), sf::Vector2f(button_width, button_height));
}


sf::Vector2f MainMenuManager::getButtonPosition(float offsetX, float offsetY) {
    float x_position = (game_window->getSize().x - button_width) / 2.0f + offsetX;
    float y_position = offsetY;
    return sf::Vector2f(x_position, y_position);
}

void MainMenuManager::update(EventPollingManager& eventManager) {
    // Update logic if needed (e.g., animations)
    show();
    updateButtonStates(eventManager);
}

void MainMenuManager::render() {
    game_window->draw(background_sprite);
    if (play_button) play_button->render(*game_window);
    if (quit_button) quit_button->render(*game_window);
}

void MainMenuManager::show() {
    initialize();
    render();
}

void MainMenuManager::updateButtonStates(EventPollingManager& eventManager) {
    if (play_button) play_button->updateState(eventManager, *game_window);
    if (quit_button) quit_button->updateState(eventManager, *game_window);
}

bool MainMenuManager::isPlayButtonPressed() const {
    return play_button && play_button->getState() == ButtonState::PRESSED;
}

bool MainMenuManager::isQuitButtonPressed() const {
    return quit_button && quit_button->getState() == ButtonState::PRESSED;
}

void MainMenuManager::resetButtonStates() {
    if (play_button) play_button->resetState();
    if (quit_button) quit_button->resetState();
}