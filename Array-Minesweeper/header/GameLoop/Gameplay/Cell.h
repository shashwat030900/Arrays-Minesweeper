#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    enum class CellState
    {
        HIDDEN,
        OPEN,
        FLAGGED,
    };

    enum class CellType
    {
        EMPTY,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        MINE,
    };

    class Cell
    {
    private:
        // Cell data members
        CellState cell_state;
        CellType cell_type;
        sf::Vector2i position;
        int mines_around;

        // View and Rendering
        const float cell_top_offset = 274.f;
        const float cell_left_offset = 583.f;
        const int tile_size = 32;
        const int slice_count = 12;
        Button cell_button;

        // Private helper functions
        
        void SetCellTexture();

    public:
        Cell(sf::Vector2i grid_position);
        ~Cell() = default;

        sf::Vector2f GetCellScreenPosition(float width, float height) const;

        // Initialization and rendering functions
        void Initialize(float width, float height);
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);

        // Cell state and type management
        CellState GetCellState() const;
        void SetCellState(CellState state);

        CellType GetCellType() const;
        void SetCellType(CellType type);

        sf::Vector2i GetCellPosition() const;
        void SetCellPosition(sf::Vector2i grid_position);

        int GetMinesAround() const;
        void SetMinesAround(int mine_count);

        float GetCellLeftOffset() const;
        float GetCellTopOffset() const;

        void Reset();
        bool CanOpenCell() const;
        void ToggleFlag();
        void OpenCell();
    };
}
