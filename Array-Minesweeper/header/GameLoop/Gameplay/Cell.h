#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UI Elements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace Gameplay
{
    class Board;
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
        CellState current_cell_state;
        CellType cell_type;
        Board* board;
        sf::Vector2i position;
        int mines_around;

        const float cell_top_offset = 274.f;
        const float cell_left_offset = 583.f;
        const int tile_size = 32;
        const int slice_count = 12;
        const std::string cell_texture_path = "assets/textures/cells.jpeg";
        Button* cell_button;

        void initialize(float width, float height, sf::Vector2i position);
        sf::Vector2f getCellScreenPosition(float width, float height) const;
        void setCellTexture();

        void registerCellButtonCallback();
        void cellButtonCallback(MouseButtonType button_type);

    public:
        Cell(float width, float height, sf::Vector2i position, Board *board);
        ~Cell() = default;

        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);

        void reset();
        bool canOpenCell() const;
        void toggleFlag();
        void open();

        CellState getCellState() const;
        void setCellState(CellState state);
        CellType getCellType() const;
        void setCellType(CellType type);
        sf::Vector2i getCellPosition();
    };
}
