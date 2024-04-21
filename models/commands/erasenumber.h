#ifndef ERASENUMBER_H
#define ERASENUMBER_H

#include <QObject>
#include <QUndoCommand>
#include "../cell.h"

class EraseNumber : public QUndoCommand
{
public:
    EraseNumber(Cell *cell, QString numberBeforeChanges);
    void undo() override;
    void redo() override;

private:
    Cell *m_cell;
    QString m_numberBeforeChanges;
};

#endif // ERASENUMBER_H
