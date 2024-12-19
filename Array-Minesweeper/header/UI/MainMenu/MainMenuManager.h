#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

namespace UI {

    using namespace UIElements;

    class MainMenuManager {
    private:
        sf::RenderWindow* game_window;
        sf::Texture background_texture;
        sf::Sprite background_sprite;

        Button* play_button;
        Button* quit_button;

        // Constants for button dimensions and positions
        const std::string background_texture_path = "assets/textures/minesweeper_bg.png";
        const std::string play_button_texture_path = "assets/textures/play_button.png";
        const std::string quit_button_texture_path = "assets/textures/quit_button.png";

        const float button_width = 300.f;
        const float button_height = 100.f;
        const float play_button_y_position = 600.f;
        const float quit_button_y_position = 750.f;
        const float background_alpha = 85.f;
        
        void initialize();
        void initializeBackground();
        void initializeButtons();

        void playButtonCallback(ButtonType mouse_button_type);
        void quitButtonCallback(ButtonType mouse_button_type);
        void registerButtonCallbacks();

        sf::Vector2f getButtonPosition(float offsetX, float offsetY);

    public:
        MainMenuManager(sf::RenderWindow* window);
        ~MainMenuManager();

        void update(Event::EventPollingManager eventManager);
        void render();
        void show();

        void checkForButtonClicks(Event::EventPollingManager& eventManager);
    };
}
