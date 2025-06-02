#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{

    enum class GameResult
    {
        NONE,
        WON,
        LOST
    };

    class GameplayManager
    {
    private:
        const float background_alpha = 85.f;
        sf::Texture background_texture;
        sf::Sprite background_sprite;
        std::string background_texture_path = "assets/textures/minesweeper_bg.png";

        Board* board;


        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();

        GameResult game_result;
        bool hasGameEnded();

    public:
        GameplayManager();
        ~GameplayManager() = default;
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);

        void setGameResult(GameResult gameResult);
    };
}