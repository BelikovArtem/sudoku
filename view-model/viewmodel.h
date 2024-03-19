#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItem>
#include <QJsonDocument>
#include <QJsonParseError>

class ViewModel
{
public:
    ViewModel();
    ~ViewModel();

    /*
     * PUBLIC METHODS
     */
    static void handleCellPressed(QPushButton* cell) {
        //QMessageBox::information(nullptr, "Success", "Cell was pressed");
        qDebug() << "Cell was pressed";
    }

private:



};

#endif // VIEWMODEL_H
