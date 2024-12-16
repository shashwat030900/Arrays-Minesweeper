#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
#include <functional>

namespace UIElements {

    enum class ButtonType {
        LEFT_MOUSE_BUTTON,
        RIGHT_MOUSE_BUTTON
    };

    enum class ButtonState {
        PRESSED,
        HELD,
        RELEASED
    };

    class Button {
    private:
        sf::Texture buttonTexture;
        sf::Sprite buttonSprite;
        ButtonState buttonState;

        using CallbackFunction = std::function<void(ButtonType)>;
        CallbackFunction callback_function = nullptr;

        bool IsMouseOnSprite(Event::EventPollingManager& eventManager, const sf::RenderWindow& window);

    public:
        Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
        void UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window);
        void Render(sf::RenderWindow& window) const;
        void SetTextureRect(const sf::IntRect& rect);
        void RegisterCallbackFunction(CallbackFunction button_callback);
        void Initialize(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
        
        void ResetButtonState();
        void SetButtonsState(ButtonState buttonState);
        ButtonState GetButtonState();
    };
}
