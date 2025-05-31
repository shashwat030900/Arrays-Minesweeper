#include <SFML/Graphics.hpp>
#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

using namespace Gameplay;


    Board::Board()
    {
        initialize();
    }

    void Board::initialize()
    {
        initializeBoardImage();
        initializeVariables();
        createBoard();
        populateBoard();

    }
    void Board::initializeBoardImage() {
        if (!boardTexture.loadFromFile(boardTexturePath)) {
            std::cerr << "Failed to load board texture!" << std::endl;
            return;
        }

        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(boardPosition, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x,
            boardHeight / boardTexture.getSize().y);
    }

    void Board::render(sf::RenderWindow& window)
    {
        window.draw(boardSprite);
        for (int row = 0; row < numberOfRows; ++row) {

            for(int col= 0; col<numberOfColumn; ++col)

            {
                cell[row][col]->render(window);
            }
        }
    }

    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();

       
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumn; ++col)
            {
                cell[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col));
            }
        }
    }

    
    float Board::getCellWidthInBoard()const {

        return(boardWidth - horizontalCellPadding) / numberOfColumn;

    }

    float Board::getCellHeightInBoard()const {

        return (boardHeight - verticalCellPadding) / numberOfRows;

    }
    void Board::initializeVariables() {

        randomEngine.seed(rancdomDevice());

    }
    void Board::populateMines() {

        std::uniform_int_distribution<int>x_dist(0, numberOfColumn - 1);
        std::uniform_int_distribution<int>y_dist(0, numberOfRows - 1);
        int mines_placed = 0;

        while (mines_placed < minesCount) {

            int x = x_dist(randomEngine);
            int y = y_dist(randomEngine);

            if (cell[x][y]->getCellType() != CellType::MINE) {

                cell[x][y]->setCellType(CellType::MINE);
                ++mines_placed;

            }
        }
    }
    void Board::populateBoard() {

        populateMines();

    }