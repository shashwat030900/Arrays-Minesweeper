#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay {
	class GameplayManager;
}

namespace UI {

	using namespace Gameplay;
	using namespace UIElements;
	using namespace Event;

	class GameplayUI {

	private:

		sf::Font bubbleBobbleFont;
		sf::Font dsDigibFont;

		sf::Text mineText;
		sf::Text timeText;

		Button* restartButton = nullptr;
		bool restartButtonClicked = false;
		const std::string restartButtonTexturePath = "assets/textures/restart_button.png";
		const int fontSize = 110;

		const float mineTextTopOffset = 65.f;
		const float mineTextLeftOffset = 660.f;

		const float timeTextTopOffset = 65.f;
		const float timeTextLesftOffset = 1150.f;

		const float restartButtonTopOffset = 100.f;
		const float restartButtonLeftOffset = 920.f;

		const float buttonWidth = 80.f;
		const float buttonHeight = 80.f;
		const sf::Color textColor = sf::Color::Red;

		GameplayManager* gameplay_manager;

		void initialize(GameplayManager* gameplay_manager);
		void initializeTexts();
		void initializeButton();
		void loadFonts();

		void registerButtonCallback();
		void RestartButtonCallback(MouseButtonType mouse_button_type); 

	public:

		GameplayUI(GameplayManager* gameplay_manager);
		~GameplayUI() = default;

		void update(int remaining_mines, int remaining_time, EventPollingManager& eventManager, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
	};
}
