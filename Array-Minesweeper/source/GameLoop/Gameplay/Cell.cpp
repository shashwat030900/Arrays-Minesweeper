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
        cellButton = new Button(cellTexturePath, cellScreenPosition, width * sliceCount, height);
        RegisterCellButtonCallback();
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

        switch (currentCellState)
        {
        case CellState::HIDDEN:
            cellButton->setTextureRect(sf::IntRect(10 * tileSize, 0, tileSize, tileSize));
            break;
        case CellState::OPEN:
            cellButton->setTextureRect(sf::IntRect(index * tileSize, 0, tileSize, tileSize));
            break;
        case CellState::FLAGGED:
            cellButton->setTextureRect(sf::IntRect(11 * tileSize, 0, tileSize, tileSize));
            break;
        }
    }

    void Cell::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        if (cellButton) cellButton->handleButtonInteractions(eventManager, window);
    }

    void Cell::Render(sf::RenderWindow& window)
    {
        SetCellTexture();
        if (cellButton) cellButton->render(window);
    }

    void Cell::RegisterCellButtonCallback()
    {
        cellButton->registerCallbackFunction([this](ButtonType buttonType) {
            CellButtonCallback(buttonType);
            });
    }

    void Cell::CellButtonCallback(ButtonType button_type)
    {
        board->OnCellButtonClicked(GetCellPosition(), button_type);
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

    void Cell::Open()
    {
        SetCellState(CellState::OPEN);
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

    float Cell::GetCellLeftOffset() const
    {
        return cellLeftOffset;
    }

    float Cell::GetCellTopOffset() const
    {
        return cellTopOffset;
    }
}
