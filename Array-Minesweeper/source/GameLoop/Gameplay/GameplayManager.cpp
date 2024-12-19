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
        // Time::TimeManager::initialize();
        remainingTime = maxLevelDuration;
        gameResult = GameResult::NONE;
    }

    void GameplayManager::InitializeBackgroundImage()
    {
        if (!backgroundTexture.loadFromFile(backgroundTexturePath))
        {
            std::cerr << "Failed to load background texture!" << std::endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setColor(sf::Color(255, 255, 255, backgroundAlpha));
    }

    void GameplayManager::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        // Time::TimeManager::update();
        HandleGameplay(eventManager, window);
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

    void GameplayManager::CheckGameWin() {
        
        if (board->AreAllCellsOpen()) {
                gameResult = GameResult::WON;;
                board->SetBoardState(BoardState::COMPLETED);
        }
    }

    void GameplayManager::CheckRestart()
    {
        if (gameplayUI.GetRestartButtonState() == ButtonState::PRESSED) {
            gameResult = GameResult::NONE;
            gameplayUI.ResetButtons();
            board->Reset();
            Time::TimeManager::initialize();
            remainingTime = maxLevelDuration;
        }
    }

    void GameplayManager::ProcessGameResult()
    {
        switch (gameResult)
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
        Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);
        board->FlagAllMines();
        board->SetBoardState(BoardState::COMPLETED);
        gameResult = GameResult::NONE;
    }

    void GameplayManager::GameLost()
    {
        Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
        board->SetBoardState(BoardState::COMPLETED);
        gameResult = GameResult::NONE;
    }

    void GameplayManager::UpdateRemainingTime()
    {
        remainingTime -= Time::TimeManager::getDeltaTime();
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

    void GameplayManager::HandleGameplay(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        if (gameResult == GameResult::NONE && board->GetBoardState() != BoardState::COMPLETED)
        {
            UpdateRemainingTime();
            board->Update(eventManager, window);
            CheckGameWin();
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
