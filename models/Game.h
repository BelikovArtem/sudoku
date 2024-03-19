#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QTimer>
#include "Cell.h"
#include "Enums.h"

class Game : public QObject {

    Q_OBJECT    // Q_OBJECT macro needed to use signals/slots

public:
    Game(QList<Cell> _grid, DifficultyLevel _level)
    {
        level =_level;

        for (Cell cell : _grid)
            grid.append(new Cell(cell));

        timer = new QTimer(nullptr);
        connect(timer, &QTimer::timeout, this, &Game::timerSlot);
    }

    ~Game()
    {
        if (timer)
            delete timer;

        for (Cell *cell : grid)
            delete cell;

        grid.clear();
    }

    /*
     * PUBLIC METHODS
     */
    void checkWin();
    void openCell(Cell::Position pos);
    void clearCell(Cell::Position pos);
    void endGame();
    void undo();
    void pauseGame();

private:
    QList<Cell*> grid;                  // Sudoku gread
    GameState gameState = Continues;    // Win, Continues, Loss, Pause
    DifficultyLevel level;              // Low, Medium, High
    Cell *lastOpenedCell = nullptr;
    int openedCells;
    int scores;
    const int CELLS_COUNT = 81;
    QTimer *timer;
    long time = 0;

private slots:
    void timerSlot();

};

#endif // GAME_H
