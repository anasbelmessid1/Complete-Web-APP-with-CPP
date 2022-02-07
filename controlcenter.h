#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include  <QGraphicsSceneHoverEvent>

class controlcenter:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // Create a constructor
    controlcenter(QString name, QGraphicsItem* parent=NULL);

    // Create public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // CONTROLCENTER_H
