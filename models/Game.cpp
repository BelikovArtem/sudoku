#include "Game.h"

/*
* PUBLIC METHODS
*/
void Game::checkWin()
{
    if (openedCellsCount == CELLS_COUNT) {
        gameState = GameState::Win;
        endGame(gameState);
    }
}

void Game::setFocus(Cell::Position pos)
{
    if (gameState == GameState::Continues) {
        cellInFocus = grid.at(pos.i * 9 + pos.j);
    }
}

void Game::openCell(int number)
{
    if (gameState == GameState::Continues) {
        cellInFocus->setNumber(number);
        if (cellInFocus->getNumber() == number) {
            cellInFocus->setOpenStatus(true);
            openedCellsCount++;
        }
    }
}

void Game::clearCell()
{
    cellInFocus->setOpenStatus(false);
}

void Game::startGame()
{
    timer->start(1);
    gameState = GameState::Continues;
}

void Game::endGame(GameState state)
{
    timer->stop();
    gameState = state;
}

void Game::undo()
{
    if (cellInFocus) {
        cellInFocus->setOpenStatus(false);
    }
}

void Game::pauseGame()
{
    timer->stop();
    gameState = GameState::Pause;
}

void Game::setGrid(QList<Cell> _grid)
{
    for (const auto &_ : _grid)
        grid.append(new Cell(_));
}

/*
 * PRIVATE SLOTS
 */
void Game::timerSlot()
{
    time++;
}
