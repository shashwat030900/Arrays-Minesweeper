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
        createBoard();
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

        //create cells for the cell[][] array
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
