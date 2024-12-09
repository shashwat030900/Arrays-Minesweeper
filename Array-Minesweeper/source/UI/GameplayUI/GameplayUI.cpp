#include "../../header/UI/GameplayUI/GameplayUI.h"
#include <iostream>

namespace UI {

    GameplayUI::GameplayUI()
    {
        Initialize();
    }

    void GameplayUI::Initialize() {
        LoadFonts();
        InitializeTexts();
        InitializeButton();
        RegisterButtonCallback();
    }

    void GameplayUI::LoadFonts() {
        if (!bubbleBobbleFont.loadFromFile("assets/fonts/bubbleBobble.ttf")) {
            std::cerr << "Error loading bubbleBobble font!" << std::endl;
        }
        if (!dsDigibFont.loadFromFile("assets/fonts/DS_DIGIB.ttf")) {
            std::cerr << "Error loading DS_DIGIB font!" << std::endl;
        }
    }

    void GameplayUI::RegisterButtonCallback()
    {
        restartButton->RegisterCallbackFunction([this](UIElements::ButtonType buttonType) {
            RestartButtonCallback(buttonType);
            });
    }

    void GameplayUI::RestartButtonCallback(ButtonType buttonType)
    {
        if (buttonType == UIElements::ButtonType::LEFT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            restartButton->SetButtonsState(ButtonState::PRESSED);
        }
    }

    void GameplayUI::InitializeTexts() {
        // Mine Text
        mineText.setFont(dsDigibFont);
        mineText.setCharacterSize(fontSize);
        mineText.setFillColor(textColor);
        mineText.setPosition(mineTextLeftOffset, minetextTopOffset);
        mineText.setString("000");


        // Time Text
        timeText.setFont(dsDigibFont);
        timeText.setCharacterSize(fontSize);
        timeText.setFillColor(textColor);
        timeText.setPosition(timeTextLeftOffset, timeTextTopOffset);
        timeText.setString("000");
    }

    void GameplayUI::InitializeButton() {
        restartButton = new Button("assets/textures/restart_button.png", sf::Vector2f(restartButtonLeftOffset, restartButtonTopOffset), buttonWidth, buttonHeight);

    }

    void GameplayUI::Update(int remaining_mines, int remaining_time, Event::EventPollingManager& eventManager, sf::RenderWindow& window) {
        mineText.setString(std::to_string(remaining_mines));
        timeText.setString(std::to_string(remaining_time));
        restartButton->UpdateState(eventManager, window);
    }

    void GameplayUI::Render(sf::RenderWindow& window) {
        window.draw(mineText);
        window.draw(timeText);
        restartButton->Render(window);
    }

    ButtonState GameplayUI::GetRestartButtonState() {
       return restartButton->GetButtonState();
    }

    void GameplayUI::ResetButtons()
    {
        restartButton->ResetButtonState();
    }
}

