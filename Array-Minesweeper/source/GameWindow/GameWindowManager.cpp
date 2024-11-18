#include "../../header/GameWindow/GameWindowManager.h"

namespace GameWindow
{
	GameWindowManager::GameWindowManager()
	{
		gameWindow = nullptr;
	}

	GameWindowManager::~GameWindowManager()
	{
		OnDestroy();
	}

	void GameWindowManager::Initialize()
	{
		gameWindow = CreateGameWindow();
		SetFrameRate(frameRate);
	}

	sf::RenderWindow* GameWindowManager::CreateGameWindow()
	{
		ConfigureVideoMode();
		return new sf::RenderWindow(videoMode, gameWindowTitle, sf::Style::Fullscreen);
	}

	void GameWindowManager::ConfigureVideoMode()
	{
		videoMode = *(new sf::VideoMode(gameWindowWidth, gameWindowHeight, sf::VideoMode::getDesktopMode().bitsPerPixel));
	}

	void GameWindowManager::OnDestroy()
	{
		delete(gameWindow);
	}

	void GameWindowManager::SetFrameRate(int frame_rate_to_set)
	{
		gameWindow->setFramerateLimit(frame_rate_to_set);
	}

	void GameWindowManager::Update() { }

	void GameWindowManager::Render() { }

	bool GameWindowManager::IsGameWindowOpen()
	{
		return gameWindow->isOpen();
	}

	sf::RenderWindow* GameWindowManager::GetGameWindow()
	{
		return gameWindow;
	}
}