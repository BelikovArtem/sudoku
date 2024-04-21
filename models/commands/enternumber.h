#ifndef ENTERNUMBER_H
#define ENTERNUMBER_H

#include <QObject>
#include <QUndoCommand>
#include "../cell.h"

class EnterNumber : public QUndoCommand
{
public:
    EnterNumber(Cell* cell, int numberToEnter, QString dataBeforeChanges);

    void undo() override;
    void redo() override;

private:
    Cell *m_cell;
    int m_numberToEnter;
    QString m_dataBeforeChanges;
};

#endif // ENTERNUMBER_H
