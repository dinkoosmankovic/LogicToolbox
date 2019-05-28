#ifndef GRANA_H
#define GRANA_H
#include <QGraphicsItem>

class Cvor;

class Grana : public QGraphicsItem {
public:
    Grana (Cvor *pocetniCvor, Cvor *krajnjiCvor);
    //GET
    Cvor *pocetniCvor() const;
    Cvor *krajnjiCvor() const;
    void popravi();
    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
     Cvor *pocetniC, *krajnjiC;
     QPointF pocetnaTacka;
     QPointF krajnjaTacka;
     qreal duzinaGrane;
};
#endif // GRANA_H
