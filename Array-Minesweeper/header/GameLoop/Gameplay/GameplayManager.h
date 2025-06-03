#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    using namespace UI;
    using namespace Time; 

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
        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();

        GameResult game_result;
        bool hasGameEnded();

        void updateRemainingTime();
        void processTimeOver();
        void handleGameplay(Event::EventPollingManager& eventmanager, sf::RenderWindow& window);

        void gameWon();
        void gameLost();

        int getMinesCount() const;

        GameplayUI* gameplay_ui;

    public:
        GameplayManager();
        ~GameplayManager() = default;
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);

        void setGameResult(GameResult gameResult);

        void checkGameWin();
        void processGameResult();
    };
}
