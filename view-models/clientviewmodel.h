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
    Q_PROPERTY(QVariantList grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(int mistakes READ mistakes NOTIFY mistakesChanged)
    Q_PROPERTY(QString gameState READ gameState WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString difficultyLevel READ difficultyLevel WRITE setDifficultyLevel NOTIFY difficultyLevelChanged)

public:
    explicit ClientViewModel(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    long time() const { return m_game.time(); }
    int score() const { return m_game.score(); }
    QVariantList grid() const { return m_grid; }
    int mistakes() const { return m_game.mistakes(); }
    QString gameState() const { return m_game.gameState(); }
    QString difficultyLevel() const { return m_game.difficultyLevel(); }

    /*
     * SETTERS
     */
    void setGameState(const QString &gameState);
    void setDifficultyLevel(const QString &difficultyLevel);

    /*
     * AVAILIBLE FROM UI
     */
    Q_INVOKABLE void startNewGame();

signals:
    void gridChanged();
    void timeChanged();
    void scoreChanged();
    void mistakesChanged();
    void gameStateChanged();
    void difficultyLevelChanged();

public slots:
    /*
     * FOR SIGNALS FROM MODEL
     */
    void onGridChanged();
    void onTimerChanged();
    void onLevelChanged();
    void onScoreChanged();
    void onMistakesChanged();
    void onGameStateChanged();

private:
    Game m_game;
    QVariantList m_grid;
};

#endif // CLIENTVIEWMODEL_H
