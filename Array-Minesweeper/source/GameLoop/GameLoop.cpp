#include "../../header/GameLoop/GameLoop.h"
#include <iostream>

GameLoop::GameLoop() {
    Initialize();
}

void GameLoop::Initialize() {
    windowManager = new GameWindow::GameWindowManager();
    windowManager->Initialize();
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
        splashScreenManager->Show();
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
    if (mainMenuManager->IsPlayButtonPressed()) {
        mainMenuManager->ResetButtonStates();
        gameplayManager->Initialize();
        currentState = GameState::GAMEPLAY;
    }
    else if (mainMenuManager->IsQuitButtonPressed()) {
        mainMenuManager->ResetButtonStates();
        currentState = GameState::EXIT;
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
