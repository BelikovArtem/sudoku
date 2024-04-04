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
void Game::setGrid(QString strGrid)
{
    char nextCharFromString;
    int number = 0, index = 0;

    m_grid.clear();
    while (strGrid.length() >= 2) {
        // get first char of the string and convert it to the char
        nextCharFromString = strGrid.at(0).toLatin1();

        // skip whitespaces and new lines
        if (nextCharFromString == ' ' || nextCharFromString == '\n' ||
            nextCharFromString == '\r') {
            strGrid.removeAt(0);
            continue;
        }

        if (nextCharFromString >= '1' && nextCharFromString <= '9') {
            number = nextCharFromString - '0';   // convert char to int

            // x - cell closed, else opened
            nextCharFromString = strGrid.at(1).toLatin1();

            Cell *cell = new Cell(number, nextCharFromString == 'x' ? false : true, index);
            m_grid.append(cell);

            // remove 2 chars from the beggining of the string
            strGrid.remove(0, 2);

            emit gridChanged(index);
            index++;
        }
    }
}

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

    emit gridChanged(index);
}

/*
 * PRIVATE SLOTS
 */
void Game::timerSlot()
{
    m_time++;

    emit timeChanged();
}
