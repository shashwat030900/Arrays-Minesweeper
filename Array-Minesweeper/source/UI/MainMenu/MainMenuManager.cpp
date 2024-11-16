#include "../../header/UI/MainMenu/MainMenuManager.h"
#include <iostream>

MainMenuManager::MainMenuManager(sf::RenderWindow* window) {
    game_window = window;
    play_button = nullptr;
    quit_button = nullptr;
}

MainMenuManager::~MainMenuManager() {
    delete play_button;
    delete quit_button;
}

void MainMenuManager::Initialize() {
    InitializeBackground();
    InitializeButtons();
}

void MainMenuManager::InitializeBackground() {
    if (!background_texture.loadFromFile("assets/textures/minesweeper_bg.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
        return;
    }
    background_sprite.setTexture(background_texture);
    background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
}
void MainMenuManager::InitializeButtons() {
    play_button = new Button("assets/textures/play_button.png", GetButtonPosition(0.f, play_button_y_position), button_width, button_height);
    quit_button = new Button("assets/textures/quit_button.png", GetButtonPosition(0.f, quit_button_y_position), button_width, button_height);
}

sf::Vector2f MainMenuManager::GetButtonPosition(float offsetX, float offsetY) {
    float x_position = (game_window->getSize().x - button_width) / 2.0f + offsetX;
    float y_position = offsetY;
    return sf::Vector2f(x_position, y_position);
}

void MainMenuManager::Update(Event::EventPollingManager& eventManager) {
    // Update logic if needed (e.g., animations)
    Initialize();
    UpdateButtonStates(eventManager);
}

void MainMenuManager::Render() {
    
    Show();
}

void MainMenuManager::Show() {
    game_window->draw(background_sprite);
    if (play_button) play_button->Render(*game_window);
    if (quit_button) quit_button->Render(*game_window);
}

void MainMenuManager::UpdateButtonStates(Event::EventPollingManager& eventManager) {
    if (play_button) play_button->UpdateState(eventManager, *game_window);
    if (quit_button) quit_button->UpdateState(eventManager, *game_window);
}

bool MainMenuManager::IsPlayButtonPressed() const {
    return play_button && play_button->GetState() == ButtonState::PRESSED;
}

bool MainMenuManager::IsQuitButtonPressed() const {
    return quit_button && quit_button->GetState() == ButtonState::PRESSED;
}

void MainMenuManager::ResetButtonStates() {
    if (play_button) play_button->ResetState();
    if (quit_button) quit_button->ResetState();
}
