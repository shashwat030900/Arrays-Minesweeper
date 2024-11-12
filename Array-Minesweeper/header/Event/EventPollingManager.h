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
		sf::Event game_event;
		sf::RenderWindow* game_window;


		MouseButtonState left_mouse_button_state;
		MouseButtonState right_mouse_button_state;

		bool isGameWindowOpen();
		bool gameWindowWasClosed();
		bool hasQuitGame();
		bool isKeyboardEvent();
		void updateButtonsState(MouseButtonState& button_state);

	public:
		EventPollingManager(sf::RenderWindow* window);
		~EventPollingManager();

		void initialize();
		void update();
		void processEvents();

		bool pressedEscapeKey();
		bool pressedLeftMouseButton();
		bool pressedRightMouseButton();
	};
}