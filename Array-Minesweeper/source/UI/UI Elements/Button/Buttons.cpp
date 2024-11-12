#include "../../header/UI/UI Elements/Button/Buttons.h"
#include <iostream>

Button::Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height) {
    Image::Initialize(texturePath, width, height, position);
}

void Button::UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

    if (eventManager.pressedLeftMouseButton() &&
        GetGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
        state = ButtonState::PRESSED;
    }
    else if (state == ButtonState::PRESSED && !eventManager.pressedLeftMouseButton()) {
        state = ButtonState::RELEASED;
    }
}

ButtonState Button::GetState() const {
    return state;
}

void Button::ResetState() {
    state = ButtonState::RELEASED;
}
