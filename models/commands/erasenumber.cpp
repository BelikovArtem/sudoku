#include "erasenumber.h"

EraseNumber::EraseNumber(Cell *cell, QString numberBeforeChanges) :
    m_cell(cell), m_numberBeforeChanges(numberBeforeChanges)
{}

void EraseNumber::undo()
{
    if (!m_cell->isOpened()) {
        if (m_numberBeforeChanges.length() > 1)
            m_cell->setNoteModeNumbers(m_numberBeforeChanges);
        else
            m_cell->enterNumber(m_numberBeforeChanges.toInt(), true);
    }
}

void EraseNumber::redo()
{
    m_cell->enterNumber(0, false);
}
