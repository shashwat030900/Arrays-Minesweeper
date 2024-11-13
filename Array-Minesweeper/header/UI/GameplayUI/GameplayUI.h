#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

class GameplayUI {
private:
    sf::Font bubble_bobble_font;
    sf::Font ds_digib_font;

    // Text elements
    sf::Text mine_text;
    sf::Text time_text;

    // Button element
    Button *restart_button = nullptr;

    // Constants
    const int font_size = 110;
    const float mine_text_top_offset = 65.f;
    const float mine_text_left_offset = 660.f;
    const float time_text_top_offset = 65.f;
    const float time_text_left_offset = 1090.f;
    const float restart_button_top_offset = 100.f;
    const float restart_button_left_offset = 920.f;
    const float button_width = 80.f;
    const float button_height = 80.f;
    const sf::Color text_color = sf::Color::Red;

    // Private methods for initialization
    void initializeTexts();
    void initializeButton();
    void loadFonts();

public:
    GameplayUI();
    ~GameplayUI() = default;

    void initialize();
    void update(int remaining_mines, int remaining_time, Event::EventPollingManager& eventManager, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void updateMineText(const std::string& text);
    bool isRestartButtonPressed();
};
