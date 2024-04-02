#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT

public:
    Cell(int number, int isOpened, int index);
    explicit Cell(QObject *parent = nullptr);
    Cell(const Cell &_);

    /*
     * SETTERS / GETTERS
     */
    int getNumber() const { return m_number; }
    void setNumber(int number);

    bool getIsOpened() const { return m_isOpened; }
    void setIsOpened(bool isOpened);

    int index() const { return m_index; }

signals:
    void numberChanged();
    void isOpenedChanged();

private:
    int m_index;
    int m_number;
    bool m_isOpened;
};

#endif // CELL_H
