#pragma once
#include "../../header/UI/UI Elements/Image/Image.h"
#include "../../header/Event/EventPollingManager.h"

enum class ButtonState {
    RELEASED,
    PRESSED
};

class Button : public Image {
private:
    ButtonState state = ButtonState::RELEASED;

public:
    Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
    void UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window);
    ButtonState GetState() const;
    void ResetState();
};
