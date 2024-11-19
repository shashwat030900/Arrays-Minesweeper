#ifndef MAINMENUMANAGER_H
#define MAINMENUMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace UI {
    class MainMenuManager {
    private:
        sf::RenderWindow* gameWindow;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        Button* playButton;
        Button* quitButton;

        // Constants for button dimensions and positions
        const float buttonWidth = 300.f;
        const float buttonHeight = 100.f;
        const float playButtonYPosition = 600.f;
        const float quitButtonYPosition = 750.f;
        const float backgroundAlpha = 85.f;

        void InitializeBackground();
        void InitializeButtons();
        sf::Vector2f GetButtonPosition(float offsetX, float offsetY);

    public:
        MainMenuManager(sf::RenderWindow* window);
        ~MainMenuManager();

        void Initialize();
        void Update(Event::EventPollingManager& eventManager);
        void Render();
        void Show();

        void UpdateButtonStates(Event::EventPollingManager& eventManager);
        bool IsPlayButtonPressed() const;
        bool IsQuitButtonPressed() const;
        void ResetButtonStates();
    };
}


#endif // MAINMENUMANAGER_H
