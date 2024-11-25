#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    GameplayManager::GameplayManager()
    {
        Initialize();
    }

    void GameplayManager::Initialize()
    {
        InitializeBackgroundImage();
        board = new Board(this);
        Time::TimeManager::Initialize();
        remainingTime = maxLevelDuration;
        gameResult = GameResult::NONE;
    }

    void GameplayManager::InitializeBackgroundImage()
    {
        if (!backgroundTexture.loadFromFile("assets/textures/minesweeper_bg.png"))
        {
            std::cerr << "Failed to load background texture!" << std::endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setColor(sf::Color(255, 255, 255, backgroundAlpha));
    }

    void GameplayManager::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        Time::TimeManager::Update();
        if (gameResult == GameResult::NONE && board->GetBoardState() != BoardState::COMPLETED)
        {
            UpdateRemainingTime();
            board->Update(eventManager, window);
            /*ProcessMouseInput(eventManager, window);*/
            HandleGameWin();
        }
        gameplayUI.Update(GetMinesCount(), static_cast<int>(remainingTime), eventManager, window);
        ProcessGameResult();
        CheckRestart();
    }


    void GameplayManager::Render(sf::RenderWindow& window)
    {
        window.draw(backgroundSprite);
        board->Render(window);
        gameplayUI.Render(window);
    }

    //void GameplayManager::ProcessMouseInput(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    //{
    //    sf::Vector2i mouse_position = eventManager.GetMousePosition(window);
    //    sf::Vector2i cell_position = board->GetCellFromMousePosition(mouse_position);

    //    if (board->IsValidCellPosition(cell_position))
    //    {
    //        board->ProcessCellInput(eventManager, cell_position);
    //    }
    //}

    void GameplayManager::HandleGameWin() {
        
        if (board->AreAllCellsOpen()) {
                gameResult = GameResult::WON;;
                board->SetBoardState(BoardState::COMPLETED);
        }
    }



    void GameplayManager::CheckRestart()
    {
        if (gameplayUI.OnRestartButtonClicked()) {
            gameResult = GameResult::NONE;
            board->Reset();
            Time::TimeManager::Initialize();
            remainingTime = maxLevelDuration;
        }
    }

    void GameplayManager::ProcessGameResult()
    {
        switch (gameResult)
        {
        case GameResult::WON:
            std::cout << "WON" << std::endl;
            GameWon();
            break;
        case GameResult::LOST:
            std::cout << "LOST" << std::endl;
            GameLost();
            break;
        default:
            break;
        }
        gameResult = GameResult::NONE;
    }


    void GameplayManager::GameWon()
    {
        Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);
        board->FlagAllMines();
        board->SetBoardState(BoardState::COMPLETED);
    }

    void GameplayManager::GameLost()
    {
        Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
        board->SetBoardState(BoardState::COMPLETED);
    }

    void GameplayManager::UpdateRemainingTime()
    {
        remainingTime -= Time::TimeManager::GetDeltaTime();
        ProcessTimeOver();   
    }

    void GameplayManager::ProcessTimeOver()
    {
        if (remainingTime <= 0)
        {
            remainingTime = 0;
            gameResult = GameResult::LOST;
            board->SetBoardState(BoardState::COMPLETED);
        }
    }

    int GameplayManager::GetMinesCount() const
    {
        return board->GetMinesCount();
    }

    float GameplayManager::GetRemainingTime() const
    {
        return remainingTime;
    }
    GameResult GameplayManager::GetGameResult()
    {
        return gameResult;
    }
    void GameplayManager::SetGameResult(GameResult gameResult)
    {
        this->gameResult = gameResult;
    }
}
