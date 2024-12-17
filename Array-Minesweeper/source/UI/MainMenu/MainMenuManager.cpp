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

    void MainMenuManager::handleButtons()
    {
        if (GetPlayButtonState() == ButtonState::PRESSED)
        {
            ResetButtonStates();
            current_state = GameState::GAMEPLAY;
            ResetButtonStates();
        }
        else if (GetQuitButtonState() == ButtonState::PRESSED)
        {
            ResetButtonStates();
            current_state = GameState::EXIT;
            ResetButtonStates();
        }
    }

    void MainMenuManager::InitializeBackground() {
        if (!backgroundTexture.loadFromFile(backgroundTexturePath)) {
            std::cerr << "Failed to load background texture" << std::endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setColor(sf::Color(255, 255, 255, backgroundAlpha));
    }

    void MainMenuManager::InitializeButtons() {
        playButton = new Button(playButtonTexturePath, GetButtonPosition(0.f, playButtonYPosition), buttonWidth, buttonHeight);
        quitButton = new Button(quitButtonTexturePath, GetButtonPosition(0.f, quitButtonYPosition), buttonWidth, buttonHeight);
        RegisterButtonCallbacks();
    }

    void MainMenuManager::RegisterButtonCallbacks()
    {
        playButton->RegisterCallbackFunction([this](UIElements::ButtonType buttonType) {
            if (buttonType == UIElements::ButtonType::LEFT_MOUSE_BUTTON) {
                Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
                playButton->SetButtonsState(ButtonState::PRESSED);
            }
            });

        // Register callback for the quit button
        quitButton->RegisterCallbackFunction([this](UIElements::ButtonType buttonType) {
            if (buttonType == UIElements::ButtonType::LEFT_MOUSE_BUTTON) {
                Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
                quitButton->SetButtonsState(ButtonState::PRESSED);
            }
            });
    }

    sf::Vector2f MainMenuManager::GetButtonPosition(float offsetX, float offsetY) {
        float x_position = (gameWindow->getSize().x - buttonWidth) / 2.0f + offsetX;
        float y_position = offsetY;
        return sf::Vector2f(x_position, y_position);
    }

    void MainMenuManager::Update(Event::EventPollingManager& eventManager)
    {
        handleButtons();
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

    ButtonState MainMenuManager::GetPlayButtonState() {
        return playButton->GetButtonState();
    }

    ButtonState MainMenuManager::GetQuitButtonState() {
        return quitButton->GetButtonState();
    }

    void MainMenuManager::ResetButtonStates() {
        playButton->ResetButtonState();
        quitButton->ResetButtonState();
    }
}
