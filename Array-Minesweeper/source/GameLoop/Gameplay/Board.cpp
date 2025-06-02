#include <SFML/Graphics.hpp>
#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>
#include "../../header/Sound/SoundManager.h"

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
                cell[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col), this);
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
        populateCells();

    }
    int Board::countMinesAround(sf::Vector2i cell_position) {

        int mine_around = 0;

        for (int a = -1; a <= 1; ++a) {

            for (int b = -1; b <= 1; ++b) {
                if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
                    continue;

                if (cell[cell_position.x + a][cell_position.y + b]->getCellType() == CellType::MINE)
                    mine_around++;

            }
        }
        return mine_around;
    }

    bool Board::isValidCellPosition(sf::Vector2i cell_position) {

        return(cell_position.x >= 0 && cell_position.y >= 0 && cell_position.x < numberOfColumn && cell_position.y < numberOfRows);



    }
    void Board::populateCells() {

        for (int row = 0; row < numberOfRows; ++row) {

            for(int col = 0; col < numberOfColumn; ++col)
                if (cell[row][col]->getCellType() != CellType::MINE) {

                    int mmine_around = countMinesAround(sf::Vector2i(row, col));
                    cell[row][col]->setCellType(static_cast<CellType>(mmine_around));
                }

        }

    }
    void Board::update (Event::EventPollingManager& eventManager, sf::RenderWindow& window) {

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumn; ++col)
                cell[row][col]->update(eventManager, window);

    }
    void Board::onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type) {

        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {

            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            openCell(cell_position);
        }
        else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON) {

            Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);
            toggleFlag(cell_position);

        }
    }

    void Board::openCell(sf::Vector2i cell_postion) {
        if (!cell[cell_postion.x][cell_postion.y]->canOpenCell()) {
            return;
        }

        cell[cell_postion.x][cell_postion.y]->open();


    }
    void Board::toggleFlag(sf::Vector2i cell_position) {

        cell[cell_position.x][cell_position.y]->toggleFlag();
        flaggedCells += (cell[cell_position.x][cell_position.y]->getCellState() == CellState::FLAGGED) ? 1 : 1;

    }