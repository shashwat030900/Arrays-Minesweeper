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

        sf::Vector2i mouse_position = eventManager.GetMousePosition(window);
        if (eventManager.PressedLeftMouseButton() &&
            buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
            if (callback_function) callback_function(ButtonType::LEFT_MOUSE_BUTTON);
        }
        else if (eventManager.PressedRightMouseButton() &&
            buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
            if (callback_function) callback_function(ButtonType::RIGHT_MOUSE_BUTTON);
        }
    }

    void Button::Render(sf::RenderWindow& window) const {
        window.draw(buttonSprite);
    }

    void Button::SetTextureRect(const sf::IntRect& rect) {
        buttonSprite.setTextureRect(rect);
    }

    void Button::RegisterCallbackFunction(CallbackFunction button_callback) {
        callback_function = button_callback;
    }
}


