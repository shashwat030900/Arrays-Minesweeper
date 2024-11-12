#ifndef MAINMENUMANAGER_H
#define MAINMENUMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

class MainMenuManager {
private:
    sf::RenderWindow* game_window;
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    Button* play_button;
    Button* quit_button;

    // Constants for button dimensions and positions
    const float button_width = 300.f;
    const float button_height = 100.f;
    const float play_button_y_position = 600.f;
    const float quit_button_y_position = 750.f;
    const float background_alpha = 85.f;

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

#endif // MAINMENUMANAGER_H
