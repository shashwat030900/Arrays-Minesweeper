#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreenManager/SplashScreenManager.h"
#include "../../header/UI/MainMenu/MainMenuManager.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Sound/SoundManager.h"
#include <iostream>

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
    GameWindowManager* windowManager;
    EventPollingManager* eventManager;
    SplashScreenManager* splashScreenManager;
    MainMenuManager* mainMenuManager;
    GameplayManager* gameplayManager;
    GameState currentState;
    Board* board;

    void Initialize();
    void HandleStates();
    void HandleMainMenuButtons();


public:
    GameLoop();
    ~GameLoop();
    void run();
};

#endif // GAMELOOP_H
