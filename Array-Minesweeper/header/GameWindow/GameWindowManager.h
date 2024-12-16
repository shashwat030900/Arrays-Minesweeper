#pragma once
#include <SFML/Graphics.hpp>

namespace GameWindow
{
	class GameWindowManager
	{
	private:
		const int frameRate = 60;

		const std::string gameWindowTitle = "Outscal Presents - Minesweeper";

		const int gameWindowWidth = 1920;
		const int gameWindowHeight = 1080;

		const sf::Color windowColor = sf::Color(200, 200, 0, 255);

		sf::VideoMode videoMode;
		sf::RenderWindow* gameWindow;

		void ConfigureVideoMode();
		void OnDestroy();

	public:
		GameWindowManager();
		~GameWindowManager();

		sf::RenderWindow* CreateGameWindow();

		void Initialize();
		void Update();
		void Render();
		bool IsGameWindowOpen();
		void SetFrameRate(int);
		sf::RenderWindow* GetGameWindow();
	};
}