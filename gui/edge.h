#ifndef EDGE_H
#define EDGE_H
#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem {
public:
    Edge (Node *pocetniCvor, Node *krajnjiCvor);
    //GET
    Node *pocetniCvor() const;
    Node *krajnjiCvor() const;
    void popravi();
    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
     Node *pocetniC, *krajnjiC;
     QPointF pocetnaTacka;
     QPointF krajnjaTacka;
     qreal duzinaGrane;
};
#endif // EDGE_H
