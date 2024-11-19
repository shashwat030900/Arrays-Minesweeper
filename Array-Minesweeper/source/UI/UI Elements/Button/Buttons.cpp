#include "../../header/UI/UI Elements/Button/Buttons.h"
#include <iostream>

namespace UIElements {
    Button::Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height) {
        Initialize(texturePath, position, width, height);
    }

    void Button::Initialize(const std::string& texturePath, const sf::Vector2f& position, float width, float height) {
        if (!buttonTexture.loadFromFile(texturePath)) {
            std::cerr << "Failed to load button texture: " << texturePath << std::endl;
            return;
        }
        buttonSprite.setTexture(buttonTexture);
        buttonSprite.setPosition(position);
        buttonSprite.setScale(width / buttonTexture.getSize().x, height / buttonTexture.getSize().y);
    }
    void Button::UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        if (eventManager.PressedLeftMouseButton() &&
            buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            state = ButtonState::PRESSED;
        }
        else if (state == ButtonState::PRESSED && !eventManager.PressedLeftMouseButton()) {
            state = ButtonState::RELEASED;
        }
    }

    void Button::Render(sf::RenderWindow& window) const {
        window.draw(buttonSprite);
    }

    void Button::SetTextureRect(const sf::IntRect& rect) {
        buttonSprite.setTextureRect(rect);
    }

    ButtonState Button::GetState() const {
        return state;
    }

    void Button::ResetState() {
        state = ButtonState::RELEASED;
    }
}


