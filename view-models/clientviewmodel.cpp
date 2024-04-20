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
void ClientViewModel::setNoteMode(bool value)
{
    m_isNoteMode = value;
}

void ClientViewModel::setLastClickedCellIndex(int index)
{
    if (index >= 0 && index <= 80) {
        m_lastClickedCellIndex = index;
        emit lastClickedCellIndexChanged();
    }
}

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
void ClientViewModel::handleUndo()
{
    if (m_game.gameState() == "Continues") {
        commandsStack.undo();
    } else {
        emit viewMessage("Game over");
    }
}

void ClientViewModel::handleEraseCell()
{
    // check game state
    if (m_game.gameState() == "Continues") {
        // check lastClickedCellIndex and cell`s openStatus
        if (isLastClickedCellAvailible()) {
            Cell *cell = m_game.grid().at(m_lastClickedCellIndex);
            int numberBeforeChanges = m_grid.at(m_lastClickedCellIndex) == " " ? 0 :
                m_grid.at(m_lastClickedCellIndex).toInt();
            // create a new EraseNumber command
            EraseNumber *eraseNumberCommand = new EraseNumber(cell, numberBeforeChanges);
            /* push created command to the commands stack
             * stack invokes the command automaticaly */
            commandsStack.push(eraseNumberCommand);
        } else {
            emit viewMessage("Select a closed cell");
        }
    } else {
        emit viewMessage("Game over");
    }
}

void ClientViewModel::startNewGame(const QString &grid)
{
    m_game.setGrid(grid);
    m_game.startGame();
}

void ClientViewModel::handleNumberEntered(int number)
{
    if (m_game.gameState() == "Continues" && !m_isNoteMode) {
        if (isLastClickedCellAvailible()) {
            Cell *cell = m_game.grid().at(m_lastClickedCellIndex);
            int numberBeforeChanges = m_grid.at(m_lastClickedCellIndex) == " " ? 0 :
                m_grid.at(m_lastClickedCellIndex).toInt();
            // create a new EnterNumber command
            EnterNumber *enterNumberCommand = new EnterNumber(cell, number,
                numberBeforeChanges);
            /* push created command to the commands stack
             * stack invokes the command automaticaly */
            commandsStack.push(enterNumberCommand);
        } else {
            emit viewMessage("Select a closed cell");
        }
    } else if (m_isNoteMode) {
        if (isLastClickedCellAvailible()) {
            Cell *cell = m_game.grid().at(m_lastClickedCellIndex);
            QString displayData = m_grid.at(m_lastClickedCellIndex);

            if (displayData.length() < 9) {
                displayData = "     \n"
                              "     \n"
                              "     ";
            }

            // create a new EnterNumberInNoteMode command
            EnterNumberInNoteMode *enterNumberInNoteModeCommand =
                new EnterNumberInNoteMode(cell, number, displayData);
            commandsStack.push(enterNumberInNoteModeCommand);
        } else {
            emit viewMessage("Select a closed cell");
        }
    } else {
        emit viewMessage("Game over");
    }
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
    if (m_game.gameState() == "Win") {
        emit viewMessage("Congratulations :)");
    }
    emit gameStateChanged();
}

void ClientViewModel::onGridChanged(int index, const QString &displayData, bool isMistake)
{
    if (index > m_grid.count() - 1) {
        m_grid.append(displayData);
    } else {
        m_grid[index] = displayData;
    }

    emit lastClickedCellIndexChanged();
    // display cell with standard color
    emit gridChanged(index, isMistake ? "red" : "#18228f");
}

/*
 * PRIVATE METHODS
 */
bool ClientViewModel::isLastClickedCellAvailible()
{
    if (m_lastClickedCellIndex >= 0 && m_lastClickedCellIndex <= 80 &&
        !m_game.grid().at(m_lastClickedCellIndex)->isOpened()) {
        return true;
    }
    return false;
}
