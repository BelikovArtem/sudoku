#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QTimer>
#include "Cell.h"
#include "Enums.h"

class Game : public QObject {

    Q_OBJECT    // Q_OBJECT macro needed to use signals/slots

public:
    Game()
    {
        grid = QList<Cell*>();          // Sudoku grid
        gameState = NotStarted;          // Win, Continues, Loss, Pause, NotStarted
        level = NotChoosed;                          // Low, Medium, High, NotChoosed
        Cell *lastOpenedCell = nullptr;
        openedCells = 0;
        scores = 0;
        QTimer *timer = nullptr;
        time = 0;
    }

    Game(QList<Cell> _grid, DifficultyLevel _level)
    {
        level =_level;

        for (Cell _ : _grid)
            grid.append(new Cell(_));

        timer = new QTimer(nullptr);
        connect(timer, &QTimer::timeout, this, &Game::timerSlot);
    }

    ~Game()
    {
        if (timer)
            delete timer;

        for (Cell *_ : grid)
            delete _;

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
    QList<Cell*> grid;
    GameState gameState;
    DifficultyLevel level;
    Cell *lastOpenedCell;
    int openedCells;
    int scores;
    const int CELLS_COUNT = 81;
    QTimer *timer;
    long time;

private slots:
    void timerSlot();

};

#endif // GAME_H
