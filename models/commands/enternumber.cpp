#include "enternumber.h"

EnterNumber::EnterNumber(Cell *cell, int numberToEnter, int numberBeforeChanges) :
    m_cell(cell), m_numberToEnter(numberToEnter),
        m_numberBeforeChanges(numberBeforeChanges)
{}

void EnterNumber::undo()
{
    if (!m_cell->isOpened())
        m_cell->enterNumber(m_numberBeforeChanges, true);
}

void EnterNumber::redo()
{
    m_cell->enterNumber(m_numberToEnter, false);
}
