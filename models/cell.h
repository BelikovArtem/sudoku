#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT

public:
    Cell(const Cell &_);
    Cell(int number, int isOpened, int index);

    /*
     * GETTERS
     */
    int index() const { return m_index; }
    int number() const { return m_number; }
    bool isOpened() const { return m_isOpened; }

    /*
     * SETTERS
     */
    // performs cell opening
    void setIsOpened(bool isOpened);

    /*
     * PUBLIC METHODS
     */
    void enterNumber(int number, bool isFromUndo);
    void setNoteModeNumbers(const QString &numbers);

private:
    int m_index;
    int m_number;
    bool m_isOpened;

signals:
    void isOpenedChanged(int index);
    void noteModeNumbersChanged(int index, const QString &numbers);
    void incorrectNumberEntered(int index, int number, bool isFromUndo);
};

#endif // CELL_H
