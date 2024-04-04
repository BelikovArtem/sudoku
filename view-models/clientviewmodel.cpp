#include "clientviewmodel.h"

ClientViewModel::ClientViewModel(QObject *parent)
    : QObject{parent}
{
    // connect to game model signals
    connect(&m_game, &Game::timeChanged, this, &ClientViewModel::onTimerChanged);
    connect(&m_game, &Game::gridChanged, this, &ClientViewModel::onGridChanged);
    connect(&m_game, &Game::scoreChanged, this, &ClientViewModel::onScoreChanged);
    connect(&m_game, &Game::mistakesChanged, this, &ClientViewModel::onMistakesChanged);
    connect(&m_game, &Game::gameStateChanged, this, &::ClientViewModel::onGameStateChanged);
    connect(&m_game, &Game::difficultyLevelChanged, this, &::ClientViewModel::onLevelChanged);
}

/*
 * SETTERS
 */
void ClientViewModel::setGameState(const QString &gameState)
{
    m_game.setGameState(gameState);
}

void ClientViewModel::setDifficultyLevel(const QString &difficultyLevel)
{
    m_game.setDifficultyLevel(difficultyLevel);
}

/*
 * AVAILIBLE FROM UI
 */
void ClientViewModel::startNewGame()
{
    m_game.startGame();

    QString grid = "4x 9x 7 5 8 6 2 3 1\r\n"
                   "8 3x 1x 9 2 7 5 4x 6x\r\n"
                   "5x 6 2x 3 1x 4x 9 8x 7x\r\n"
                   "9x 7 5 4 6 1 8 2 3\r\n"
                   "1x 8 6 2 3x 5 4 7 9\r\n"
                   "3 2 4 8 7 9x 6x 1 5x\r\n"
                   "7x 4x 3x 6 5 2 1 9 8\r\n"
                   "2x 5x 8x 1 9 3x 7 6x 4\r\n"
                   "6 1x 9 7 4x 8x 3x 5x 2x ";
    m_game.setGrid(grid);
}

/*
 * PUBLIC SLOTS
 */
// FROM MODELS
void ClientViewModel::onTimerChanged()
{
    emit timeChanged();
}

void ClientViewModel::onLevelChanged()
{
    emit difficultyLevelChanged();
}

void ClientViewModel::onScoreChanged()
{
    emit scoreChanged();
}

void ClientViewModel::onMistakesChanged()
{
    emit mistakesChanged();
}

void ClientViewModel::onGameStateChanged()
{
    emit gameStateChanged();
}

void ClientViewModel::onGridChanged(int index)
{
    bool isOpened = m_game.grid().at(index)->getIsOpened();
    int number = m_game.grid().at(index)->getNumber();
    QString numberToInsert = isOpened ? QString::number(number) : " ";

    if (index > m_grid.count() - 1) {
        m_grid.append(numberToInsert);
    } else {
        m_grid[index] = numberToInsert;
    }

    emit gridChanged();
}
