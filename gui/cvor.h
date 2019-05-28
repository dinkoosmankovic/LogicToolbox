#ifndef CVOR_H
#define CVOR_H
#include <QGraphicsItem>
#include <QList>
#include <QString>
#include <QMap>
#include <iostream>


class Grana;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Cvor : public QGraphicsItem {
private:
    QList<Grana *> listaGrana;
    QList<QMap<QString, bool>> varijableSvjetova;
    QList<QString> dostizniSvjetovi;
    QString imeSvijeta;
    QPointF novaPozicija;
    GraphWidget *graf;

public:
    Cvor(GraphWidget *graphWidget);
    void ispisiVarijable();
    void dodajVarijablu (QMap<QString, bool>);
    void dodajGranu (Grana *grana);
    void postaviIme(QString ime);
    void dodajDostizniSvijet (QString imeSvijeta);
    void isprintajDostizne();
    QList<QString> vratiDostizne ();
    QList<Grana *> grane() const;
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
#endif // CVOR_H
