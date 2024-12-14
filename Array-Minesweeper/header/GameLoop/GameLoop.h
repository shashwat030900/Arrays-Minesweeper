#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include "../../header/Sound/SoundManager.h"
#include <iostream>

using namespace GameWindow;
using namespace Event;
using namespace UI;

enum class GameState {
    SPLASH_SCREEN,
    MAIN_MENU,
    GAMEPLAY,
    EXIT
};

class GameLoop {
private:
    GameWindowManager* windowManager;
    EventPollingManager* eventManager;
    SplashScreenManager* splashScreenManager;
    GameState currentState;

    void Initialize();
    void HandleStates();


public:
    GameLoop();
    ~GameLoop();
    void run();
};

#endif // GAMELOOP_H
