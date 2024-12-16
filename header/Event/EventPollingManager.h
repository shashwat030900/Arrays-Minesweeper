#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace Event
{
    enum class MouseButtonState
    {
        PRESSED,
        HELD,
        RELEASED,
    };


    class EventPollingManager
    {
    private:
        sf::Event gameEvent;
        sf::RenderWindow* gameWindow;

        MouseButtonState leftMouseButtonState;
        MouseButtonState rightMouseButtonState;

        bool IsGameWindowOpen();
        bool GameWindowWasClosed();
        bool HasQuitGame();
        bool IsKeyboardEvent();
        void UpdateMouseButtonState(MouseButtonState& button_state, sf::Mouse::Button button_type);

    public:
        EventPollingManager(sf::RenderWindow* window);
        ~EventPollingManager();

        void Initialize(sf::RenderWindow* window);
        void Update();
        void ProcessEvents();

        bool PressedEscapeKey();
        bool PressedLeftMouseButton();
        bool PressedRightMouseButton();

        sf::Vector2i GetMousePosition(const sf::RenderWindow& window);
    };
}
