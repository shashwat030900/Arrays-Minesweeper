#include <iostream>
#include "../../header/UI/GameplayUI.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include "../../header/Event/EventPollingManager.h"
#include <SFML/Graphics.hpp>

namespace UI {

	GameplayUI::GameplayUI(GameplayManager* gameplay_manager) {

		initialize(gameplay_manager);
	}

	void GameplayUI::initialize(GameplayManager* gameplay_manager) {

		this->gameplay_manager = gameplay_manager;
		loadFonts();
		initializeTexts();
		initializeButton();
		registerButtonCallback();
	}

	void GameplayUI::loadFonts() {

		if (!bubbleBobbleFont.loadFromFile("assets/fonts/bubbleBobble.ttf"))
			std::cerr << "Error loading bubbleBobble font! " << std::endl;

		if (!dsDigibFont.loadFromFile("assets/fonts/DS_DIGIB.ttf"))
			std::cerr << "Error loading DS_DIGIB font! ";

	}

	void GameplayUI::initializeTexts() {

		mineText.setFont(dsDigibFont);
		mineText.setCharacterSize(fontSize);
		mineText.setFillColor(textColor);
		mineText.setPosition(mineTextLeftOffset, mineTextTopOffset);
		mineText.setString("000");

		timeText.setFont(dsDigibFont);
		timeText.setPosition(timeTextLesftOffset, timeTextTopOffset);
		timeText.setFillColor(textColor);
		timeText.setCharacterSize(fontSize);
		timeText.setString("000");

	}

	void GameplayUI::update(int remaining_mines, int remaining_time,
		EventPollingManager& eventManager, sf::RenderWindow& window) {
		mineText.setString(std::to_string(remaining_mines));
		timeText.setString(std::to_string(remaining_time));
		
		restartButton->handelButtonInteractions(eventManager, window);
	}

	void GameplayUI::render(sf::RenderWindow& window) {

		window.draw(mineText);
		window.draw(timeText);
		restartButton->render(window);
	}

	void GameplayUI::initializeButton() {

		restartButton = new Button(restartButtonTexturePath, sf::Vector2f(restartButtonLeftOffset, restartButtonTopOffset),buttonWidth, buttonHeight);


	}
	void GameplayUI::registerButtonCallback() {
		restartButton->registerCallbackFunction([this](UIElements::MouseButtonType buttonType) {
			RestartButtonCallback(buttonType); 
			});
	}

	void GameplayUI::RestartButtonCallback(MouseButtonType mouse_button_type) {
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			gameplay_manager->restartGame(); 
		}
	}

}