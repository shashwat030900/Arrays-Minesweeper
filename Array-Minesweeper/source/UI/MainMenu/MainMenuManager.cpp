#include "../../header/UI/MainMenu/MainMenuManager.h"
#include <iostream>

MainMenuManager::MainMenuManager(sf::RenderWindow* window) {
    gameWindow = window;
    playButton = nullptr;
    quitButton = nullptr;
}

MainMenuManager::~MainMenuManager() {
    delete playButton;
    delete quitButton;
}

void MainMenuManager::Initialize() {
    InitializeBackground();
    InitializeButtons();
}

void MainMenuManager::InitializeBackground() {
    if (!backgroundTexture.loadFromFile("assets/textures/minesweeper_bg.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setColor(sf::Color(255, 255, 255, backgroundAlpha));
}
void MainMenuManager::InitializeButtons() {
    playButton = new Button("assets/textures/play_button.png", GetButtonPosition(0.f, playButtonYPosition), buttonWidth, buttonHeight);
    quitButton = new Button("assets/textures/quit_button.png", GetButtonPosition(0.f, quitButtonYPosition), buttonWidth, buttonHeight);
}

sf::Vector2f MainMenuManager::GetButtonPosition(float offsetX, float offsetY) {
    float x_position = (gameWindow->getSize().x - buttonWidth) / 2.0f + offsetX;
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
    gameWindow->draw(backgroundSprite);
    if (playButton) playButton->Render(*gameWindow);
    if (quitButton) quitButton->Render(*gameWindow);
}

void MainMenuManager::UpdateButtonStates(Event::EventPollingManager& eventManager) {
    if (playButton) playButton->UpdateState(eventManager, *gameWindow);
    if (quitButton) quitButton->UpdateState(eventManager, *gameWindow);
}

bool MainMenuManager::IsPlayButtonPressed() const {
    return playButton && playButton->GetState() == ButtonState::PRESSED;
}

bool MainMenuManager::IsQuitButtonPressed() const {
    return quitButton && quitButton->GetState() == ButtonState::PRESSED;
}

void MainMenuManager::ResetButtonStates() {
    if (playButton) playButton->ResetState();
    if (quitButton) quitButton->ResetState();
}
