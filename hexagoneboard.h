#ifndef HEXAGONEBOARD_H
#define HEXAGONEBOARD_H
#include <QList>
#include "hexagone.h"

class hexagoneboard{
public:
    // constructors
   hexagoneboard();

    // getters/setters
    QList<hexagone*> getHexes();

    // public methods
    void placeHexes(int x, int y, int cols, int rows);

private:
    void createHexColumn(int x, int y, int numOfRows);
    QList<hexagone*> hexes;
};

#endif // HEXBOARD_H
