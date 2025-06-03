#include "../../header/GameLoop/GameLoop.h"
#include "../../header/Time/TimeManager.h"
#include <iostream>
#include "..\..\header\Sound\SoundManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/MainMenu/MainMenuManager.h"


GameState GameLoop::current_state = GameState::SPLASH_SCREEN;

GameLoop::GameLoop() { initialize(); }

void GameLoop::initialize()
{
    
    window_manager = new GameWindowManager();
    game_window = window_manager->getGameWindow();
    event_manager = new EventPollingManager(game_window);
    gameplay_manager = new Gameplay::GameplayManager();
    main_menu_manager = new MainMenuManager(game_window);

    splash_screen_manager = new SplashScreenManager(game_window);

    
    Sound::SoundManager::Initialize();
    Sound::SoundManager::PlayBackgroundMusic();

    Time::TimeManager::initialize();
}

GameLoop::~GameLoop()
{
    delete window_manager;
    delete event_manager;
    delete splash_screen_manager;
    delete  gameplay_manager;
    delete main_menu_manager;
}

void GameLoop::update()
{
    Time::TimeManager::update();
    event_manager->update();
    window_manager->update();
    
    switch (current_state)
    {
    case GameState::SPLASH_SCREEN:
        splash_screen_manager->update();
        break;
    case GameState::MAIN_MENU:
        main_menu_manager->update(*event_manager);
        break;
    case GameState::GAMEPLAY:
        gameplay_manager->update(*event_manager, *game_window);
        break;
    case GameState::EXIT:
        game_window->close();
        break;
    }

}

void GameLoop::render()
{
    game_window->clear();
    window_manager->render(); 
    gameplay_manager->update(*event_manager, *game_window);

    switch (current_state)
    {
    case GameState::SPLASH_SCREEN:
        splash_screen_manager->render();
        break;
    case GameState::MAIN_MENU:
        main_menu_manager->render();
        break;
        
    case GameState::GAMEPLAY:
        
        gameplay_manager->render(*game_window); 

        break;
    }

    game_window->display();
}

void GameLoop::run()
{
    while (window_manager->isGameWindowOpen())
    {
        event_manager->processEvents();
        update();
        render();
    }
}

void GameLoop::setGameState(GameState state_to_set) { 
    
    GameLoop::current_state = state_to_set; 
}