#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"

namespace Gameplay
{
    class GameplayManager;
    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class Board
    {
    private:
        GameplayManager *gameplayManager;
        // Board Constants
        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;
        static const int minesCount = 9;

        // State and View Members
        BoardState boardState;
        Cell* board[numberOfRows][numberOfColumns];
        int flaggedCells;

        
        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;
        // Board Rendering
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;

        const float boardPosition = 530.f;

        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        // Randomization
        std::default_random_engine randomEngine;
        std::random_device randomDevice;

        // Private helper methods
        void CreateBoard();
        void InitializeBoardImage();
        void PopulateBoard(sf::Vector2i first_cell_position);
        void PopulateMines(sf::Vector2i first_cell_position);
        void PopulateCells();
        int CountMinesAround(sf::Vector2i cell_position);
        void FlagCell(sf::Vector2i cell_position);
        void OpenCell(sf::Vector2i cell_position);
        void ProcessCellType(sf::Vector2i cell_position);
        void ProcessEmptyCell(sf::Vector2i cell_position);
        void ProcessMineCell(sf::Vector2i cell_position);
        void OpenEmptyCells(sf::Vector2i cell_position);
        void ResetBoard();
        void DeleteBoard();
        void OpenAllCells();
        void RevealAllMines();

    public:
        Board(GameplayManager *gameplayManager);
        ~Board();

        // Game flow methods
        void Initialize();
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);
        void OnCellButtonClicked(sf::Vector2i cell_position, ButtonType buttonType);
        bool IsValidCellPosition(sf::Vector2i cell_position);
        void Reset();

        // Getters
        BoardState GetBoardState() const;
        void SetBoardState(BoardState state);
        int GetMinesCount() const;
        float GetCellWidthInBoard() const;
        float GetCellHeightInBoard() const;


        bool AreAllCellsOpen();
        void FlagAllMines();
        void ShowBoard();
    };
}
