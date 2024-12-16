#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"
#include "../../header/Sound/SoundManager.h"
#include <SFML/Graphics.hpp>


using namespace UI;
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
        const float maxLevelDuration = 150.0f;
        const float gameOverTime = 11.0f;
        float remainingTime;

        const float backgroundAlpha = 85.f;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        std::string backgroundTexturePath = "assets/textures/minesweeper_bg.png";

        Board *board;
        GameResult gameResult = GameResult::NONE;
        GameplayUI gameplayUI;

        void UpdateRemainingTime();
        void ProcessTimeOver();
        void HandleGameplay(Event::EventPollingManager& eventManager, sf::RenderWindow& window);

        void GameWon();
        void GameLost();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void Initialize();
        void InitializeBackgroundImage();

        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);

        void CheckGameWin();
        void CheckRestart();
        void ProcessGameResult();

        int GetMinesCount() const;
        float GetRemainingTime() const;

        GameResult GetGameResult();
        void SetGameResult(GameResult gameResult);
    };
}
