#include "../../header/UI/UI Elements/Button/Buttons.h"
#include <iostream>

Button::Button(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load button texture: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

void Button::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Button::updateState(EventPollingManager& eventManager, const sf::RenderWindow& window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

    if (eventManager.pressedLeftMouseButton() &&
        sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
        state = ButtonState::PRESSED;
    }
    else if (state == ButtonState::PRESSED && !eventManager.pressedLeftMouseButton()) {
        state = ButtonState::RELEASED;
    }
}


ButtonState Button::getState() const {
    return state;
}

void Button::resetState() {
    state = ButtonState::RELEASED;
}
