#include "enternumberinnotemode.h"

EnterNumberInNoteMode::EnterNumberInNoteMode(Cell *cell, int numberToEnter,
    const QString &numbersBeforeChanges)
    : m_cell(cell), m_numberToEnter(numberToEnter),
    m_numbersBeforeChanges(numbersBeforeChanges)
{}

void EnterNumberInNoteMode::undo()
{
    if (!m_cell->isOpened()) {
        if (m_numbersBeforeChanges.length() > 1)
            m_cell->setNoteModeNumbers(m_numbersBeforeChanges);
        else
            m_cell->enterNumber(m_numbersBeforeChanges.toInt(), true);
    }
}

void EnterNumberInNoteMode::redo()
{
    QString numbers = m_numbersBeforeChanges;

    if (numbers.length() < 9) {
        numbers = "     \n"
                  "     \n"
                  "     ";
    }

    int cnt = -1;
    for (int i = 0; i < numbers.length(); i++) {
        if (i % 2 == 0) {
            cnt++;
            if (m_numberToEnter - 1 == cnt) {
                numbers[i] = numbers[i] == QChar(' ') ? QChar('0' + m_numberToEnter) : QChar(' ');
                m_cell->setNoteModeNumbers(numbers);
                return;
            }
        }
    }
}
