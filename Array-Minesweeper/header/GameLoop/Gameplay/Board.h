#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "../../header/Event/EventPollingManager.h"


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


    public:

        Board();

        void render(sf::RenderWindow& window);
    };
}