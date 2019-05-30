#include "node.h"
#include "edge.h"
#include <QPainter>
#include <math.h>
#include <iostream>

static const double PI = 3.14159265358979323846264338327950288419717;
static double dvaPI = 2.0 * PI;

Edge::Edge (Node *pocetniCvor, Node *krajnjiCvor) : duzinaGrane(10) {
     setAcceptedMouseButtons(0);
     pocetniC = pocetniCvor;
     krajnjiC = krajnjiCvor;
     pocetniC->dodajGranu(this);
     krajnjiC->dodajGranu(this);
     popravi();
}

Node *Edge::pocetniCvor() const {
    return pocetniC;
}

Node *Edge::krajnjiCvor() const {
    return krajnjiC;
}
void Edge::popravi()
{
    if (!pocetniC || !krajnjiC)
        return;
    QLineF linija(mapFromItem(pocetniC, 0, 0), mapFromItem(krajnjiC, 0, 0));
    qreal duzina = linija.length();
    prepareGeometryChange();
    if (duzina > qreal(20.)) {
        QPointF edgeOffset((linija.dx() * 10) / duzina, (linija.dy() * 10) / duzina);
        pocetnaTacka = linija.p1() + edgeOffset;
        krajnjaTacka = linija.p2() - edgeOffset;
    }
    else {
        pocetnaTacka = krajnjaTacka = linija.p1();
    }
}
QRectF Edge::boundingRect() const
{
    if (!pocetniC || !krajnjiC)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + duzinaGrane) / 2.0;

    return QRectF(pocetnaTacka, QSizeF(krajnjaTacka.x() - pocetnaTacka.x(),
                                      krajnjaTacka.y() - pocetnaTacka.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!pocetniC || !krajnjiC)
        return;

    QLineF line(pocetnaTacka, krajnjaTacka);
    if (qFuzzyCompare(line.length(), qreal(0.))) {
      //  std::cout << line.length()<<std::endl;
        return;
    }

    // Crtanje linije
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    painter->drawLine(line);

    // Crtanje strelica
    double ugao = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        ugao = dvaPI - ugao;

  /*  QPointF izvorisnaStrelicaP1 = pocetnaTacka + QPointF(sin(ugao + PI / 3) * duzinaGrane,
                                                  cos(ugao + PI / 3) * duzinaGrane);
    QPointF izvorisnaStrelicaP2 = pocetnaTacka + QPointF(sin(ugao + PI - PI / 3) * duzinaGrane,
                                                  cos(ugao + PI - PI / 3) * duzinaGrane);*/
    QPointF odredisnaStrelicaP1 = krajnjaTacka + QPointF(sin(ugao - PI / 3) * duzinaGrane,
                                              cos(ugao - PI / 3) * duzinaGrane);
    QPointF odredisnaStrelicaP2 = krajnjaTacka + QPointF(sin(ugao - PI + PI / 3) * duzinaGrane,
                                              cos(ugao - PI + PI / 3) * duzinaGrane);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << odredisnaStrelicaP1 << odredisnaStrelicaP2);
}
