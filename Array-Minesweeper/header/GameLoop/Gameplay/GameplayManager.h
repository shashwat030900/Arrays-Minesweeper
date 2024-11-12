#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
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
        const float max_level_duration = 301.0f;
        const float game_over_time = 11.0f;

        Board board;
        Time::TimeManager time_manager;
        float remaining_time;
        GameResult game_result;

        void UpdateRemainingTime();
        bool IsTimeOver();
        void BeginGameOverTimer();

        void GameWon();
        void GameLost();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void Initialize(sf::RenderWindow& window);
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);

        void Restart();
        void EndGame(GameResult result);

        int GetMinesCount() const;
        float GetRemainingTime() const;
    };
}
