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
#include "grana.h"
#include "cvor.h"
#include "graphwidget.h"
#include "mainwindow.h"


/*TODO
  POVEĆATI VELIČINU ELIPSE
 */

Cvor::Cvor(GraphWidget *graphWidget) : graf(graphWidget) {

    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setFlag(ItemIsMovable); //POMJERANJE
    setFlag(ItemSendsGeometryChanges);
}

void Cvor::dodajGranu(Grana *grana) {
    listaGrana << grana;
    grana->popravi();
}

QList<Grana *> Cvor::grane() const {
    return listaGrana;
}

QRectF Cvor::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -10 - adjust,23 + adjust, 23 + adjust);
}

QPainterPath Cvor::shape() const
{
    QPainterPath temp;
    temp.addEllipse(-10, -10, 30, 30);
    return temp;
}

//Mijenjanje boje čvorova
void Cvor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    //Sunken stanje je stanje kad se klikne na čvor pa da se ilustrira kao da "potonuo" čvor
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        //Centar se pomjera da se ilustrira da je "sunken", odnosno da se zna da je klik
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
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Cvor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Grana *edge, listaGrana)
            edge->popravi();
        graf->pomjeranje();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

bool Cvor::advance()
{
    if (novaPozicija == pos())
        return false;

    setPos(novaPozicija);
    return true;
}


void Cvor::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        novaPozicija = pos();
        return;
    }

    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        Cvor *node = qgraphicsitem_cast<Cvor *>(item);
        if (!node)
            continue;

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
    double weight = (listaGrana.size() + 1) * 10;
    foreach (Grana *edge, listaGrana) {
        QPointF vec;
        if (edge->pocetniCvor() == this)
            vec = mapToItem(edge->pocetniCvor(), 0, 0);
        else
            vec = mapToItem(edge->krajnjiCvor(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    novaPozicija = pos() + QPointF(xvel, yvel);
    novaPozicija.setX(qMin(qMax(novaPozicija.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    novaPozicija.setY(qMin(qMax(novaPozicija.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

void Cvor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("World  \"" + this->imeSvijeta + "\" ");
    wdg->resize(200, 200);
    QString temp;
    for (QMap<QString, bool> mapa : this->varijableSvjetova) {
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

void Cvor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Cvor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Cvor::dodajVarijablu (QMap<QString, bool> var) {
    varijableSvjetova.append(var);
}

void Cvor::ispisiVarijable() {
    for (int i = 0; i<varijableSvjetova.length(); i++) {
       // std::cout << varijableSvjetova[i].toStdString()<< std::endl;
    }
}

void Cvor::postaviIme(QString ime) {
    imeSvijeta = ime;
}

void Cvor::dodajDostizniSvijet (QString imeSvijeta) {
    dostizniSvjetovi.append(imeSvijeta);
}

void Cvor::isprintajDostizne() {
    for (int i = 0; i<this->dostizniSvjetovi.count(); i++) {
         std::cout << dostizniSvjetovi[i].toStdString() << std::endl;
    }
}

QList<QString> Cvor::vratiDostizne () {
    return this->dostizniSvjetovi;
}
