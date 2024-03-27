#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    connectCellsInGrid(ui->grid1_9);
    connectCellsInGrid(ui->grid10_18);
    connectCellsInGrid(ui->grid19_27);
    connectCellsInGrid(ui->grid28_36);
    connectCellsInGrid(ui->grid37_45);
    connectCellsInGrid(ui->grid46_54);
    connectCellsInGrid(ui->grid55_63);
    connectCellsInGrid(ui->grid64_72);
    connectCellsInGrid(ui->grid73_81);
}

GameWindow::~GameWindow()
{
    delete ui;
}

/*
 * PRIVATE METHODS
 */
void GameWindow::connectCellsInGrid(QGridLayout *grid)
{
    for (int i = 0; i < grid->count(); i++) {
        auto cell = qobject_cast<QPushButton*>(grid->itemAt(i)->widget());
        if (cell) {
            connect(cell, &QPushButton::clicked, this, [this, cell] {
                emit cellClicked(cell);
            });
        } else {
            qDebug() << "Cell is nullptr after qobject_cast";
        }
    }
}

/*
 * SLOTS
 */
void cellClicked(int index)
{


}
