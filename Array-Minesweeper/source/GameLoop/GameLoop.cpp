#include "../../header/GameLoop/GameLoop.h"
#include <iostream>

GameLoop::GameLoop() {
    Initialize();
}

void GameLoop::Initialize() {
    windowManager = new GameWindow::GameWindowManager();
    eventManager = new Event::EventPollingManager(windowManager->GetGameWindow());
    splashScreenManager = new SplashScreenManager(windowManager->GetGameWindow());
    mainMenuManager = new MainMenuManager(windowManager->GetGameWindow());
    gameplayManager = new GameplayManager();

    currentState = GameState::SPLASH_SCREEN;

    Sound::SoundManager::Initialize();
    Sound::SoundManager::PlayBackgroundMusic();
}

GameLoop::~GameLoop() {
    delete windowManager;
    delete eventManager;
    delete splashScreenManager;
    delete mainMenuManager;
    delete gameplayManager;
}

void GameLoop::HandleStates() {
    switch (currentState) {
    case GameState::SPLASH_SCREEN:
        splashScreenManager->Render();
        currentState = GameState::MAIN_MENU;
        break;

    case GameState::MAIN_MENU:
        eventManager->Update();
        HandleMainMenuButtons();
        mainMenuManager->Update(*eventManager);
        mainMenuManager->Render();
        break;

    case GameState::GAMEPLAY:
        eventManager->Update();
        gameplayManager->Update(*eventManager, *windowManager->GetGameWindow());
        gameplayManager->Render(*windowManager->GetGameWindow());
        break;

    case GameState::EXIT:
        windowManager->GetGameWindow()->close();
        break;
    }
}

void GameLoop::HandleMainMenuButtons() {
    if (mainMenuManager->GetPlayButtonState() == ButtonState::PRESSED) {
        mainMenuManager->ResetButtonStates();
        currentState = GameState::GAMEPLAY;
        mainMenuManager->ResetButtonStates();
    }
    else if (mainMenuManager->GetQuitButtonState() == ButtonState::PRESSED) {
        mainMenuManager->ResetButtonStates();
        currentState = GameState::EXIT;
        mainMenuManager->ResetButtonStates();
    }
}

void GameLoop::run() {
    while (windowManager->IsGameWindowOpen()) {
        eventManager->ProcessEvents();
        windowManager->GetGameWindow()->clear();
        HandleStates();
        windowManager->GetGameWindow()->display();
    }
}
