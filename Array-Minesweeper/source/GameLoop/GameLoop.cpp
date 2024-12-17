#include "../../header/GameLoop/GameLoop.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

GameLoop::GameLoop() { initialize(); }

void GameLoop::initialize()
{
    // Create Managers:
    window_manager = new GameWindowManager();
    game_window = window_manager->GetGameWindow();
    event_manager = new EventPollingManager(game_window);

    splash_screen_manager = new SplashScreenManager(game_window);
    main_menu_manager = new MainMenuManager(game_window);
    gameplay_manager = new GameplayManager();

    // Initialize Game State:
    current_state = GameState::SPLASH_SCREEN;

    // Initialize Sounds:
    Sound::SoundManager::Initialize();
    Sound::SoundManager::PlayBackgroundMusic();
}

GameLoop::~GameLoop()
{
    delete window_manager;
    delete event_manager;
    delete splash_screen_manager;
    delete main_menu_manager;
    delete gameplay_manager;
}

void GameLoop::update()
{
    event_manager->Update();
    window_manager->Update();

    switch (current_state)
    {
    case GameState::SPLASH_SCREEN:
        splash_screen_manager->Update();
        break;
    case GameState::MAIN_MENU:
        main_menu_manager->Update(event_manager);
        break;
    case GameState::GAMEPLAY:
        gameplay_manager->Update(event_manager, game_window);
        break;
    case GameState::EXIT:
        game_window->close();
        break;
    }
    
}

void GameLoop::render()
{
    game_window->clear();
    window_manager->Render();

    switch (current_state)
    {
    case GameState::SPLASH_SCREEN:
        splash_screen_manager->Render();
        break;
    case GameState::MAIN_MENU:
        main_menu_manager->Render();
        break;
    case GameState::GAMEPLAY:
        gameplay_manager->Render(game_window);
        break;
    }
    
    game_window->display();
}

void GameLoop::run()
{
    while (window_manager->IsGameWindowOpen())
    {
        event_manager->ProcessEvents();
        update();
        render();
    }
}
