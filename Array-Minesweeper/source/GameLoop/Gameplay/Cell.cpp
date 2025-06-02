#include <SFML/Graphics.hpp>
#include  <iostream>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/UI/UIElements/Button.h"
#include "../../header/GameLoop/Gameplay/Board.h"


using namespace Gameplay;


Cell::Cell(float width, float height, sf::Vector2i position, Board* board)
{
    initialize(width, height, position, board);
}
void Cell::initialize(float width, float height, sf::Vector2i position, Board* board)
{
    this->position = position;
    this->board = board;
    sf::Vector2f cellScreenPosition = getCellScreenPosition(width, height);
    cell_button = new Button(cell_texture_path, cellScreenPosition, width * slice_count, height);
    current_cell_state = CellState::HIDDEN;

    registerCellButtonCallback();
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

sf::Vector2f Cell::getCellScreenPosition(float width, float height) const
{
    float xScreenPosition = cell_left_offset + position.x * width;
    float yScreenPosition = cell_top_offset + position.y * height;
    return sf::Vector2f(xScreenPosition, yScreenPosition);
}

void Cell::update(Event::EventPollingManager& event_manager, sf::RenderWindow& window) {

    if (cell_button)
        cell_button->handelButtonInteractions(event_manager, window);
}

void Cell::registerCellButtonCallback() {
    cell_button->registerCallbackFunction([this](MouseButtonType button_type) {
        cellButtonCallback(button_type);
        });
}
void Cell::cellButtonCallback(MouseButtonType button_type) {


    board->onCellButtonClicked(getCellPosition(), button_type);


}
    
sf::Vector2i Cell::getCellPosition() {

    return position;
}







