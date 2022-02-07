#ifndef HEXAGONE_H
#define HEXAGONE_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class hexagone: public QGraphicsPolygonItem{
public:
    // Create constructors
    hexagone(QGraphicsItem* parent=NULL);
    //Create getters
    int getAttackOf(int theside);
    bool getIsPlaced();
    QString getOwner();

    //Create setters
    void setAttackOf(int theside, int theattack);
    void setOwner(QString player);
    void setIsPlaced(bool b);

    void displaySideAttacks();
    void createLines();
    void findNeighbors();
    void switchOwner();
    void captureNeighbors();

    //Add event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);


private:
    QList<QGraphicsLineItem*> lines;
    QList<hexagone*> neighbors;
    bool isPlaced;
    QString owner;
    int side0Attack;
    int side1Attack;
    int side2Attack;
    int side3Attack;
    int side4Attack;
    int side5Attack;
    QList<QGraphicsTextItem*> attackTexts;
};

#endif // HEXAGONE_H
