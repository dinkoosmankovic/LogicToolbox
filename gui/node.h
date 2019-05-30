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
    QList<QMap<QString, bool>> varijableSvjetova;
    QList<QString> dostizniSvjetovi;
    QString imeSvijeta;
    QPointF novaPozicija;
    GraphWidget *graf;

public:
    Node(GraphWidget *graphWidget);
    void ispisiVarijable();
    void dodajVarijablu (QMap<QString, bool>);
    void dodajGranu (Edge *edge);
    void postaviIme(QString ime);
    void dodajDostizniSvijet (QString imeSvijeta);
    void isprintajDostizne();
    QList<QString> vratiDostizne ();
    QList<Edge *> grane() const;
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
