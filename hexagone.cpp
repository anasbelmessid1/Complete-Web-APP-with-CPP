
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "hexgame.h"

extern hexgame* game;

#include <QDebug> // remove TODO
hexagone::hexagone(QGraphicsItem *parent){

    //Use the points: (1,0), (1,2), (2,0), (2,2), (3,1) and (0,1) to draw the hexagon
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    // Scale the points by 40
    int SCALE_BY = 40;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // Use the scaled points to create the hexagone
    QPolygonF hexagon(hexPoints);

    // Draw the hexagone
    setPolygon(hexagon);

    // Initialize
    isPlaced = false;

    // Create lines
    createLines();

    // Initializing side attacks to 0
    side0Attack = 0;
    side1Attack = 0;
    side2Attack = 0;
    side3Attack = 0;
    side4Attack = 0;
    side5Attack = 0;

    // Create QGraphicsTextItems to represent visually each side's attack
    QGraphicsTextItem* text0 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text1 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text2 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text3 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text4 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem* text5 = new QGraphicsTextItem(QString::number(0),this);

    attackTexts.append(text0);
    attackTexts.append(text1);
    attackTexts.append(text2);
    attackTexts.append(text3);
    attackTexts.append(text4);
    attackTexts.append(text5);

    // Set the position of every attack text
    text0->setPos(50,0);
    text1->setPos(20,15);
    text2->setPos(20,40);
    text3->setPos(50,55);
    text4->setPos(80,40);
    text5->setPos(80,15);

    // Make all attacks texts invisible
    for (size_t i = 0, n = attackTexts.size(); i < n; i++){
        attackTexts[i]->setVisible(false);
    }
}

int hexagone::getAttackOf(int theside){
    if (theside == 0){
        return side0Attack;
    }
    else if (theside == 1){
        return side1Attack;
    }
    else if (theside == 2){
        return side2Attack;
    }
    else if (theside == 3){
        return side3Attack;
    }
    else if (theside == 4){
        return side4Attack;
    }
    else if (theside == 5){
        return side5Attack;
    }
}

bool hexagone::getIsPlaced(){
    return isPlaced;
}

QString hexagone::getOwner(){
    return owner;
}

void hexagone::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // Case of the hexagone is not placed (in this case called a card) then pick it up
    if (getIsPlaced() == false){
        game->pickUpCard(this);
    }

    // Otherwise (the hexagone is placed),replace it
    else {
        game->placeCard(this);
    }
}

void hexagone::setAttackOf(int theside, int theattack){
    // We set the attack of the specified side and modify it's text
    switch (theside){
    case 0:
        side0Attack = theattack;
        attackTexts[0]->setPlainText(QString::number(theattack));
    case 1:
        side1Attack = theattack;
        attackTexts[1]->setPlainText(QString::number(theattack));
    case 2:
        side2Attack = theattack;
        attackTexts[2]->setPlainText(QString::number(theattack));
    case 3:
        side3Attack = theattack;
        attackTexts[3]->setPlainText(QString::number(theattack));
    case 4:
        side4Attack = theattack;
        attackTexts[4]->setPlainText(QString::number(theattack));
    case 5:
        side5Attack = theattack;
        attackTexts[5]->setPlainText(QString::number(theattack));
    }
}

void hexagone::setOwner(QString player){
    // Set the owner (player)
    owner = player;

    // We have to change the color of hexagones
    if (player == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if (player == QString("PLAYER1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if (player == QString("PLAYER2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void hexagone::setIsPlaced(bool b){
    isPlaced = b;
}

void hexagone::displaySideAttacks(){
    // Make all the side attacks texts visible
    for (size_t i = 0, n = attackTexts.size(); i < n; i++){
        attackTexts[i]->setVisible(true);
    }
}

void hexagone::createLines(){
    QPointF hexCenter(x()+60,y()+40);
    QPointF finalPt(hexCenter.x(),hexCenter.y()-65);
    QLineF ln(hexCenter,finalPt);

    for (size_t i = 0, n = 6; i < n; ++i){
        QLineF lnCopy(ln);
        lnCopy.setAngle(90+60*i);
        QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy,this);
        lines.append(line);
        line->setVisible(false);
    }
}

void hexagone::findNeighbors(){
    for (size_t i = 0, n = lines.size(); i < n; i++){
        // if the line collides with an item of type Hex, add it to neighbors
        QList<QGraphicsItem*> cItems = lines[i]->collidingItems();
        for (size_t j = 0; j < cItems.size(); j++){
            hexagone* item = dynamic_cast<hexagone*>(cItems[j]);
            if (cItems[j] != this && item){
                neighbors.append(item);
            }
        }
    }
}

void hexagone::switchOwner(){
    //In case of the owner is player1, change it to player2 and vice versa
    if (getOwner() == QString("PLAYER1")){
        setOwner(QString("PLAYER2"));
    }
    else if (getOwner() == QString("PLAYER2")){
        setOwner(QString("PLAYER1"));
    }
}

void hexagone::captureNeighbors(){
    // Captures weaker neighbors
    for (size_t i = 0, n = neighbors.size(); i < n; i++){
        bool isEnemy = false;
        bool isNotNeutral = false;

        if (this->getOwner() != neighbors[i]->getOwner()){
            isEnemy = true;
        }

        if (neighbors[i]->owner != QString("NOONE")){
            isNotNeutral = true;
        }

        // This is an enemy and not neutral
        if (isEnemy && isNotNeutral){
            // Find attack of touching sides
            int thisAttack = 0;
            int neighborsAttack = 0;
            if (i == 0){
                thisAttack = getAttackOf(0);
                neighborsAttack = neighbors[0]->getAttackOf(3);
            }
            else if (i == 1){
                thisAttack = getAttackOf(1);
                neighborsAttack = neighbors[1]->getAttackOf(4);
            }
            else if (i == 2){
                thisAttack = getAttackOf(2);
                neighborsAttack = neighbors[2]->getAttackOf(5);
            }
            else if (i == 3){
                thisAttack = getAttackOf(3);
                neighborsAttack = neighbors[3]->getAttackOf(0);
            }
            else if (i == 4){
                thisAttack = getAttackOf(4);
                neighborsAttack = neighbors[4]->getAttackOf(1);
            }
            else if (i == 5){
                thisAttack = getAttackOf(5);
                neighborsAttack = neighbors[5]->getAttackOf(2);
            }

            // The one who has greater attack, we will Change the player
            if (thisAttack > neighborsAttack){
                neighbors[i]->switchOwner();
            }

        }
    }
}
