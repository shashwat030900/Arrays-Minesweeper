#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameLoop/Gameplay/Cell.h" 
#include "../../header/Sound/SoundManager.h"

namespace Gameplay
{

    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class GameplayManager;

    class Board
    {
    private:
        
        BoardState boardState;
        GameplayManager* gameplay_manager ;
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        void initializeBoardImage();
        void initialize(GameplayManager* gameplay_manager);
        void createBoard();

        static const int numberOfRows = 9;
        static const int numberOfColumn = 9;
        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;
        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;
        
        Cell* cell[numberOfRows][numberOfColumn];

        std::default_random_engine randomEngine;
        std::random_device rancdomDevice;

        static const int minesCount = 8;

        void populateBoard(sf::Vector2i cell_position);
        void initializeVariables(GameplayManager* gameplay_manager);
        void populateMines(sf::Vector2i firrst_cell_position);

        int countMinesAround(sf::Vector2i cell_position);
        void populateCells();
        bool isValidCellPosition(sf::Vector2i cell_position);
        void openCell(sf::Vector2i cell_position);

        int flaggedCells;
        void toggleFlag(sf::Vector2i cell_position);

        void processCellType(sf::Vector2i cell_position);
        void processEmptyCell(sf::Vector2i cell_position);

        void processMineCell(sf::Vector2i cell_position);
        
        bool isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y);



    public:

        Board(GameplayManager* gameplay_maager);
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
        void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);
        void revealAllMines();

        BoardState getBoardState() const;
        void setBoardState(BoardState state);

    };
}