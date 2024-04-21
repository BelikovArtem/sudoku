#include "enternumber.h"

EnterNumber::EnterNumber(Cell *cell, int numberToEnter, QString dataBeforeChanges) :
    m_cell(cell), m_numberToEnter(numberToEnter),
    m_dataBeforeChanges(dataBeforeChanges)
{}

void EnterNumber::undo()
{
    if (!m_cell->isOpened()) {
        if (m_dataBeforeChanges.length() > 1)
            m_cell->setNoteModeNumbers(m_dataBeforeChanges);
        else
            m_cell->enterNumber(m_dataBeforeChanges.toInt(), false);
    }
}

void EnterNumber::redo()
{
    m_cell->enterNumber(m_numberToEnter, false);
}
