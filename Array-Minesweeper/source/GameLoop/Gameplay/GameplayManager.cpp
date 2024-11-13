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
            std::cout << "Time Over\n";
            EndGame(GameResult::LOST);
        }

        board.Update(eventManager, window);

        if (eventManager.pressedLeftMouseButton() || eventManager.pressedRightMouseButton())
        {
            // Get mouse position relative to the window
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

            // Retrieve cell dimensions and offsets from a sample cell
            float cell_width = board.GetCellWidth();
            float cell_height = board.GetCellHeight();

            // Assuming all cells share the same offset within a board, retrieve it from a cell
            float cell_left_offset = board.GetSampleCellLeftOffset();
            float cell_top_offset = board.GetSampleCellTopOffset();

            // Calculate grid coordinates based on mouse click and cell dimensions
            int grid_x = (mouse_position.x - cell_left_offset) / cell_width;
            int grid_y = (mouse_position.y - cell_top_offset) / cell_height;

            // Check if grid coordinates are within bounds
            if (grid_x >= 0 && grid_x < board.GetNumberOfColumns() &&
                grid_y >= 0 && grid_y < board.GetNumberOfRows())
            {
                sf::Vector2i cell_position(grid_x, grid_y);
                std::cout << "Cell position: " << cell_position.x << ", " << cell_position.y << std::endl;

                // Process cell input
                board.ProcessCellInput(eventManager, cell_position);

                if (board.AreAllCellsOpen())
                {
                    EndGame(GameResult::WON);
                }
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
