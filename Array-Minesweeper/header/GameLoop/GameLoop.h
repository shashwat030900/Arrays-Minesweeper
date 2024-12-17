#pragma once
#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include "../../header/UI/MainMenu/MainMenuManager.h"
#include "../../header/GameLoop/Gameplay/Board.h"

using namespace GameWindow;
using namespace Event;
using namespace Gameplay;
using namespace UI;

enum class GameState {
    SPLASH_SCREEN,
    MAIN_MENU,
    GAMEPLAY,
    EXIT
};

class GameLoop {
private:
    GameWindowManager* window_manager;
    EventPollingManager* event_manager;

    sf::RenderWindow* game_window;
    SplashScreenManager* splash_screen_manager;
    MainMenuManager* main_menu_manager;
    GameplayManager* gameplay_manager;

    GameState current_state;
    
    void initialize();
    void update();
    void render();

public:
    GameLoop();
    ~GameLoop();
    
    void run();
    
};