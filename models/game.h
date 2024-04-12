#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include <QObject>

#include "cell.h"

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    long time() const { return m_time; }
    int score() const { return m_score; }
    int mistakes() const { return m_mistakes; }
    QList<Cell*> grid() const { return m_grid; }
    QString gameState() const { return m_gameState; }
    int openedCells() const { return m_openedCells; }
    QString difficultyLevel() const { return m_level; }

    /*
     * SETTERS
     */
    void setGrid(QString strGrid);
    void setGameState(QString state);
    void setDifficultyLevel(QString level);

    /*
     * PUBLIC METHODS
     */
    void endGame();
    void startGame();
    void enterNumberInCell(int index, int number);

signals:
    void timeChanged();
    void gridChanged(int index);
    void scoreChanged();
    void mistakesChanged();
    void usernameChanged();
    void gameStateChanged();
    void difficultyLevelChanged();

private:
    QTimer *timer;
    QList<Cell*> m_grid;

    long m_time;
    int m_score;
    int m_mistakes;
    QString m_level;
    int m_openedCells;
    QString m_gameState;

private slots:
    void timerSlot();
};

#endif // GAME_H
