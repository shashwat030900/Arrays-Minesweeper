


GameLoop::GameLoop() {
    windowManager = new GameWindow::GameWindowManager();
    windowManager->initialize();
    eventManager = new Event::EventPollingManager(windowManager->getGameWindow());
    splashScreenManager = new SplashScreenManager();
    mainMenuManager = new MainMenuManager();
    gameplayManager = new GameplayManager();
    currentState = GameState::SPLASH_SCREEN;
}

GameLoop::~GameLoop() {
    delete windowManager;
    delete eventManager;
    delete splashScreenManager;
    delete mainMenuManager;
    delete gameplayManager;
}

void GameLoop::handleState() {
    switch (currentState) {
    case GameState::SPLASH_SCREEN:
        splashScreenManager->show(windowManager->getGameWindow());
        currentState = GameState::MAIN_MENU;
        break;

    case GameState::MAIN_MENU:
        mainMenuManager->display(windowManager->getGameWindow());
        // Transition logic to gameplay or exit
        currentState = GameState::GAMEPLAY; // Example transition
        break;

    case GameState::GAMEPLAY:
        gameplayManager->startGame(windowManager->getGameWindow());
        // Logic to check if game should exit or go to main menu
        currentState = GameState::EXIT; // Example end state
        break;

    case GameState::EXIT:
        windowManager->getGameWindow()->close();
        break;
    }
}

void GameLoop::run() {
    while (windowManager->isGameWindowOpen()) {
        eventManager->processEvents();
        handleState();
        windowManager->getGameWindow()->clear();
        windowManager->getGameWindow()->display();
    }
}
