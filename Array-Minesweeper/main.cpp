#include "header/GameWindow/GameWindowManager.h"
#include "header/Event/EventPollingManager.h"

int main()
{
    using namespace GameWindow;
    using namespace Event;

    GameWindowManager* game_window = new GameWindowManager();
    game_window->initialize();
    EventPollingManager event_manager(game_window->getGameWindow());


    while (game_window->isGameWindowOpen()) {
        event_manager.processEvents();
        game_window->getGameWindow()->clear();
        game_window->getGameWindow()->display();
    }


    delete game_window;

    return 0;
}