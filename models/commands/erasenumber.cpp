#include "erasenumber.h"

EraseNumber::EraseNumber(Cell *cell, int numberBeforeChanges) :
    m_cell(cell), m_numberBeforeChanges(numberBeforeChanges)
{}

void EraseNumber::undo()
{
    if (!m_cell->isOpened())
        m_cell->enterNumber(m_numberBeforeChanges, true);
}

void EraseNumber::redo()
{
    m_cell->enterNumber(0, false);
}
