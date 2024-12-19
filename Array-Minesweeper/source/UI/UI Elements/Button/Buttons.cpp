#include "../../header/UI/UI Elements/Button/Buttons.h"
#include <iostream>

namespace UIElements {

    Button::Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height)
    {
        initialize(texture_path, position, width, height);
    }

    void Button::initialize(const std::string& texture_path, const sf::Vector2f& position, float width, float height)
    {
        if (!button_texture.loadFromFile(texture_path)) {
            std::cerr << "Failed to load button texture: " << texture_path << std::endl;
            return;
        }

        buttonSprite.setTexture(button_texture);
        buttonSprite.setPosition(position);
        buttonSprite.setScale(width / button_texture.getSize().x, height / button_texture.getSize().y);
    }

    void Button::handleButtonInteractions(Event::EventPollingManager& event_manager, const sf::RenderWindow& window) {

        if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window))
            callback_function(ButtonType::LEFT_MOUSE_BUTTON);
        else if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window))
            callback_function(ButtonType::RIGHT_MOUSE_BUTTON);
    }

    bool Button::isMouseOnSprite(Event::EventPollingManager& event_manager, const sf::RenderWindow& window)
    {
        sf::Vector2i mouse_position = event_manager.getMousePosition();
        return buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
    }

    void Button::render(sf::RenderWindow& window) const { window.draw(buttonSprite); }

    void Button::setTextureRect(const sf::IntRect& rect) { buttonSprite.setTextureRect(rect); }

    void Button::registerCallbackFunction(CallbackFunction button_callback) { callback_function = button_callback; }
}
