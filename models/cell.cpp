#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject{parent}
{}

Cell::Cell(int number, int isOpened, int index) :
    m_number(number), m_isOpened(isOpened), m_index(index)
{}

Cell::Cell(const Cell &_) :
    m_number(_.getNumber()), m_isOpened(_.getIsOpened()), m_index(_.index())
{}

void Cell::setNumber(int number) {
    if (m_number != number && !m_isOpened) {
        m_number = number;
    }
}

void Cell::setIsOpened(bool isOpened) {
    if (!m_isOpened && isOpened) {
        m_isOpened = isOpened;
    }
}
