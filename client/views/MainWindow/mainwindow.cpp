#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    connectCellsInGrid(ui->grid1_9);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * PRIVATE METHODS
 */
void MainWindow::connectCellsInGrid(QGridLayout *grid)
{
    for (int i = 0; i < grid->count(); i++) {
        auto cell = qobject_cast<QPushButton*>(grid->itemAt(i)->widget());
        if (cell)
            connect(cell, &QPushButton::clicked, [cell](){ ViewModel::handleCellPressed(cell); });
        else
            qDebug() << "Cell is nullptr after qobject_cast";
    }
}
