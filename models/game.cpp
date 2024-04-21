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
// Parse QString to QList<Cell*>
void Game::setGrid(QString strGrid)
{
    m_openedCells = 0;
    char nextCharFromString;
    int number = 0, index = 0;

    m_grid.clear();
    while (strGrid.length() >= 2) {
        // get first QChar of the QString and convert it to the char
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

            bool isOpened = nextCharFromString != 'x';

            Cell *cell = new Cell(number, isOpened, index);

            // connect to cell`s signal
            connect(cell, &Cell::incorrectNumberEntered, this,
                    &Game::onIncorrectNumberEntered);
            connect(cell, &Cell::isOpenedChanged, this, &Game::onIsOpenedChanged);
            connect(cell, &Cell::noteModeNumbersChanged, this,
                    &Game::onNoteModeNumbersChanged);

            m_grid.append(cell);
            m_openedCells += isOpened ? 1 : 0;

            // remove 2 chars from the beggining of the string
            strGrid.remove(0, 2);

            QString displayNumber = isOpened ? QString::number(number) : " ";
            emit gridChanged(index, displayNumber, false);
            index++;
        }
    }
}

void Game::setGameState(QString state)
{
    m_gameState = state;
    if (state == "Loose") {
        endGame();
        return;
    }
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
    m_time = 0;
    m_mistakes = 0;
    m_score = 0;

    timer->start();

    m_gameState = "Continues";
    emit gameStateChanged();
}

void Game::endGame()
{
    timer->stop();
    emit gameStateChanged();
}

/*
 * PRIVATE SLOTS
 */
void Game::timerSlot()
{
    m_time++;
    emit timeChanged();
}

void Game::onIsOpenedChanged(int index, bool isTip)
{
    m_openedCells++;

    if (!isTip) {
        m_score += 150;
    }

    if (m_openedCells == 81) {

        if (m_level == "Low") {
            m_score += 250;
        } else if (m_level == "Medium") {
            m_score += 500;
        } else {
            m_score += 1000;
        }
        m_score -= m_time;
        if (m_score < 100) m_score = 100;

        m_gameState = "Win";
        endGame();
    }

    emit scoreChanged();
    emit gridChanged(index, QString::number(m_grid.at(index)->number()), false);
}

void Game::onNoteModeNumbersChanged(int index, const QString &numbers)
{
    emit gridChanged(index, numbers, false);
}

void Game::onIncorrectNumberEntered(int index, int number, bool isFromUndo)
{
    // if number is zero, just clear the cell on a View
    if (!isFromUndo && number != 0) {
        m_mistakes++;
        emit mistakesChanged();

        if (m_mistakes >= 3) {
            m_gameState = "Loose";
            endGame();
        }
    }

    QString displayData = number == 0 ? " " : QString::number(number);
    emit gridChanged(index, displayData, true);
}
