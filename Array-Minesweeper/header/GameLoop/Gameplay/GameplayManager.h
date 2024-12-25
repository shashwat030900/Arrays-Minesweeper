#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    using namespace UI;

    enum class GameResult
    {
        NONE,
        WON,
        LOST
    };

    class GameplayManager
    {
    private:
        const float max_level_duration = 150.0f;
        const float game_over_time = 11.0f;
        float remaining_time;

        const float background_alpha = 85.f;
        sf::Texture background_texture;
        sf::Sprite background_sprite;
        std::string background_texture_path = "assets/textures/minesweeper_bg.png";

        Board* board;
        GameResult game_result;
        GameplayUI* gameplay_ui;

        void updateRemainingTime();
        void processTimeOver();

        void handleGameplay(EventPollingManager* eventManager, sf::RenderWindow* window);
        bool hasGameEnded();
        void gameWon();
        void gameLost();

        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();
        
        int getMinesCount() const;
    
    public:
        GameplayManager();
        ~GameplayManager() = default;

        void update(EventPollingManager* eventManager, sf::RenderWindow* window);
        void render(sf::RenderWindow& window);

        void checkGameWin();
        void restartGame();
        void processGameResult();

        void setGameResult(GameResult gameResult);
    };
}
