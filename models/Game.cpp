#include "Game.h"

/*
* PUBLIC METHODS
*/
void Game::checkWin()
{
    if (openedCells == CELLS_COUNT) {
        gameState = GameState::Win;
    }
}

void Game::openCell(Cell::Position pos)
{
    lastOpenedCell = grid.at(pos.i * pos.j);
    lastOpenedCell->setOpenStatus(true);
    openedCells++;
}

void Game::clearCell(Cell::Position pos)
{
    grid.at(pos.i * pos.j)->setOpenStatus(false);
}

void Game::endGame()
{
    timer->stop();
}

void Game::undo()
{
    if (lastOpenedCell)
        lastOpenedCell->setOpenStatus(false);
}

void Game::pauseGame()
{
    timer->stop();
    gameState = GameState::Pause;
}

/*
 * PRIVATE SLOTS
 */
void Game::timerSlot()
{
    time++;
}
