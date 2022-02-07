#ifndef HEXGAME_H
#define HEXGAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
// #include "HexBoard.h"
#include "hexagoneboard.h"
#include <QMouseEvent>

class hexgame: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    hexgame(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);
    void pickUpCard(hexagone* card);
    void placeCard(hexagone* hexToReplace);
    void nextPlayersTurn();
    void removeFromDeck(hexagone *card,QString player);
    void hexgameOver();
    void displayhexgameOverWindow(QString textToDisplay);

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    // public attributes
    QGraphicsScene* scene;
    hexagoneboard* hexBoard;
    hexagone* cardToPlace;
    QPointF originalPos;
    int numCardsPlaced;

public slots:
    void start();
    void restarthexgame();

private:
    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(QString player);
    void createInitialCards();
    void drawCards();

    // private attributes
    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<hexagone* > player1Cards;
    QList<hexagone* > player2Cards;
};

#endif // hexgame_H
