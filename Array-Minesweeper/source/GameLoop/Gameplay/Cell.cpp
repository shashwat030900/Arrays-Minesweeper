#include "../../header/GameLoop/Gameplay/Cell.h"
#include <iostream>

namespace Gameplay
{
    Cell::Cell(sf::Vector2i grid_position)
        : cell_button("assets/textures/cells.jpeg", sf::Vector2f(0, 0), tile_size, tile_size),
        position(grid_position), cell_state(CellState::HIDDEN), cell_type(CellType::EMPTY), mines_around(0)
    {
    }

    void Cell::Initialize(float width, float height)
    {
        sf::Vector2f cell_screen_position = GetCellScreenPosition(width, height);
        cell_button.Initialize("assets/textures/cells.jpeg", width * slice_count, height, cell_screen_position);
    }

    sf::Vector2f Cell::GetCellScreenPosition(float width, float height) const
    {
        float x_screen_position = cell_left_offset + position.x * width;
        float y_screen_position = cell_top_offset + position.y * height;
        return sf::Vector2f(x_screen_position, y_screen_position);
    }

    void Cell::SetCellTexture()
    {
        int index = static_cast<int>(cell_type);
        switch (cell_state)
        {
        case CellState::HIDDEN:
            cell_button.SetTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
            break;
        case CellState::OPEN:
            cell_button.SetTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
            break;
        case CellState::FLAGGED:
            cell_button.SetTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
            break;
        }
    }

    void Cell::Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        cell_button.UpdateState(eventManager, window);
    }

    void Cell::Render(sf::RenderWindow& window)
    {
        SetCellTexture();
        cell_button.Render(window);
    }

    // State and Type Management
    CellState Cell::GetCellState() const
    {
        return cell_state;
    }

    void Cell::SetCellState(CellState state)
    {
        cell_state = state;
    }

    CellType Cell::GetCellType() const
    {
        return cell_type;
    }

    void Cell::SetCellType(CellType type)
    {
        cell_type = type;
    }

    sf::Vector2i Cell::GetCellPosition() const
    {
        return position;
    }

    void Cell::SetCellPosition(sf::Vector2i grid_position)
    {
        position = grid_position;
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
        cell_state = CellState::HIDDEN;
        cell_type = CellType::EMPTY;
        mines_around = 0;
    }

    bool Cell::CanOpenCell() const
    {
        return cell_state != CellState::FLAGGED && cell_state != CellState::OPEN;
    }

    void Cell::ToggleFlag()
    {
        if (cell_state == CellState::HIDDEN)
        {
            cell_state = CellState::FLAGGED;
        }
        else if (cell_state == CellState::FLAGGED)
        {
            cell_state = CellState::HIDDEN;
        }
    }

    void Cell::OpenCell()
    {
        SetCellState(CellState::OPEN);
    }
}
