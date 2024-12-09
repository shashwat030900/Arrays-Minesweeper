#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace UI {

    class GameplayUI {
    private:
        sf::Font bubbleBobbleFont;
        sf::Font dsDigibFont;

        // Text elements
        sf::Text mineText;
        sf::Text timeText;

        // Button element
        Button* restartButton = nullptr;
        bool restartButtonClicked = false;

        // Constants
        const int fontSize = 110;

        const float minetextTopOffset = 65.f;
        const float mineTextLeftOffset = 660.f;

        const float timeTextTopOffset = 65.f;
        const float timeTextLeftOffset = 1090.f;

        const float restartButtonTopOffset = 100.f;
        const float restartButtonLeftOffset = 920.f;

        const float buttonWidth = 80.f;
        const float buttonHeight = 80.f;
        const sf::Color textColor = sf::Color::Red;

        // Private methods for initialization
        void InitializeTexts();
        void InitializeButton();
        void LoadFonts();

        void RegisterButtonCallback();
        void RestartButtonCallback(ButtonType buttonType);

    public:
        GameplayUI();
        ~GameplayUI() = default;

        void Initialize();
        void Update(int remaining_mines, int remaining_time, Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);
        ButtonState GetRestartButtonState();
        void ResetButtons();
    };
}

