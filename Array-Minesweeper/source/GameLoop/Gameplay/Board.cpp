#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    Board::Board(GameplayManager* gameplayManager) { initialize(gameplayManager); }

    Board::~Board() { deleteBoard(); }

    void Board::initialize(GameplayManager* gameplayManager)
    {
        initializeVariables(gameplayManager);
        initializeBoardImage();
        createBoard();
        reset();
    }

    void Board::initializeVariables(GameplayManager* gameplay_manager)
    {
        this->gameplay_manager = gameplay_manager;
        boardState = BoardState::FIRST_CELL;
        flaggedCells = 0;
    }

    void Board::initializeBoardImage()
    {
        if (!boardTexture.loadFromFile(boardTexturePath))
        {
            std::cerr << "Failed to load board texture!" << std::endl;
            return;
        }
        
        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(boardPosition, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x, boardHeight / boardTexture.getSize().y);
    }

    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();
        
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                board[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col), this);
    }
    
    void Board::reset()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                board[row][col]->reset();

        flaggedCells = 0;
        boardState = BoardState::FIRST_CELL;
    }
    
    void Board::deleteBoard()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                delete board[row][col];
    }

    void Board::update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        if (boardState == BoardState::COMPLETED)
            return;

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                board[row][col]->update(eventManager, window);
    }

    void Board::render(sf::RenderWindow& window)
    {
        window.draw(boardSprite);
        
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                board[row][col]->render(window);
    }

    void Board::onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type)
    {
        if (boardState == BoardState::COMPLETED)
            return;

        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
        {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            openCell(cell_position);
        }
        else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
        {
            Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);
            flagCell(cell_position);
        }
    }

    void Board::openCell(sf::Vector2i cell_position)
    {
        if (!board[cell_position.x][cell_position.y]->canOpenCell())
            return;
        
        // Handle first click logic
        if (boardState == BoardState::FIRST_CELL)
        {
            populateBoard(cell_position);
            boardState = BoardState::PLAYING;
        }

        // Open the cell and process its type
        processCellType(cell_position);
        board[cell_position.x][cell_position.y]->open();
    }

    void Board::flagCell(sf::Vector2i cell_position)
    {
        board[cell_position.x][cell_position.y]->toggleFlag();
        flaggedCells += (board[cell_position.x][cell_position.y]->getCellState() == CellState::FLAGGED) ? 1 : -1;
    }

    void Board::populateBoard(sf::Vector2i first_cell_position)
    {
        populateMines(first_cell_position);
        populateCells();
    }

    void Board::populateMines(sf::Vector2i first_cell_position)
    {
        std::uniform_int_distribution<int> x_dist(0, numberOfColumns - 1);
        std::uniform_int_distribution<int> y_dist(0, numberOfRows - 1);

        int mines_placed = 0;
        while (mines_placed < minesCount)
        {
            int x = x_dist(randomEngine);
            int y = y_dist(randomEngine);

            if (isInvalidMinePosition(first_cell_position, first_cell_position.x, first_cell_position.y))
                continue;

            board[x][y]->setCellType(CellType::MINE);
            ++mines_placed;
        }
    }

    bool Board::isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y)
    {
        return (x == first_cell_position.x && y == first_cell_position.y) || board[x][y]->getCellType() == CellType::MINE;
    }

    void Board::populateCells()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                if (board[row][col]->getCellType() != CellType::MINE)
                {
                    int mines_around = countMinesAround(sf::Vector2i(row, col));
                    board[row][col]->setCellType(static_cast<CellType>(mines_around));
                }
    }

    int Board::countMinesAround(sf::Vector2i cell_position)
    {
        int mines_around = 0;

        for (int a = -1; a <= 1; ++a)
            for (int b = -1; b <= 1; ++b)
            {
                if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
                    continue;

                if (board[cell_position.x + a][cell_position.y + b]->getCellType() == CellType::MINE)
                    mines_around++;
            }

        return mines_around;
    }

    void Board::processCellType(sf::Vector2i cell_position)
    {
        switch (board[cell_position.x][cell_position.y]->getCellType())
        {
        case CellType::EMPTY:
            processEmptyCell(cell_position);
            break;
        case CellType::MINE:
            processMineCell(cell_position);
            break;
        default:
            break;
        }
    }

    void Board::processEmptyCell(sf::Vector2i cell_position)
    {
        CellState cell_state = board[cell_position.x][cell_position.y]->getCellState();

        switch (cell_state)
        {
        case::Gameplay::CellState::OPEN:
            return;
        case::Gameplay::CellState::FLAGGED:
            flaggedCells--;
        default:
            board[cell_position.x][cell_position.y]->open();
        }

        for (int a = -1; a <= 1; a++)
            for (int b = -1; b <= 1; b++)
            {
                sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);
                
                if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(next_cell_position)))
                    continue;
                
                openCell(next_cell_position);
            }

    }

    void Board::processMineCell(sf::Vector2i cell_position)
    {
        gameplay_manager->setGameResult(GameResult::LOST);
        boardState = BoardState::COMPLETED;
        revealAllMines();
    }

    void Board::revealAllMines()
    {
        for (int row = 0; row < numberOfRows; row++)
        {
            for (int col = 0; col < numberOfColumns; col++)
            {
                // Check if the cell contains a mine
                if (board[row][col]->getCellType() == CellType::MINE)
                {
                    // Open the mine cell
                    board[row][col]->setCellState(CellState::OPEN);
                }
            }
        }
    }

    // Check if all non-mine cells are open
    bool Board::areAllCellsOpen()
    {
        int total_cell_count = numberOfRows * numberOfColumns;
        int open_cell_count = 0;

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                if (board[row][col]->getCellState() == CellState::OPEN && board[row][col]->getCellType() != CellType::MINE)
                    open_cell_count++;
        
        return (total_cell_count - open_cell_count == minesCount);
    }

    void Board::flagAllMines()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                if (board[row][col]->getCellType() == CellType::MINE && board[row][col]->getCellState() != CellState::FLAGGED)
                    flagCell(sf::Vector2i(row, col));
    }
    
    bool Board::isValidCellPosition(sf::Vector2i cell_position)
    {
        return (cell_position.x >= 0 && cell_position.y >= 0 && cell_position.x < numberOfColumns && cell_position.y < numberOfRows);
    }

    BoardState Board::getBoardState() const { return boardState; }

    void Board::setBoardState(BoardState state) { boardState = state; }

    int Board::getMinesCount() const { return minesCount - flaggedCells; }

    float Board::getCellWidthInBoard() const { return (boardWidth - horizontalCellPadding) / static_cast<float>(numberOfColumns); }

    float Board::getCellHeightInBoard() const { return (boardHeight - verticalCellPadding) / static_cast<float>(numberOfRows); }
}
