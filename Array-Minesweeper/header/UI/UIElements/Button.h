#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
#include <functional>

namespace UIElements {

    enum class MouseButtonType
    {
        LEFT_MOUSE_BUTTON,
        RIGHT_MOUSE_BUTTON
    };

    class Button {
    private:
        sf::Texture button_texture;
        sf::Sprite buttonSprite;

        void initialize(const std::string& texture_path, const sf::Vector2f& position, float width, float height);
        bool isMouseOnSprite(Event::EventPollingManager& event_mamnager, const sf::RenderWindow& window);
        using CallbackFunction = std::function < void(MouseButtonType)>;
        CallbackFunction callback_function = nullptr;


    public:
        Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height);

        void render(sf::RenderWindow& window) const;

        void setTextureRect(const sf::IntRect& rect);

        void handelButtonInteractions(Event::EventPollingManager& event_manager, const sf::RenderWindow& window);
        void registerCallbackFunction(CallbackFunction button_function);
    };
}