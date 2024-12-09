#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameWindow/GameWindowManager.h"
#include <iostream>

namespace Event
{
    using namespace GameWindow;

    EventPollingManager::EventPollingManager(sf::RenderWindow* window)
    {
        Initialize(window);
    }

    EventPollingManager::~EventPollingManager() = default;

    void EventPollingManager::Initialize(sf::RenderWindow* window)
    {
        gameWindow = window;
        leftMouseButtonState = MouseButtonState::RELEASED;
        rightMouseButtonState = MouseButtonState::RELEASED;
    }

    void EventPollingManager::Update()
    {
        UpdateMouseButtonState(leftMouseButtonState, sf::Mouse::Left);
        UpdateMouseButtonState(rightMouseButtonState, sf::Mouse::Right);
    }

    void EventPollingManager::ProcessEvents()
    {
        if (IsGameWindowOpen())
        {
            while (gameWindow->pollEvent(gameEvent))
            {
                if (GameWindowWasClosed() || HasQuitGame())
                    gameWindow->close();
            }
        }
    }

    void EventPollingManager::UpdateMouseButtonState(MouseButtonState& button_state, sf::Mouse::Button button_type)
    {
        if (sf::Mouse::isButtonPressed(button_type))
        {
            switch (button_state)
            {
            case MouseButtonState::RELEASED:
                button_state = MouseButtonState::PRESSED;
                break;
            case MouseButtonState::PRESSED:
                button_state = MouseButtonState::HELD;
                break;
            }
        }
        else
        {
            button_state = MouseButtonState::RELEASED;
        }
    }

    bool EventPollingManager::IsGameWindowOpen()
    {
        return gameWindow != nullptr;
    }

    bool EventPollingManager::GameWindowWasClosed()
    {
        return gameEvent.type == sf::Event::Closed;
    }

    bool EventPollingManager::HasQuitGame()
    {
        return (IsKeyboardEvent() && PressedEscapeKey());
    }

    bool EventPollingManager::IsKeyboardEvent()
    {
        return gameEvent.type == sf::Event::KeyPressed;
    }

    bool EventPollingManager::PressedEscapeKey()
    {
        return gameEvent.key.code == sf::Keyboard::Escape;
    }

    bool EventPollingManager::PressedLeftMouseButton()
    {
        return leftMouseButtonState == MouseButtonState::PRESSED;
    }

    bool EventPollingManager::PressedRightMouseButton()
    {
        return rightMouseButtonState == MouseButtonState::PRESSED;
    }

    sf::Vector2i EventPollingManager::GetMousePosition(const sf::RenderWindow& window)
    {
        return sf::Mouse::getPosition(window);
    }
}
