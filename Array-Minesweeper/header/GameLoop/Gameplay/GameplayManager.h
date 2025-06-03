#pragma once

#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/UI/GameplayUI.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/Sound/SoundManager.h"

#include <SFML/Graphics.hpp>

namespace Gameplay {

    enum class GameResult {
        NONE,
        WON,
        LOST
    };

    class GameplayManager {
    public:
        GameplayManager();

        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
        void restartGame();
        int getMinesCount() const;
        void setGameResult(GameResult gameResult);
        bool hasGameEnded();

    private:
        void initialize();
        void initializeVariables();
        void initializeBackgroundImage();

        void handleGameplay(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void checkGameWin();
        void processTimeOver();
        void processGameResult();
        void gameWon();
        void gameLost();
        void updateRemainingTime();

        Board* board = nullptr;
        UI::GameplayUI* gameplay_ui = nullptr;

        sf::Texture background_texture;
        sf::Sprite background_sprite;
        const std::string background_texture_path = "assets/textures/minesweeper_bg.png";
        const int background_alpha = 180;

        GameResult game_result = GameResult::NONE;
        float remaining_time = 0.0f;
        const float max_level_duration = 120.0f;
    };
}
