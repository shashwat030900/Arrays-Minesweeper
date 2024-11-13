#include "../../header/UI/GameplayUI/GameplayUI.h"
#include <iostream>

GameplayUI::GameplayUI()
{

}

void GameplayUI::initialize() {
    loadFonts();
    initializeTexts();
    initializeButton();
}

void GameplayUI::loadFonts() {
    if (!bubble_bobble_font.loadFromFile("assets/fonts/bubbleBobble.ttf")) {
        std::cerr << "Error loading bubbleBobble font!" << std::endl;
    }
    if (!ds_digib_font.loadFromFile("assets/fonts/DS_DIGIB.ttf")) {
        std::cerr << "Error loading DS_DIGIB font!" << std::endl;
    }
}

void GameplayUI::initializeTexts() {
    // Mine Text
    mine_text.setFont(bubble_bobble_font);
    mine_text.setCharacterSize(font_size);
    mine_text.setFillColor(text_color);
    mine_text.setPosition(mine_text_left_offset, mine_text_top_offset);
    mine_text.setString("000");
    

    // Time Text
    time_text.setFont(ds_digib_font);
    time_text.setCharacterSize(font_size);
    time_text.setFillColor(text_color);
    time_text.setPosition(time_text_left_offset, time_text_top_offset);
    time_text.setString("000");
}

void GameplayUI::initializeButton() {
    restart_button = new Button("assets/textures/restart_button.png", sf::Vector2f(restart_button_left_offset, restart_button_top_offset), button_width, button_height);
}

void GameplayUI::update(int remaining_mines, int remaining_time, Event::EventPollingManager& eventManager, sf::RenderWindow& window) {
    mine_text.setString(std::to_string(remaining_mines));
    time_text.setString(std::to_string(remaining_time));
    restart_button->UpdateState(eventManager, window);
}

void GameplayUI::render(sf::RenderWindow& window) {
    window.draw(mine_text);
    window.draw(time_text);
    restart_button->Render(window);
}

void GameplayUI::updateMineText(const std::string& text)
{
    mine_text.setString(text);
}

bool GameplayUI::isRestartButtonPressed() {
    return restart_button->GetState() == ButtonState::PRESSED;
}
