#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

namespace Gameplay
{
    Board::Board()
        : board_state(BoardState::FIRST_CELL), flagged_cells(0), random_engine(random_device())
    {
        CreateBoard();
    }

    Board::~Board()
    {
        DeleteBoard();
    }

    void Board::Initialize(sf::RenderWindow& window)
    {
        InitializeBackgroundImage(window);
        InitializeBoardImage(window);
        InitializeCells();
        Reset();
    }

    void Board::InitializeBackgroundImage(sf::RenderWindow& window)
    {
        background_image.Initialize("assets/textures/minesweeper_bg.png", window.getSize().x, window.getSize().y, sf::Vector2f(0, 0));
        background_image.SetImageAlpha(background_alpha);
    }

    void Board::InitializeBoardImage(sf::RenderWindow& window)
    {
        board_image.Initialize("assets/textures/board.png", board_width, board_height, sf::Vector2f(0, 0));
        board_image.SetCentreAlinged(window);
    }

    void Board::CreateBoard()
    {
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
            {
                board[row][col] = new Cell(sf::Vector2i(row, col));
            }
        }
    }

    void Board::InitializeCells()
    {
        float cell_width = GetCellWidth();
        float cell_height = GetCellHeight();
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
            {
                board[row][col]->Initialize(cell_width, cell_height);
            }
        }
    }

    void Board::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
            {
                board[row][col]->Update(eventManager, window);
            }
        }
    }

    void Board::Render(sf::RenderWindow& window)
    {
        background_image.Render(window);
        board_image.Render(window);
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
            {
                board[row][col]->Render(window);
            }
        }
    }

    void Board::ProcessCellInput(Event::EventPollingManager& eventManager, sf::Vector2i cell_position)
    {
        if (board_state == BoardState::COMPLETED)
            return;

        if (eventManager.pressedLeftMouseButton())
        {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            OpenCell(cell_position);
        }
            
        else if (eventManager.pressedRightMouseButton()) {
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
        std::uniform_int_distribution<int> x_dist(0, number_of_columns - 1);
        std::uniform_int_distribution<int> y_dist(0, number_of_rows - 1);

        int mines_placed = 0;
        while (mines_placed < mines_count)
        {
            int x = x_dist(random_engine);
            int y = y_dist(random_engine);

            if ((x == first_cell_position.x && y == first_cell_position.y) || board[x][y]->GetCellType() == CellType::MINE)
                continue;

            board[x][y]->SetCellType(CellType::MINE);
            ++mines_placed;
        }
    }

    void Board::PopulateCells()
    {
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
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
        flagged_cells += (board[cell_position.x][cell_position.y]->GetCellState() == CellState::FLAGGED) ? 1 : -1;
    }

    void Board::OpenCell(sf::Vector2i cell_position)
    {
        if (board[cell_position.x][cell_position.y]->CanOpenCell())
        {
            if (board_state == BoardState::FIRST_CELL)
            {
                PopulateBoard(cell_position);
                board_state = BoardState::PLAYING;
            }

            ProcessCellType(cell_position);
            board[cell_position.x][cell_position.y]->SetCellState(CellState::OPEN);
        }
    }

    void Board::DeleteBoard()
    {
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
            {
                delete board[row][col];
            }
        }
    }

    // Check if all non-mine cells are open
    bool Board::AreAllCellsOpen() {
        int total_cell_count = number_of_rows * number_of_columns;
        int open_cell_count = 0;

        for (int row = 0; row < number_of_rows; ++row) {
            for (int col = 0; col < number_of_columns; ++col) {
                if (board[row][col]->GetCellState() == CellState::OPEN && board[row][col]->GetCellType() != CellType::MINE) {
                    open_cell_count++;
                }
            }
        }

        // Check if all non-mine cells are open
        return (total_cell_count - open_cell_count == mines_count);
    }

    // Check if a given cell position is within the board boundaries
    bool Board::IsValidCellPosition(sf::Vector2i cell_position) {
        return (cell_position.x >= 0 && cell_position.y >= 0 &&
            cell_position.x < number_of_columns && cell_position.y < number_of_rows);
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

    // Process an empty cell, opening neighboring cells if applicable
    void Board::ProcessEmptyCell(sf::Vector2i cell_position) {
        OpenEmptyCells(cell_position);
    }

    // Process a cell that contains a mine, triggering game over logic
    void Board::ProcessMineCell(sf::Vector2i cell_position) {
        std::cout << "Mine triggered at (" << cell_position.x << ", " << cell_position.y << ") - Game Over\n";
        Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
        RevealAllMines();
        board_state = BoardState::COMPLETED;
    }

    // Open all contiguous empty cells starting from the given cell
    void Board::OpenEmptyCells(sf::Vector2i cell_position) {
        switch (board[cell_position.x][cell_position.y]->GetCellState())
        {
        case::Gameplay::CellState::OPEN:
            return;
        case::Gameplay::CellState::FLAGGED:
            flagged_cells--;
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
        for (int row = 0; row < number_of_rows; ++row) {
            for (int col = 0; col < number_of_columns; ++col) {
                board[row][col]->Reset();
            }
        }
        flagged_cells = 0;
        board_state = BoardState::FIRST_CELL;
    }

    void Board::FlagAllMines()
    {
        for (int row = 0; row < number_of_rows; ++row)
        {
            for (int col = 0; col < number_of_columns; ++col)
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
        switch (board_state)
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
        for (int a = 0; a < number_of_rows; ++a)
        {
            for (int b = 0; b < number_of_columns; ++b)
            {
                board[a][b]->OpenCell();
            }
        }
    }

    void Board::RevealAllMines()
    {
        for (int row = 0; row < number_of_rows; row++)
        {
            for (int col = 0; col < number_of_columns; col++)
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
        return board_state;
    }

    // Set the current state of the board
    void Board::SetBoardState(BoardState state) {
        board_state = state;
    }

    // Get the number of mines that have not been flagged
    int Board::GetMinesCount() const {
        return mines_count - flagged_cells;
    }

    float Board::GetCellWidth() const
    {
        return (board_width - board_width_offset) / static_cast<float>(number_of_columns);
    }

    float Board::GetCellHeight() const
    {
        return (board_height - board_height_offset) / static_cast<float>(number_of_rows);
    }


    float Board::GetSampleCellLeftOffset() const
    {
        return board[0][0]->GetCellLeftOffset();
    }

    float Board::GetSampleCellTopOffset() const
    {
        return board[0][0]->GetCellTopOffset();
    }

    int Board::GetNumberOfColumns() const
    {
        return number_of_columns;
    }

    int Board::GetNumberOfRows() const
    {
        return number_of_rows;
    }


}
