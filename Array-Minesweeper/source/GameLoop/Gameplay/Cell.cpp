#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

namespace Gameplay
{
    Cell::Cell(float width, float height, sf::Vector2i position, Board* board)
    {
        Initialize(width, height, position);
        this->board = board;
    }

    void Cell::Initialize(float width, float height, sf::Vector2i position)
    {
        this->position = position;
        sf::Vector2f cellScreenPosition = GetCellScreenPosition(width, height);
        cellButton = new Button("assets/textures/cells.jpeg", cellScreenPosition, width * sliceCount, height);
        RegisterButtonCallback();
    }

    sf::Vector2f Cell::GetCellScreenPosition(float width, float height) const
    {
        float xScreenPosition = cellLeftOffset + position.x * width;
        float yScreenPosition = cellTopOffset + position.y * height;
        return sf::Vector2f(xScreenPosition, yScreenPosition);
    }

    void Cell::SetCellTexture()
    {
        int index = static_cast<int>(cellType);
        if (static_cast<int>(currentCellState) == 1)
            std::cout << "Setting cell texture: State=" << static_cast<int>(currentCellState)
            << ", Type=" << static_cast<int>(cellType) << ", Index=" << index << std::endl;

        switch (currentCellState)
        {
        case CellState::HIDDEN:
            cellButton->SetTextureRect(sf::IntRect(10 * tileSize, 0, tileSize, tileSize));
            break;
        case CellState::OPEN:
            cellButton->SetTextureRect(sf::IntRect(index * tileSize, 0, tileSize, tileSize));
            break;
        case CellState::FLAGGED:
            cellButton->SetTextureRect(sf::IntRect(11 * tileSize, 0, tileSize, tileSize));
            break;
        }
    }

    void Cell::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        if (cellButton) cellButton->UpdateState(eventManager, window);
    }

    void Cell::Render(sf::RenderWindow& window)
    {
        SetCellTexture();
        if (cellButton) cellButton->Render(window);
    }

    void Cell::RegisterButtonCallback()
    {
        cellButton->RegisterCallbackFunction([this](ButtonType buttonType) {
            cellButtonCallback(buttonType);
            });
    }

    void Cell::cellButtonCallback(ButtonType button_type)
    {
        board->OnCellButtonClicked(GetCellPosition(), button_type);
    }

    CellState Cell::GetCellState() const
    {
        return currentCellState;
    }

    void Cell::SetCellState(CellState state)
    {
        currentCellState = state;
    }

    CellType Cell::GetCellType() const
    {
        return cellType;
    }

    void Cell::SetCellType(CellType type)
    {
        cellType = type;
    }


    void Cell::SetCellPosition(sf::Vector2i grid_position)
    {
        position = grid_position;
    }

    sf::Vector2i Cell::GetCellPosition()
    {
        return position;
    }

    int Cell::GetMinesAround() const
    {
        return mines_around;
    }

    void Cell::SetMinesAround(int mine_count)
    {
        mines_around = mine_count;
    }

    void Cell::Reset()
    {
        currentCellState = CellState::HIDDEN;
        cellType = CellType::EMPTY;
        mines_around = 0;
    }

    bool Cell::CanOpenCell() const
    {
        return currentCellState != CellState::FLAGGED && currentCellState != CellState::OPEN;
    }

    void Cell::ToggleFlag()
    {
        if (currentCellState == CellState::HIDDEN)
        {
            currentCellState = CellState::FLAGGED;
        }
        else if (currentCellState == CellState::FLAGGED)
        {
            currentCellState = CellState::HIDDEN;
        }
    }

    void Cell::OpenCell()
    {
        std::cout << "Changing cell state" << "\n";
        SetCellState(CellState::OPEN);
    }

    float Cell::GetCellLeftOffset() const
    {
        return cellLeftOffset;
    }

    float Cell::GetCellTopOffset() const
    {
        return cellTopOffset;
    }

}
