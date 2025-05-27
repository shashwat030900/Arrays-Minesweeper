#include <SFML/Graphics.hpp>
#include "../../header/GameLoop/Gameplay/Cell.h"

using namespace Gameplay;


Cell::Cell(float width, float height, sf::Vector2i position)
{
    initialize(width, height, position);
}
void Cell::initialize(float width, float height, sf::Vector2i position)
{
    this->position = position;
    sf::Vector2f float_position(static_cast<float>(position.x), static_cast<float>(position.y));
    cell_button = new Button(cell_texture_path, float_position, width * slice_count, height);
}
void Cell::render(sf::RenderWindow& window) {
    setCellTexture();
    if (cell_button) cell_button->render(window);
    
}

CellState Cell::getCellState() const {

    return current_cell_state;
}

void Cell::setCellState(CellState state) {

    current_cell_state = state;
}

CellType Cell::getCellType() const {

    return cell_type;
}

void Cell::setCellType(CellType type) {

    cell_type = type;

}
void Cell::setCellTexture() {

    int index = static_cast<int>(cell_type);
    switch (current_cell_state) {

    case  CellState::OPEN:
            cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
            break;

    case  CellState::HIDDEN:
        cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
        break;

    case CellState::FLAGGED:

        cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));

    }
}

















