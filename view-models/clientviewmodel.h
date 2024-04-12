#ifndef CLIENTVIEWMODEL_H
#define CLIENTVIEWMODEL_H

#include "models/game.h"
#include <QObject>
#include <QQuickView>

class ClientViewModel : public QObject
{

    Q_OBJECT
    Q_PROPERTY(long time READ time NOTIFY timeChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)
    Q_PROPERTY(QStringList grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(int mistakes READ mistakes NOTIFY mistakesChanged)
    Q_PROPERTY(QString gameState READ gameState WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(int lastClickedCellIndex READ lastClickedCellIndex WRITE setLastClickedCellIndex NOTIFY lastClickedCellIndexChanged)
    Q_PROPERTY(QString difficultyLevel READ difficultyLevel WRITE setDifficultyLevel NOTIFY difficultyLevelChanged)

public:
    explicit ClientViewModel(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    long time() const { return m_game.time(); }
    int score() const { return m_game.score(); }
    QStringList grid() const { return m_grid; }
    int mistakes() const { return m_game.mistakes(); }
    QString gameState() const { return m_game.gameState(); }
    QString difficultyLevel() const { return m_game.difficultyLevel(); }
    int lastClickedCellIndex() const { return m_lastClickedCellIndex; }

    /*
     * SETTERS
     */
    void setLastClickedCellIndex(int index);
    void setGameState(const QString &gameState);
    void setDifficultyLevel(const QString &difficultyLevel);

    /*
     * AVAILIBLE FROM UI
     */
    Q_INVOKABLE void handleUndo();
    Q_INVOKABLE void handleEraseCell();
    Q_INVOKABLE void handleCellClicked(int index);
    Q_INVOKABLE void handleNumberEntered(int number);
    Q_INVOKABLE void startNewGame(const QString &grid);

signals:
    void gridChanged();
    void timeChanged();
    void scoreChanged();
    void mistakesChanged();
    void gameStateChanged();
    void difficultyLevelChanged();
    void lastClickedCellIndexChanged();
    void viewMessage(const QString &message);

public slots:
    /*
     * FOR SIGNALS FROM MODEL
     */
    void onGridChanged(int index);
    void onTimerChanged();
    void onLevelChanged();
    void onScoreChanged();
    void onMistakesChanged();
    void onGameStateChanged();

private:
    Game m_game;
    QStringList m_grid;

    int m_lastClickedCellIndex = -1;
};

#endif // CLIENTVIEWMODEL_H
