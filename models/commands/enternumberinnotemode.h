#ifndef ENTERNUMBERINNOTEMODE_H
#define ENTERNUMBERINNOTEMODE_H

#include "../cell.h"
#include <QUndoCommand>

class EnterNumberInNoteMode : public QUndoCommand
{
public:
    EnterNumberInNoteMode(Cell *cell, int numberToEnter,
                          const QString &numbersBeforeChanges);
    void undo() override;
    void redo() override;

private:
    Cell* m_cell;
    int m_numberToEnter;
    QString m_numbersBeforeChanges;
};

#endif // ENTERNUMBERINNOTEMODE_H
