#include <QPainter>
#include <math.h>
#include <iostream>
#include "node.h"
#include "edge.h"

static const double PI = 3.14159265358979323846264338327950288419717;
static double doublePI = 2.0 * PI;

Edge::Edge (Node *sourceNode, Node *destNode) : arrowSize(16) {
     setAcceptedMouseButtons(0);
     sourceN = sourceNode;
     destN = destNode;
     sourceN->addEdge(this);
     destN->addEdge(this);
     adjust();
}

Node *Edge::sourceNode() const {
    return sourceN;
}

Node *Edge::destNode() const {
    return destN;
}
void Edge::adjust()
{
    if (!sourceN || !destN) return;
    QLineF line(mapFromItem(sourceN, 0, 0), mapFromItem(destN, 0, 0));
    qreal length = line.length();
    prepareGeometryChange();
    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length); //20 is radius of the node
        sourcePoint = line.p1() + edgeOffset;
        destinationPoint = line.p2() - edgeOffset;
    }
    else {
        sourcePoint = destinationPoint = line.p1();
    }
}
QRectF Edge::boundingRect() const
{
    if (!sourceN || !destN) return QRectF();
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;
    return QRectF(sourcePoint, QSizeF(destinationPoint.x() - sourcePoint.x(), destinationPoint.y() - sourcePoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     if (!sourceN || !destN) return;

    QLineF line(sourcePoint, destinationPoint);
    if (qFuzzyCompare(line.length(), qreal(0.))) {
      //  std::cout << line.length()<<std::endl;
        return;
    }

    // Drawing lines
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    painter->drawLine(line);

    // Drawing arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0) angle = doublePI - angle;
    QPointF destinationArrowP1 = destinationPoint + QPointF(sin(angle - PI / 3) * arrowSize, cos(angle - PI / 3) * arrowSize);
    QPointF destinationArrowP2 = destinationPoint + QPointF(sin(angle - PI + PI / 3) * arrowSize, cos(angle - PI + PI / 3) * arrowSize);
    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destinationArrowP1 << destinationArrowP2);
}
