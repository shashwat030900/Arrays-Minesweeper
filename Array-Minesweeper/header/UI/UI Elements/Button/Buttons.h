// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"

using namespace Event;

enum class ButtonState {
    PRESSED,
    HELD,
    RELEASED
};

class Button {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    ButtonState state = ButtonState::RELEASED;

public:
    Button(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size);
    void render(sf::RenderWindow& window);
    void updateState(EventPollingManager& eventManager, const sf::RenderWindow& window);
    ButtonState getState() const;
    void resetState();
};

#endif // BUTTON_H
