#ifndef MAINMENUMANAGER_H
#define MAINMENUMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

using namespace Event;

class MainMenuManager {
private:
    sf::RenderWindow* game_window;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Texture play_button_texture;
    sf::Sprite play_button_sprite;
    sf::Texture quit_button_texture;
    sf::Sprite quit_button_sprite;

    Button *play_button = nullptr;
    Button *quit_button = nullptr;


    // Constants:
    const float button_width = 300.f;           
    const float button_height = 100.f;          

    const float play_button_y_position = 600.f;
    const float quit_button_y_position = 750.f;

    const float background_alpha = 85.f;

    void initializeBackground();
    void initializeButtons();
    sf::Vector2f getButtonPosition(float offsetX, float offsetY);

public:
    MainMenuManager(sf::RenderWindow* window);
    ~MainMenuManager();

    void initialize();
    void update(EventPollingManager& eventManager);
    void render();
    void show();
    void updateButtonStates(EventPollingManager& eventManager);

    bool isPlayButtonPressed() const;
    bool isQuitButtonPressed() const;

    void resetButtonStates();

};

#endif