#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QMessageBox>
#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QString>
#include <QList>
#include <QTextEdit>
#include <QLabel>
#include <QFont>
#include <QMap>
#include <QDebug>
#include <QPen>
#include <QLinearGradient>
#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

/*TODO
  PREPRAVITI SVE GETTER-E NA CONST ------ ZA SVAKU KLASU
 */

Node::Node(GraphWidget *graphWidget) : graph(graphWidget) {
    radius = 20;
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setFlag(ItemIsMovable); //Moving nodes
    setFlag(ItemSendsGeometryChanges);
}

void Node::addEdge(Edge *edge) {
    edgesList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const {
    return edgesList;
}

QRectF Node::boundingRect() const
{
   return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}


QPainterPath Node::shape() const
{
    QPainterPath temp;
    temp.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    return temp;
}

//Changing node color
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse( radius - 3, radius - 3, 2 * radius, 2 * radius );
    QRadialGradient gradient(-3, -3, radius);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::black).light(120));
        gradient.setColorAt(0, QColor(Qt::darkRed).light(120));
    }
    else {
        gradient.setColorAt(0, Qt::black);
        gradient.setColorAt(1, Qt::darkRed);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse( -radius, -radius, 2 * radius, 2 * radius );
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgesList)
            edge->adjust();
        graph->moving();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

bool Node::advance()
{
    if (newPosition == pos()) return false;
    setPos(newPosition);
    return true;
}


void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPosition = pos();
        return;
    }

    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node) continue;
        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }

    // Now subtract all forces pulling items together
    double weight = (edgesList.size() + 1) * 10;
    foreach (Edge *edge, edgesList) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->sourceNode(), 0, 0);
        else
            vec = mapToItem(edge->destNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    newPosition = pos() + QPointF(xvel, yvel);
    newPosition.setX(qMin(qMax(newPosition.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPosition.setY(qMin(qMax(newPosition.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("World  \"" + this->worldName + "\" ");
    wdg->resize(200, 200);
    QString temp;
    for (QMap<QString, bool> mapa : this->worldVariables) {
        QMap<QString, bool>::iterator i;
        for (i = mapa.begin(); i != mapa.end(); ++i) {
            QString varijabla = i.key();
            QString vrijednost;
            if (i.value()) vrijednost = "True";
            else vrijednost = "False";
            temp += " " + varijabla + " : " + vrijednost + "\n";
        }
    }
    QLabel *label = new QLabel(wdg);
    QFont f("Times New Roman", 18, QFont::Bold);
    label->setFont(f);
    label->setText(temp);
    label->setAlignment(Qt::AlignCenter); //NE CENTRIRA ''''
    wdg->show();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::addVariable (QMap<QString, bool> var) {
    worldVariables.append(var);
}

void Node::printVariables() {
    for (int i = 0; i<worldVariables.length(); i++) {
       // std::cout << worldVariables[i].toStdString()<< std::endl;
    }
}

void Node::setName(QString name) {
    worldName = name;
}

void Node::addAdjacentWorlds (QString worldName) {
    adjacentWorlds.append(worldName);
}

void Node::printAdjacentWorlds() {
    for (int i = 0; i<this->adjacentWorlds.count(); i++) {
         std::cout << adjacentWorlds[i].toStdString() << std::endl;
    }
}

QList<QString> Node::getAdjacentWorlds() {
    return this->adjacentWorlds;
}
