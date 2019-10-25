//
// Created by Alma Ibrašimović, january 2019.
//

#ifndef NODE_H
#define NODE_H
#include <QGraphicsItem>
#include <QList>
#include <QString>
#include <QMap>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRect>
#include <QObject>
#include <QLabel>
#include <QPointF>
#include <QLineEdit>

#include "../include/CoreEvaluator.h"
#include "../include/ResultTree.h"

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QObject, public QGraphicsItem{
     Q_OBJECT

private:
    QList<Edge *> edgesList;
    QList<QMap<QString, bool>> worldVariables; //Variables inside each world
    QList<QString> adjacentWorlds;
    QString worldName;
    QPointF newPosition;
    GraphWidget *graphA;
    QString path;
    QPointF position;
    QWidget *widget;
    QLineEdit *lineA;
    QLineEdit *lineB;
    QList<QString> variableNames;
    int radius;

public:
    enum { Type = UserType + 1};
    int type() const { return Type; }
    Node(GraphWidget *graphWidget, QString path = "UniverseConfig.json");
    QList<QString> getVariables() const;
    void addVariable (QMap<QString, bool>);
    void addEdge(Edge *edge);
    void setName(QString name);
    void addAdjacentWorlds (QString imeSvijeta);
    void printAdjacentWorlds();
    QList<QString> getAdjacentWorlds();
    QList<Edge *> edges() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void calculateForces();
    bool advance();
    QList<QMap<string,char*>> getResults() const;
    QPointF getPosition() const { return position; }
    void setPosition(QPointF pos) { position = pos; }
    void setVariableNames(QString name) { variableNames.append(name); }
    QList<QString> getVariableNames() const { return variableNames; }

protected:
    QVariant itemChange(GraphicsItemChange promjena,const QVariant &vrijednost);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private slots:
    void changeValue();
    void listValue();
};
#endif // NODE_H
