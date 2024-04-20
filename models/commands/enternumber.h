#ifndef ENTERNUMBER_H
#define ENTERNUMBER_H

#include <QObject>
#include <QUndoCommand>
#include "../cell.h"

class EnterNumber : public QUndoCommand
{
public:
    EnterNumber(Cell* cell, int numberToEnter, int numberBeforeChanges);

    void undo() override;
    void redo() override;

private:
    Cell *m_cell;
    int m_numberToEnter;
    int m_numberBeforeChanges;
};

#endif // ENTERNUMBER_H
