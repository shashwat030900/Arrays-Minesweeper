#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    Board::Board(GameplayManager *gameplayManager)
        : boardState(BoardState::FIRST_CELL), flaggedCells(0), randomEngine(randomDevice())
    {
        this->gameplayManager = gameplayManager;
        Initialize();
    }

    Board::~Board()
    {
        DeleteBoard();
    }

    void Board::Initialize()
    {
        InitializeBoardImage();
        CreateBoard();
        reset();
    }

    void Board::InitializeBoardImage()
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

    void Board::CreateBoard()
    {
        float cell_width = GetCellWidthInBoard();
        float cell_height = GetCellHeightInBoard();
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col), this);
            }
        }
    }

    void Board::OnCellButtonClicked(sf::Vector2i cell_position, ButtonType buttonType) {

        if (boardState == BoardState::COMPLETED)
            return;

        if (buttonType == ButtonType::LEFT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            OpenCell(cell_position);
        }
        else if (buttonType == ButtonType::RIGHT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);
            FlagCell(cell_position);
        }
    }

    void Board::update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        if (boardState == BoardState::COMPLETED)
            return;

        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col]->Update(eventManager, window);
            }
        }
    }

    void Board::render(sf::RenderWindow& window)
    {
        window.draw(boardSprite);
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col]->Render(window);
            }
        }
    }

    void Board::PopulateBoard(sf::Vector2i first_cell_position)
    {
        PopulateMines(first_cell_position);
        PopulateCells();
    }

    void Board::PopulateMines(sf::Vector2i first_cell_position)
    {
        std::uniform_int_distribution<int> x_dist(0, numberOfColumns - 1);
        std::uniform_int_distribution<int> y_dist(0, numberOfRows - 1);

        int mines_placed = 0;
        while (mines_placed < minesCount)
        {
            int x = x_dist(randomEngine);
            int y = y_dist(randomEngine);

            if ((x == first_cell_position.x && y == first_cell_position.y) || board[x][y]->GetCellType() == CellType::MINE)
                continue;

            board[x][y]->SetCellType(CellType::MINE);
            ++mines_placed;
        }
    }

    void Board::PopulateCells()
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                if (board[row][col]->GetCellType() != CellType::MINE)
                {
                    int mines_around = CountMinesAround(sf::Vector2i(row, col));
                    board[row][col]->SetCellType(static_cast<CellType>(mines_around));
                }
            }
        }
    }

    int Board::CountMinesAround(sf::Vector2i cell_position)
    {
        int mines_around = 0;

        for (int a = -1; a <= 1; ++a)
        {
            for (int b = -1; b <= 1; ++b)
            {
                if ((a == 0 && b == 0) || !IsValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
                    continue;

                if (board[cell_position.x + a][cell_position.y + b]->GetCellType() == CellType::MINE)
                    mines_around++;
            }
        }

        return mines_around;
    }

    void Board::FlagCell(sf::Vector2i cell_position)
    {
        board[cell_position.x][cell_position.y]->ToggleFlag();
        flaggedCells += (board[cell_position.x][cell_position.y]->GetCellState() == CellState::FLAGGED) ? 1 : -1;
    }

    void Board::OpenCell(sf::Vector2i cell_position)
    {
        if (!board[cell_position.x][cell_position.y]->CanOpenCell()) {
            return;
        }
        
        // Handle first click logic
        if (boardState == BoardState::FIRST_CELL) {
            PopulateBoard(cell_position);
            boardState = BoardState::PLAYING;
        }

        // Open the cell and process its type
        ProcessCellType(cell_position);
        board[cell_position.x][cell_position.y]->Open();
    }

    void Board::DeleteBoard()
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                delete board[row][col];
            }
        }
    }

    // Check if all non-mine cells are open
    bool Board::areAllCellsOpen() {
        int total_cell_count = numberOfRows * numberOfColumns;
        int open_cell_count = 0;

        for (int row = 0; row < numberOfRows; ++row) {
            for (int col = 0; col < numberOfColumns; ++col) {
                if (board[row][col]->GetCellState() == CellState::OPEN && board[row][col]->GetCellType() != CellType::MINE) {
                    open_cell_count++;
                }
            }
        }

        // Check if all non-mine cells are open
        return (total_cell_count - open_cell_count == minesCount);
    }

    // Check if a given cell position is within the board boundaries
    bool Board::IsValidCellPosition(sf::Vector2i cell_position) {
        return (cell_position.x >= 0 && cell_position.y >= 0 &&
            cell_position.x < numberOfColumns && cell_position.y < numberOfRows);
    }

    // Process the cell type to determine if it’s empty, contains a mine, or has surrounding mines
    void Board::ProcessCellType(sf::Vector2i cell_position) {

        switch (board[cell_position.x][cell_position.y]->GetCellType()) {
        case CellType::EMPTY:
            ProcessEmptyCell(cell_position);
            break;
        case CellType::MINE:
            ProcessMineCell(cell_position);
            break;
        default:
            break;
        }
    }

    void Board::ProcessEmptyCell(sf::Vector2i cell_position) {
        OpenEmptyCells(cell_position);
    }

    void Board::ProcessMineCell(sf::Vector2i cell_position) {
        gameplayManager->setGameResult(GameResult::LOST);
        boardState = BoardState::COMPLETED;
        RevealAllMines();
    }

    void Board::OpenEmptyCells(sf::Vector2i cell_position) {
        switch (board[cell_position.x][cell_position.y]->GetCellState())
        {
        case::Gameplay::CellState::OPEN:
            return;
        case::Gameplay::CellState::FLAGGED:
            flaggedCells--;
        default:
            board[cell_position.x][cell_position.y]->Open();
        }

        for (int a = -1; a < 2; a++)
        {
            for (int b = -1; b < 2; b++)
            {
                if ((a == 0 && b == 0) || !IsValidCellPosition(sf::Vector2i(a + cell_position.x, b + cell_position.y))) continue;

                sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);
                OpenCell(next_cell_position);
            }
        }
    }

    void Board::ResetBoard() {
        for (int row = 0; row < numberOfRows; ++row) {
            for (int col = 0; col < numberOfColumns; ++col) {
                board[row][col]->Reset();
            }
        }
        flaggedCells = 0;
        boardState = BoardState::FIRST_CELL;
    }

    void Board::flagAllMines()
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                if (board[row][col]->GetCellType() == CellType::MINE && board[row][col]->GetCellState() != CellState::FLAGGED)
                {
                    FlagCell(sf::Vector2i(row, col));
                }
            }
        }
    }

    void Board::ShowBoard()
    {
        switch (boardState)
        {
        case BoardState::FIRST_CELL:
            PopulateBoard(sf::Vector2i(0, 0));
            OpenAllCells();
            break;
        case BoardState::PLAYING:
            OpenAllCells();
            break;
        case BoardState::COMPLETED:
            // The board is already completed, no action needed
            break;
        default:
            break;
        }
    }

    void Board::OpenAllCells()
    {
        for (int a = 0; a < numberOfRows; ++a)
        {
            for (int b = 0; b < numberOfColumns; ++b)
            {
                board[a][b]->Open();
            }
        }
    }

    void Board::RevealAllMines()
    {
        for (int row = 0; row < numberOfRows; row++)
        {
            for (int col = 0; col < numberOfColumns; col++)
            {
                // Check if the cell contains a mine
                if (board[row][col]->GetCellType() == CellType::MINE)
                {
                    // Open the mine cell
                    board[row][col]->SetCellState(CellState::OPEN);
                }
            }
        }
    }

    // Wrapper for resetting the board
    void Board::reset() {
        ResetBoard();
    }

    // Get the current state of the board
    BoardState Board::getBoardState() const {
        return boardState;
    }

    // Set the current state of the board
    void Board::setBoardState(BoardState state) {
        boardState = state;
    }

    // Get the number of mines that have not been flagged
    int Board::getMinesCount() const {
        return minesCount - flaggedCells;
    }

    float Board::GetCellWidthInBoard() const
    {
        return (boardWidth - horizontalCellPadding) / static_cast<float>(numberOfColumns);
    }

    float Board::GetCellHeightInBoard() const
    {
        return (boardHeight - verticalCellPadding) / static_cast<float>(numberOfRows);
    }
}
