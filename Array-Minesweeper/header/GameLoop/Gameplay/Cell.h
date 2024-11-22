#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"
using namespace UIElements;

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
        CellState currentCellState;
        CellType cellType;
        sf::Vector2i position;
        int mines_around;

        // View and Rendering
        const float cellTopOffset = 274.f;
        const float cellLeftOffset = 583.f;
        const int tileSize = 32;
        const int sliceCount = 12;
        Button *cellButton;

        // Private helper functions
        
        void SetCellTexture();

    public:
        Cell(float width, float height, sf::Vector2i position);
        ~Cell() = default;

        sf::Vector2f GetCellScreenPosition(float width, float height) const;

        // Initialization and rendering functions
        void Initialize(float width, float height, sf::Vector2i position);
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);

        // Cell state and type management
        CellState GetCellState() const;
        void SetCellState(CellState state);

        CellType GetCellType() const;
        void SetCellType(CellType type);

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
