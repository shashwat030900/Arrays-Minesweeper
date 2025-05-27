#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

enum class CellState {

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
namespace Gameplay
{

    class Cell
    {
    private:
        sf::Vector2i position;

        const int tile_size = 128;
        const int slice_count = 12;
        const std::string cell_texture_path = "assets/textures/cells.jpeg";

        Button* cell_button;

        void initialize(float width, float height, sf::Vector2i position);
        CellState current_cell_state;
        CellType cell_type;

        const float cell_top_offset = 274.f;
        const float cell_left_offset = 583.f;
        sf::Vector2f getCellScreenPosition() const;


    public:
        Cell(float width, float height, sf::Vector2i position);
        ~Cell() = default;

        void render(sf::RenderWindow& window);

        CellState getCellState() const;
        void setCellState(CellState state);
        CellType getCellType() const;
        void setCellType(CellType type);
        void setCellTexture();

    };
}