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
void ClientViewModel::startNewGame(const QString &grid)
{
    m_game.setGrid(grid);
    m_game.startGame();
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
