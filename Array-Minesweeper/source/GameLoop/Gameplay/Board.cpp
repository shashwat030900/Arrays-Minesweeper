#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

namespace Gameplay
{
    Board::Board()
        : boardState(BoardState::FIRST_CELL), flaggedCells(0), randomEngine(randomDevice())
    {
        CreateBoard();
    }

    Board::~Board()
    {
        DeleteBoard();
    }

    void Board::Initialize()
    {
        InitializeBackgroundImage();
        InitializeBoardImage();
        InitializeCells();
        Reset();
    }

    void Board::InitializeBackgroundImage()
    {
        if (!backgroundTexture.loadFromFile("assets/textures/minesweeper_bg.png"))
        {
            std::cerr << "Failed to load background texture!" << std::endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setColor(sf::Color(255, 255, 255, backgroundAlpha));
    }

    void Board::InitializeBoardImage()
    {
        if (!boardTexture.loadFromFile("assets/textures/board.png"))
        {
            std::cerr << "Failed to load board texture!" << std::endl;
            return;
        }
        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(530.f, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x, boardHeight / boardTexture.getSize().y);
    }

    void Board::CreateBoard()
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col] = new Cell(sf::Vector2i(row, col));
            }
        }
    }

    void Board::InitializeCells()
    {
        float cell_width = GetCellWidth();
        float cell_height = GetCellHeight();
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col]->Initialize(cell_width, cell_height);
            }
        }
    }

    void Board::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col]->Update(eventManager, window);
            }
        }
    }

    void Board::Render(sf::RenderWindow& window)
    {
        window.draw(backgroundSprite);
        window.draw(boardSprite);
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                board[row][col]->Render(window);
            }
        }
    }

    void Board::ProcessCellInput(Event::EventPollingManager& eventManager, sf::Vector2i cell_position)
    {
        if (boardState == BoardState::COMPLETED)
            return;

        if (eventManager.PressedLeftMouseButton())
        {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            OpenCell(cell_position);
        }
            
        else if (eventManager.PressedRightMouseButton()) {
            Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);
            FlagCell(cell_position);
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
        if (board[cell_position.x][cell_position.y]->CanOpenCell())
        {
            if (boardState == BoardState::FIRST_CELL)
            {
                PopulateBoard(cell_position);
                boardState = BoardState::PLAYING;
            }

            ProcessCellType(cell_position);
            board[cell_position.x][cell_position.y]->SetCellState(CellState::OPEN);
        }
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
    bool Board::AreAllCellsOpen() {
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
            Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
            ProcessMineCell(cell_position);
            break;
        default:
            break;
        }
    }

    // Process an empty cell, opening neighboring cells if applicable
    void Board::ProcessEmptyCell(sf::Vector2i cell_position) {
        OpenEmptyCells(cell_position);
    }

    // Process a cell that contains a mine, triggering game over logic
    void Board::ProcessMineCell(sf::Vector2i cell_position) {
        RevealAllMines();
        boardState = BoardState::COMPLETED;
    }

    // Open all contiguous empty cells starting from the given cell
    void Board::OpenEmptyCells(sf::Vector2i cell_position) {

        switch (board[cell_position.x][cell_position.y]->GetCellState())
        {
        case::Gameplay::CellState::OPEN:
            return;
        case::Gameplay::CellState::FLAGGED:
            flaggedCells--;
        default:
            board[cell_position.x][cell_position.y]->OpenCell();
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

    // Reset the board to its initial state
    void Board::ResetBoard() {
        for (int row = 0; row < numberOfRows; ++row) {
            for (int col = 0; col < numberOfColumns; ++col) {
                board[row][col]->Reset();
            }
        }
        flaggedCells = 0;
        boardState = BoardState::FIRST_CELL;
    }

    void Board::FlagAllMines()
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
                board[a][b]->OpenCell();
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
    void Board::Reset() {
        ResetBoard();
    }

    // Get the current state of the board
    BoardState Board::GetBoardState() const {
        return boardState;
    }

    // Set the current state of the board
    void Board::SetBoardState(BoardState state) {
        boardState = state;
    }

    // Get the number of mines that have not been flagged
    int Board::GetMinesCount() const {
        return minesCount - flaggedCells;
    }

    float Board::GetCellWidth() const
    {
        return (boardWidth - boardWidthOffset) / static_cast<float>(numberOfColumns);
    }

    float Board::GetCellHeight() const
    {
        return (boardHeight - boardHeightOffset) / static_cast<float>(numberOfRows);
    }


    float Board::GetSampleCellLeftOffset() const
    {
        return board[0][0]->GetCellLeftOffset();
    }

    float Board::GetSampleCellTopOffset() const
    {
        return board[0][0]->GetCellTopOffset();
    }

    sf::Vector2i Board::GetCellFromMousePosition(const sf::Vector2i& mouse_position) const
    {
        float cell_width = GetCellWidth();
        float cell_height = GetCellHeight();
        float cell_left_offset = GetSampleCellLeftOffset();
        float cell_top_offset = GetSampleCellTopOffset();

        int grid_x = (mouse_position.x - cell_left_offset) / cell_width;
        int grid_y = (mouse_position.y - cell_top_offset) / cell_height;

        return sf::Vector2i(grid_x, grid_y);
    }

    int Board::GetNumberOfColumns() const
    {
        return numberOfColumns;
    }

    int Board::GetNumberOfRows() const
    {
        return numberOfRows;
    }


}
