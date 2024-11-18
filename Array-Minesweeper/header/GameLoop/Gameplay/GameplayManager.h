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
        const float maxLevelDuration = 201.0f;
        const float gameOverTime = 11.0f;
        float remainingTime;

        Board board;
        GameResult gameResult = GameResult::NONE;
        GameplayUI gameplayUI;

        void UpdateRemainingTime();
        bool IsTimeOver();

        void GameWon();
        void GameLost();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void Initialize();
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);

        void ProcessGameOver();
        void ProcessMouseInput(Event::EventPollingManager& eventManager, sf::RenderWindow& window);

        void CheckRestart();
        void EndGame(GameResult result);

        int GetMinesCount() const;
        float GetRemainingTime() const;
    };
}
