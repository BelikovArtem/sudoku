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

signals:
    void timeChanged();
    void scoreChanged();
    void mistakesChanged();
    void usernameChanged();
    void gameStateChanged();
    void difficultyLevelChanged();
    void gridChanged(int index, const QString &data, bool isMistake);

private:
    QTimer *timer;
    QList<Cell*> m_grid;

    long m_time;
    int m_score;
    int m_mistakes;
    QString m_level;        // difficulty level
    int m_openedCells;
    QString m_gameState;

private slots:
    void timerSlot();
    void onIsOpenedChanged(int index);
    void onNoteModeNumbersChanged(int index, const QString &numbers);
    void onIncorrectNumberEntered(int index, int number, bool isFromUndo);
};

#endif // GAME_H
