#include "../../header/UI/UI Elements/Button/Buttons.h"
#include <iostream>

Button::Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height) {
    Initialize(texturePath, position, width, height);
}

void Button::Initialize(const std::string& texturePath, const sf::Vector2f& position, float width, float height) {
    if (!button_texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load button texture: " << texturePath << std::endl;
        return;
    }
    button_sprite.setTexture(button_texture);
    button_sprite.setPosition(position);
    button_sprite.setScale(width / button_texture.getSize().x, height / button_texture.getSize().y);
}
void Button::UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

    if (eventManager.pressedLeftMouseButton() &&
        button_sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
        Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
        state = ButtonState::PRESSED;
    }
    else if (state == ButtonState::PRESSED && !eventManager.pressedLeftMouseButton()) {
        state = ButtonState::RELEASED;
    }
}

void Button::Render(sf::RenderWindow& window) const {
    window.draw(button_sprite);
}

void Button::SetTextureRect(const sf::IntRect& rect) {
    button_sprite.setTextureRect(rect);
}

ButtonState Button::GetState() const {
    return state;
}

void Button::ResetState() {
    state = ButtonState::RELEASED;
}
