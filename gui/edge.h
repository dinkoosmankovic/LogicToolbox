#ifndef EDGE_H
#define EDGE_H
#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem {
public:
    Edge (Node *sourceNode, Node *destNode);
    //GET
    Node *sourceNode() const;
    Node *destNode() const;
    void adjust();
    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
     Node *sourceN, *destN;
     QPointF sourcePoint;
     QPointF destinationPoint;
     qreal arrowSize;
};
#endif // EDGE_H
