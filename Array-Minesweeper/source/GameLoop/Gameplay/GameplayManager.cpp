#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    GameplayManager::GameplayManager()
    {
    }

    void GameplayManager::Initialize()
    {
        board.Initialize();
        Time::TimeManager::Initialize();
        gameplayUI.Initialize();
        remainingTime = maxLevelDuration;
        gameResult = GameResult::NONE;
    }

    void GameplayManager::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        Time::TimeManager::Update();
        UpdateRemainingTime();
        board.Update(eventManager, window);
        ProcessGameOver();

        if (gameResult == GameResult::NONE) {
            gameplayUI.Update(GetMinesCount(), static_cast<int>(remainingTime), eventManager, window);
        }
        
        ProcessMouseInput(eventManager, window);
        CheckRestart();    
    }


    void GameplayManager::Render(sf::RenderWindow& window)
    {
        board.Render(window);
        gameplayUI.Render(window);
    }

    void GameplayManager::ProcessMouseInput(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        sf::Vector2i mouse_position = eventManager.GetMousePosition(window);
        sf::Vector2i cell_position = board.GetCellFromMousePosition(mouse_position);

        if (board.IsValidCellPosition(cell_position))
        {
            board.ProcessCellInput(eventManager, cell_position);
        }
    }

    void GameplayManager::ProcessGameOver() {
        if (board.AreAllCellsOpen())
        {
            EndGame(GameResult::WON);
        }
        if (IsTimeOver())
        {
            EndGame(GameResult::LOST);
        }
    }

    void GameplayManager::CheckRestart()
    {
        if (gameplayUI.IsRestartButtonPressed()) {
            gameResult = GameResult::NONE;
            board.Reset();
            Time::TimeManager::Initialize();
            remainingTime = maxLevelDuration;
        }
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
        gameResult = GameResult::WON;
        board.FlagAllMines();
        Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);
        board.SetBoardState(BoardState::COMPLETED);
    }

    void GameplayManager::GameLost()
    {
        gameResult = GameResult::LOST;
        board.ShowBoard();
        Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
        board.SetBoardState(BoardState::COMPLETED);
    }

    void GameplayManager::UpdateRemainingTime()
    {
        if (gameResult == GameResult::WON || gameResult == GameResult::LOST || board.GetBoardState() == BoardState::COMPLETED)
            return;

        remainingTime -= Time::TimeManager::GetDeltaTime();
        if (remainingTime < 0)
        {
            remainingTime = 0;
        }
    }

    bool GameplayManager::IsTimeOver()
    {
        return remainingTime <= 1.0f;
    }

    int GameplayManager::GetMinesCount() const
    {
        return board.GetMinesCount();
    }

    float GameplayManager::GetRemainingTime() const
    {
        return remainingTime;
    }
}
