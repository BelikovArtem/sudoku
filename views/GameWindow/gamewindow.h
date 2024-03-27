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

public slots:
    void handleRedrawCell(QPushButton* cell, int number);

signals:
    void cellClicked(QPushButton *cell, int i, int j);
    void numberEntered(int number);

private slots:
    void on_number1_clicked();

    void on_number2_clicked();

    void on_number3_clicked();

    void on_number4_clicked();

    void on_number5_clicked();

    void on_number6_clicked();

    void on_number7_clicked();

    void on_number8_clicked();

    void on_number9_clicked();

private:
    Ui::GameWindow *ui;
    QList<QPushButton*> listOfCells;

    /*
     * PRIVATE METHODS
     */
    void addCellsFromGridToList(QGridLayout *grid);
    void connectCellsInList();
};

#endif // GAMEWINDOW_H
