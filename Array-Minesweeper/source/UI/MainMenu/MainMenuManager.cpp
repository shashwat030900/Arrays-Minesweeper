#include "../../header/UI/MainMenu/MainMenuManager.h"
#include <iostream>

namespace UI {
    MainMenuManager::MainMenuManager(sf::RenderWindow* window) {
        gameWindow = window;
        Initialize();
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

        playButton->RegisterCallbackFunction([this](UIElements::ButtonType buttonType) {
            if (buttonType == UIElements::ButtonType::LEFT_MOUSE_BUTTON) {
                OnPlayButtonClicked();
            }
            });

        // Register callback for the quit button
        quitButton->RegisterCallbackFunction([this](UIElements::ButtonType buttonType) {
            if (buttonType == UIElements::ButtonType::LEFT_MOUSE_BUTTON) {
                OnQuitButtonClicked();
            }
            });
    }

    sf::Vector2f MainMenuManager::GetButtonPosition(float offsetX, float offsetY) {
        float x_position = (gameWindow->getSize().x - buttonWidth) / 2.0f + offsetX;
        float y_position = offsetY;
        return sf::Vector2f(x_position, y_position);
    }

    void MainMenuManager::Update(Event::EventPollingManager& eventManager) {
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

    bool MainMenuManager::OnPlayButtonClicked() {
        std::cout << "Play button clicked! Transitioning to gameplay..." << std::endl;
        return true;
    }

    bool MainMenuManager::OnQuitButtonClicked() {
        std::cout << "Quit button clicked! Exiting the game..." << std::endl;
        return true;
    }

    //bool MainMenuManager::IsPlayButtonPressed() const {
    //    return playButton && playButton->GetState() == ButtonState::PRESSED;
    //}

    //bool MainMenuManager::IsQuitButtonPressed() const {
    //    return quitButton && quitButton->GetState() == ButtonState::PRESSED;
    //}

    //void MainMenuManager::ResetButtonStates() {
    //    if (playButton) playButton->ResetState();
    //    if (quitButton) quitButton->ResetState();
    //}

}
