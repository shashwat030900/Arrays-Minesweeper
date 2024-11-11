#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include "../../header/UI/MainMenu/MainMenuManager.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"

enum class GameState {
    SPLASH_SCREEN,
    MAIN_MENU,
    GAMEPLAY,
    EXIT
};

class GameLoop {
private:
    GameWindow::GameWindowManager* windowManager;
    Event::EventPollingManager* eventManager;
    SplashScreenManager* splashScreenManager;
    MainMenuManager* mainMenuManager;
    GameplayManager* gameplayManager;
    GameState currentState;

    void handleState();

public:
    GameLoop();
    ~GameLoop();
    void run();
};

#endif // GAMELOOP_H
