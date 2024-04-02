#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}, m_gameState("NotStarted"), m_level("NotChoosed"), m_openedCells(0),
    m_score(0), m_time(0), m_mistakes(0)
{
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &Game::timerSlot);

    m_grid = QList<Cell*>();
}

/*
 * SETTERS
 */
void Game::setGameState(QString state)
{
    m_gameState = state;

    emit gameStateChanged();
}

void Game::setDifficultyLevel(QString level)
{
    m_level = level;

    emit difficultyLevelChanged();
}

/*
 * PUBLIC METHODS
 */
void Game::startGame()
{
    timer->start();

    m_gameState = "Continues";
    emit gameStateChanged();
}

void Game::enterNumberInCell(int index, int number)
{
    m_grid.at(index)->setNumber(number);

    emit gridChanged();
}

/*
 * PRIVATE SLOTS
 */
void Game::timerSlot()
{
    m_time++;

    emit timeChanged();
}
