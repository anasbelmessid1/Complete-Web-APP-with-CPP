#include "hexgame.h"

extern hexgame* game;

hexagoneboard::hexagoneboard(){

}

QList<hexagone *> hexagoneboard::getHexes(){
    return hexes;
}

void hexagoneboard::placeHexes(int x, int y, int columns, int rows){
    int X_SH = 82;
    int Y_SH = 41;

    for (size_t i = 0, n = columns; i < n; i++){
        if (i % 2 == 0){ // even column
            Y_SH = 0;
        }
        else{ // odd column
            Y_SH = 41;
        }
        createHexColumn(x+X_SH*i,y+Y_SH,rows);
    }
}

void hexagoneboard::createHexColumn(int x, int y, int numOfRows){
    // creates a column of Hexes at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        hexagone* hexag = new hexagone();
        hexag->setPos(x,y+82*i);
        hexes.append(hexag);
        game->scene->addItem(hexag);
    }
}
