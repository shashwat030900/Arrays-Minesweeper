#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"
#include "../../header/Sound/SoundManager.h"
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
        float remaining_time;

        Board board;
        Time::TimeManager time_manager;
        GameResult game_result;
        GameplayUI ui;

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
