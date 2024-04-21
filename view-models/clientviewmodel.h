#ifndef CLIENTVIEWMODEL_H
#define CLIENTVIEWMODEL_H

#include "models/game.h"
#include "models/commands/enternumber.h"
#include "models/commands/erasenumber.h"
#include "models/commands/enternumberinnotemode.h"

#include <QObject>
#include <QUndoStack>

class ClientViewModel : public QObject
{

    Q_OBJECT
    Q_PROPERTY(long time READ time NOTIFY timeChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)
    Q_PROPERTY(QStringList grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(int mistakes READ mistakes NOTIFY mistakesChanged)
    Q_PROPERTY(bool isNoteMode READ isNoteMode WRITE setNoteMode NOTIFY isNoteModeChanged)
    Q_PROPERTY(QString gameState READ gameState WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString difficultyLevel READ difficultyLevel WRITE setDifficultyLevel NOTIFY difficultyLevelChanged)
    Q_PROPERTY(int lastClickedCellIndex READ lastClickedCellIndex WRITE setLastClickedCellIndex NOTIFY lastClickedCellIndexChanged)

public:
    explicit ClientViewModel(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    long time() const { return m_game.time(); }
    QStringList grid() const { return m_grid; }
    int score() const { return m_game.score(); }
    bool isNoteMode() const { return m_isNoteMode; }
    int mistakes() const { return m_game.mistakes(); }
    QString gameState() const { return m_game.gameState(); }
    int lastClickedCellIndex() const { return m_lastClickedCellIndex; }
    QString difficultyLevel() const { return m_game.difficultyLevel(); }

    /*
     * SETTERS
     */
    void setNoteMode(bool value);
    void setLastClickedCellIndex(int index);
    void setGameState(const QString &gameState);
    void setDifficultyLevel(const QString &difficultyLevel);

    /*
     * AVAILIBLE FROM UI
     */
    Q_INVOKABLE void handleUndo();
    Q_INVOKABLE void handleEraseCell();
    Q_INVOKABLE void handleNumberEntered(int number);
    Q_INVOKABLE void startNewGame(const QString &grid);

signals:
    void gridChanged(int index, QString color);
    void timeChanged();
    void scoreChanged();
    void mistakesChanged();
    void gameStateChanged();
    void isNoteModeChanged();
    void difficultyLevelChanged();
    void lastClickedCellIndexChanged();
    void viewMessage(const QString &message);

public slots:
    /*
     * FOR SIGNALS FROM MODEL
     */
    void onTimerChanged();
    void onLevelChanged();
    void onScoreChanged();
    void onMistakesChanged();
    void onGameStateChanged();
    void onGridChanged(int index, const QString &data, bool isMistake);

private:
    Game m_game;
    QStringList m_grid;
    QUndoStack commandsStack;

    bool m_isNoteMode = false;
    int m_lastClickedCellIndex = -1;

    /*
     * PRIVATE METHODS
     */
    bool isLastClickedCellAvailible();
};

#endif // CLIENTVIEWMODEL_H
