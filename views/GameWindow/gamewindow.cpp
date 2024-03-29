#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameWindow)
    , listOfCells(81)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    addCellsFromGridToList(ui->grid1_9,   0, 0);
    addCellsFromGridToList(ui->grid10_18, 3, 0);
    addCellsFromGridToList(ui->grid19_27, 6, 0);
    addCellsFromGridToList(ui->grid28_36, 0, 27 );
    addCellsFromGridToList(ui->grid37_45, 3, 27);
    addCellsFromGridToList(ui->grid46_54, 6, 27);
    addCellsFromGridToList(ui->grid55_63, 0, 54);
    addCellsFromGridToList(ui->grid64_72, 3, 54);
    addCellsFromGridToList(ui->grid73_81, 6, 54);

    connectCellsInList();
}

GameWindow::~GameWindow()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void GameWindow::handleRedrawCell(int index, int number)
{
    listOfCells.at(index)->setIcon(QPixmap(":/icons/images/cell" + QString::number(number) + ".png"));
}

/*
 * PRIVATE METHODS
 */
void GameWindow::addCellsFromGridToList(QGridLayout *grid, int row_offset, int col_offset)
{
    int row = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            auto cell = qobject_cast<QPushButton*>(grid->itemAtPosition(i, j)->widget());
            if (cell) {
                listOfCells[i * 3 + j + row_offset + col_offset + row] = cell;
            } else {
                qDebug() << "Cell is nullptr after qobject_cast";
            }
        }
        row += 6;
    }
}

void GameWindow::connectCellsInList()
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            const auto &_ = listOfCells.at(row * 9 + col);
            connect(_, &QPushButton::clicked, this, [this, row, col] {
                emit cellClicked(row, col);
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
