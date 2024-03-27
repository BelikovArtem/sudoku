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
        grid = QList<Cell*>();           // Sudoku grid        
        gameState = NotStarted;          // Win, Continues, Loss, Pause, NotStarted
        level = NotChoosed;              // Low, Medium, High, NotChoosed
        Cell *lastOpenedCell = nullptr;
        openedCellsCount = 0;
        scores = 0;
        timer = new QTimer();
        time = 0;
    }

    Game(QList<Cell> _grid, DifficultyLevel _level)
    {
        level =_level;

        setGrid(_grid);

        timer = new QTimer();
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
    void setFocus(Cell::Position pos);
    void openCell(int number);
    void clearCell();
    void startGame();
    void endGame(GameState state);
    void undo();
    void pauseGame();
    void setGrid(QList<Cell> _grid);

    /*
     * PUBLIC FIELDS
     */
    const int CELLS_COUNT = 81;

private:
    QList<Cell*> grid;
    GameState gameState;
    DifficultyLevel level;
    Cell *cellInFocus;
    int openedCellsCount;
    int scores;
    QTimer *timer;
    long time;

private slots:
    void timerSlot();

};

#endif // GAME_H
