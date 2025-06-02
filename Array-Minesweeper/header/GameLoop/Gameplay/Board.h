#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameLoop/Gameplay/Cell.h" 

namespace Gameplay
{
    class Board
    {
    private:
        
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        void initializeBoardImage();
        void initialize();
        void createBoard();

        static const int numberOfRows = 9;
        static const int numberOfColumn = 9;
        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;
        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;
        
        Cell* cell[numberOfRows][numberOfColumn];

        std::default_random_engine randomEngine;
        std::random_device rancdomDevice;

        static const int minesCount = 8;

        void populateBoard();
        void initializeVariables();
        void populateMines();

        int countMinesAround(sf::Vector2i cell_position);
        void populateCells();
        bool isValidCellPosition(sf::Vector2i cell_position);
        void openCell(sf::Vector2i cell_position);

    public:

        Board();
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
        void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);
    };
}