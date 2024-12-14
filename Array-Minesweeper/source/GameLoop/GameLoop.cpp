#include "../../header/GameLoop/GameLoop.h"
#include <iostream>

GameLoop::GameLoop() {
    Initialize();
}

void GameLoop::Initialize() {
    windowManager = new GameWindow::GameWindowManager();
    eventManager = new Event::EventPollingManager(windowManager->GetGameWindow());
    splashScreenManager = new SplashScreenManager(windowManager->GetGameWindow());

    currentState = GameState::SPLASH_SCREEN;

    Sound::SoundManager::Initialize();
    Sound::SoundManager::PlayBackgroundMusic();
}

GameLoop::~GameLoop() {
    delete windowManager;
    delete eventManager;
    delete splashScreenManager;
}

void GameLoop::HandleStates() {
    switch (currentState) {
    case GameState::SPLASH_SCREEN:
        splashScreenManager->Render();
        currentState = GameState::MAIN_MENU;
        break;

    case GameState::MAIN_MENU:
        break;

    case GameState::GAMEPLAY:
        eventManager->Update();
        break;

    case GameState::EXIT:
        windowManager->GetGameWindow()->close();
        break;
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
