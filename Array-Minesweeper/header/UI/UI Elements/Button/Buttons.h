#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"

namespace UIElements {

    enum class ButtonState {
        RELEASED,
        PRESSED
    };

    class Button {
    private:
        sf::Texture buttonTexture;
        sf::Sprite buttonSprite;
        ButtonState state = ButtonState::RELEASED;

    public:
        Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
        void UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window);
        void Render(sf::RenderWindow& window) const;
        void SetTextureRect(const sf::IntRect& rect);
        void Initialize(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
        ButtonState GetState() const;
        void ResetState();
    };
}
