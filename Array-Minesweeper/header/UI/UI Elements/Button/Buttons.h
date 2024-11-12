#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Image/Image.h"
#include "../../header/Event/EventPollingManager.h"

enum class ButtonState {
    RELEASED,
    PRESSED,
    HELD
};

class Button {
private:
    UI::UIElement::Image image;       // Use Image class for rendering
    ButtonState state = ButtonState::RELEASED;

public:
    Button(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size);
    void Render(sf::RenderWindow& window);
    void UpdateState(Event::EventPollingManager& eventManager, const sf::RenderWindow& window);

    ButtonState GetState() const;
    void ResetState();
};

#endif // BUTTON_H
