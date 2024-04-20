#include "enternumberinnotemode.h"

EnterNumberInNoteMode::EnterNumberInNoteMode(Cell *cell, int numberToEnter,
    const QString &numbersBeforeChanges)
    : m_cell(cell), m_numberToEnter(numberToEnter),
    m_numbersBeforeChanges(numbersBeforeChanges)
{}

void EnterNumberInNoteMode::undo()
{
    m_cell->setNoteModeNumbers(m_numbersBeforeChanges);
}

void EnterNumberInNoteMode::redo()
{
    QString numbers = m_numbersBeforeChanges;

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
