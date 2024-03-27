#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QGridLayout>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

signals:
    void cellClicked(QPushButton *cell);

private:
    Ui::GameWindow *ui;

    /*
     * PRIVATE METHODS
     */
    void connectCellsInGrid(QGridLayout *grid);
};

#endif // GAMEWINDOW_H
