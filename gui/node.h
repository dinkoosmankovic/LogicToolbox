#ifndef NODE_H
#define NODE_H
#include <QGraphicsItem>
#include <QList>
#include <QString>
#include <QMap>
#include <iostream>


class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem {

private:
    QList<Edge *> edgesList;
    QList<QMap<QString, bool>> worldVariables; //Variables inside each world
    QList<QString> adjacentWorlds;
    QString worldName;
    QPointF newPosition;
    GraphWidget *graph;

public:
    Node(GraphWidget *graphWidget);
    void printVariables();
    void addVariable (QMap<QString, bool>);
    void addEdge(Edge *edge);
    void setName(QString name);
    void addAdjacentWorlds (QString imeSvijeta);
    void printAdjacentWorlds();
    QList<QString> getAdjacentWorlds();
    QList<Edge *> edges() const;
    enum { Type = UserType + 1};
    int type() const { return Type; }

    //Reimplementacija već postojećih metoda u baznoj klasi
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    //MOGU SE OBRISATI
    void calculateForces();
    bool advance();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

protected:
    QVariant itemChange(GraphicsItemChange promjena,const QVariant &vrijednost);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // NODE_H
