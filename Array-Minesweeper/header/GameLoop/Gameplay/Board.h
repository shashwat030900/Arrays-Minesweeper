#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"

namespace Gameplay
{
    class GameplayManager;
    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class Board
    {
    private:
        GameplayManager *gameplay_manager;
        // Board Constants
        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;
        static const int minesCount = 9;

        // State and View Members
        BoardState boardState;
        Cell* board[numberOfRows][numberOfColumns];
        int flaggedCells;
        
        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;

        // Board Rendering
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;
        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        // Randomization
        std::default_random_engine randomEngine;
        std::random_device randomDevice;

        // Private helper methods
        void initialize(GameplayManager* gameplay_manager);
        void initializeVariables(GameplayManager* gameplay_manager);
        void initializeBoardImage();

        void createBoard();
        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;
        void deleteBoard();

        void openCell(sf::Vector2i cell_position);
        void flagCell(sf::Vector2i cell_position);
        
        void populateBoard(sf::Vector2i first_cell_position);
        void populateMines(sf::Vector2i first_cell_position);
        bool isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y);
        int countMinesAround(sf::Vector2i cell_position);
        void populateCells();
        
        void processCellType(sf::Vector2i cell_position);
        void processEmptyCell(sf::Vector2i cell_position);
        void processMineCell(sf::Vector2i cell_position);

        void openEmptyCells(sf::Vector2i cell_position);
        void OpenAllCells();
        void revealAllMines();

    public:
        Board(GameplayManager* gameplayManager);
        ~Board();

        // Game flow methods
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);

        void reset();
        void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);



        bool isValidCellPosition(sf::Vector2i cell_position);

        
        BoardState getBoardState() const;
        void setBoardState(BoardState state);
        int getMinesCount() const;
        
        bool areAllCellsOpen();
        void flagAllMines();
    };
}
