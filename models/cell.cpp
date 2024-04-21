#include "cell.h"

Cell::Cell(int number, int isOpened, int index) :
    m_number(number), m_isOpened(isOpened), m_index(index)
{}

Cell::Cell(const Cell &_) :
    m_number(_.number()), m_isOpened(_.isOpened()), m_index(_.index())
{}

/*
 * SETTERS
 */
void Cell::setIsOpened(bool isOpened, bool isTip) {
    // if the cell isn`t already opened
    if (!m_isOpened && isOpened) {
        m_isOpened = isOpened;
        emit isOpenedChanged(m_index, isTip);
    }
}

/*
 * PUBLIC METHODS
 */
void Cell::enterNumber(int number, bool isFromUndo)
{
    if (m_number != number) {
        emit incorrectNumberEntered(m_index, number, isFromUndo);
    } else {
        m_isOpened = true;
        emit isOpenedChanged(m_index, false);
    }
}

void Cell::setNoteModeNumbers(const QString &numbers)
{
    emit noteModeNumbersChanged(m_index, numbers);
}
