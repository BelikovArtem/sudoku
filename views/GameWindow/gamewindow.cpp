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

    addCellsFromGridToList(ui->grid1_9);
    addCellsFromGridToList(ui->grid10_18);
    addCellsFromGridToList(ui->grid19_27);
    addCellsFromGridToList(ui->grid28_36);
    addCellsFromGridToList(ui->grid37_45);
    addCellsFromGridToList(ui->grid46_54);
    addCellsFromGridToList(ui->grid55_63);
    addCellsFromGridToList(ui->grid64_72);
    addCellsFromGridToList(ui->grid73_81);

    connectCellsInList();
}

GameWindow::~GameWindow()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void GameWindow::handleRedrawCell(QPushButton* cell, int number)
{
    switch (number) {
    case 0:
        cell->setIcon(QPixmap(":/icons/images/rectangle.png"));
        break;
    default:
        cell->setIcon(QPixmap(":/icons/images/cell" + QString::number(number) + ".png"));
        break;
    }
}

/*
 * PRIVATE METHODS
 */
void GameWindow::addCellsFromGridToList(QGridLayout *grid)
{
    for (int i = 0; i < grid->count(); i++) {
        auto cell = qobject_cast<QPushButton*>(grid->itemAt(i)->widget());
        if (cell) {
            listOfCells.append(cell);
        } else {
            qDebug() << "Cell is nullptr after qobject_cast";
        }
    }
}

void GameWindow::connectCellsInList()
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            const auto &_ = listOfCells.at(row * 9 + col);
            connect(_, &QPushButton::clicked, this, [this, _, row, col] {
                emit cellClicked(_, row, col);
            });
        }
    }
}

/*
 * PRIVATE SLOTS
 */
void GameWindow::on_number1_clicked()
{
    emit numberEntered(1);
}

void GameWindow::on_number2_clicked()
{
    emit numberEntered(2);
}

void GameWindow::on_number3_clicked()
{
    emit numberEntered(3);
}

void GameWindow::on_number4_clicked()
{
    emit numberEntered(4);
}

void GameWindow::on_number5_clicked()
{
    emit numberEntered(5);
}

void GameWindow::on_number6_clicked()
{
    emit numberEntered(6);
}

void GameWindow::on_number7_clicked()
{
    emit numberEntered(7);
}

void GameWindow::on_number8_clicked()
{
    emit numberEntered(8);
}

void GameWindow::on_number9_clicked()
{
    emit numberEntered(9);
}
