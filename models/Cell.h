#ifndef CELL_H
#define CELL_H

class Cell {
public:

    // cell position on board
    struct Position {
        int i;
        int j;
    };

    Cell(int number, bool isOpened, Position position) :
        number(number), isOpened(isOpened), position(position)
    {}
    Cell(const Cell &cell) :
        number(cell.number), isOpened(cell.isOpened), position(cell.position)
    {}

    /*
     * GETTERS
     */
    int getNumber() const { return number; }
    bool getOpenStatus() const { return isOpened; }
    Position getPosition() const { return position; }

    /*
     * SETTERS
     */
    void setNumber(int _number) { number = _number; }
    void setOpenStatus(bool _isOpened) { isOpened = _isOpened; }
    void setPosition(const Position &_position) { position = _position; }

private:
    int number;
    bool isOpened = false;
    Position position;
};

#endif // CELL_H
