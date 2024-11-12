#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameWindow/GameWindowManager.h"
#include <iostream>

namespace Event
{
    using namespace GameWindow;

    EventPollingManager::EventPollingManager(sf::RenderWindow* window)
        : game_window(window), left_mouse_button_state(MouseButtonState::RELEASED), right_mouse_button_state(MouseButtonState::RELEASED) {}

    EventPollingManager::~EventPollingManager() = default;

    void EventPollingManager::initialize(sf::RenderWindow* window)
    {
        game_window = window;
        left_mouse_button_state = MouseButtonState::RELEASED;
        right_mouse_button_state = MouseButtonState::RELEASED;
    }

    void EventPollingManager::update()
    {
        updateButtonsState(left_mouse_button_state, sf::Mouse::Left);
        updateButtonsState(right_mouse_button_state, sf::Mouse::Right);
    }

    void EventPollingManager::processEvents()
    {
        if (isGameWindowOpen())
        {
            while (game_window->pollEvent(game_event))
            {
                if (gameWindowWasClosed() || hasQuitGame())
                    game_window->close();
            }
        }
    }

    void EventPollingManager::updateButtonsState(MouseButtonState& button_state, sf::Mouse::Button button_type)
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

    bool EventPollingManager::isGameWindowOpen()
    {
        return game_window != nullptr;
    }

    bool EventPollingManager::gameWindowWasClosed()
    {
        return game_event.type == sf::Event::Closed;
    }

    bool EventPollingManager::hasQuitGame()
    {
        return (isKeyboardEvent() && pressedEscapeKey());
    }

    bool EventPollingManager::isKeyboardEvent()
    {
        return game_event.type == sf::Event::KeyPressed;
    }

    bool EventPollingManager::pressedEscapeKey()
    {
        return game_event.key.code == sf::Keyboard::Escape;
    }

    bool EventPollingManager::pressedLeftMouseButton()
    {
        return left_mouse_button_state == MouseButtonState::PRESSED;
    }

    bool EventPollingManager::pressedRightMouseButton()
    {
        return right_mouse_button_state == MouseButtonState::PRESSED;
    }
}
