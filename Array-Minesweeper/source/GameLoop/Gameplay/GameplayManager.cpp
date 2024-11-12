#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    GameplayManager::GameplayManager()
        : remaining_time(max_level_duration), game_result(GameResult::NONE)
    {
    }

    void GameplayManager::Initialize(sf::RenderWindow& window)
    {
        board.Initialize(window);
        time_manager.Initialize();
        remaining_time = max_level_duration;
        game_result = GameResult::NONE;
    }

    void GameplayManager::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        time_manager.Update();
        UpdateRemainingTime();

        if (IsTimeOver())
        {
            EndGame(GameResult::LOST);
        }

        board.Update(eventManager, window);

        if (eventManager.pressedLeftMouseButton() || eventManager.pressedRightMouseButton())
        {
            sf::Vector2i cell_position; // Get actual cell position from mouse click
            board.ProcessCellInput(eventManager, cell_position);

            if (board.AreAllCellsOpen())
            {
                EndGame(GameResult::WON);
            }
        }
    }

    void GameplayManager::Render(sf::RenderWindow& window)
    {
        board.Render(window);
    }

    void GameplayManager::Restart()
    {
        game_result = GameResult::NONE;
        board.Reset();
        time_manager.Initialize();
        remaining_time = max_level_duration;
    }

    void GameplayManager::EndGame(GameResult result)
    {
        switch (result)
        {
        case GameResult::WON:
            GameWon();
            break;
        case GameResult::LOST:
            GameLost();
            break;
        default:
            break;
        }
    }

    void GameplayManager::GameWon()
    {
        game_result = GameResult::WON;
        board.FlagAllMines();
        board.SetBoardState(BoardState::COMPLETED);
        std::cout << "Congratulations! You won the game!" << std::endl;
    }

    void GameplayManager::GameLost()
    {
        if (game_result == GameResult::NONE)
        {
            game_result = GameResult::LOST;
            BeginGameOverTimer();
            board.ShowBoard();
            board.SetBoardState(BoardState::COMPLETED);
        }
    }

    void GameplayManager::BeginGameOverTimer()
    {
        remaining_time = game_over_time;
    }

    void GameplayManager::UpdateRemainingTime()
    {
        if (game_result == GameResult::WON)
            return;

        remaining_time -= time_manager.GetDeltaTime();
        if (remaining_time < 0)
        {
            remaining_time = 0;
        }
    }

    bool GameplayManager::IsTimeOver()
    {
        return remaining_time <= 1.0f;
    }

    int GameplayManager::GetMinesCount() const
    {
        return board.GetMinesCount();
    }

    float GameplayManager::GetRemainingTime() const
    {
        return remaining_time;
    }
}
