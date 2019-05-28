#include <iostream>
#include <QtGui>
#include <math.h>
#include <QTextEdit>
#include <QFile>
#include <QFont>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <QMap>
#include "graphwidget.h"
#include "cvor.h"
#include "grana.h"
#include <QFileDialog>
#include "mainwindow.h"
#include <QLabel>

 QGraphicsScene *scena;
 QString putanja;

 //možda kreirati klasu universe sa svim atributimas
 GraphWidget::GraphWidget(QWidget *roditelj) : QGraphicsView(roditelj),timerId(0){
     scena = new QGraphicsScene(this);
     scena->setItemIndexMethod(QGraphicsScene::NoIndex);
     scena->width();

     scena->height();
     scena->setSceneRect(-250, -250, 600, 525);
     setScene(scena);
     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.35), qreal(1.1));
     setMinimumSize(800,750);
     QPushButton *button = new QPushButton("Load .json file", this);
     connect(button, SIGNAL (released()), this, SLOT(ucitavanjeFajla()));
     button->setGeometry(QRect(QPoint(0,33),QSize(150, 50)));
     QFont f("Times New Roman", 12, QFont::Bold);
     button->setFont(f);
     /*Label *label = new QLabel(this);
     QFont fa("Times New Roman", 22, QFont::Bold);
     label->setFont(fa);
     label->setText("<font color='red'>Učitajte datoteku da bi se prikazo graf</font>");
     label->setGeometry(120,262,600,200);*/
 }
 void GraphWidget::ucitavanjeFajla() {
     scena->clear();
     QString imeFajla = QFileDialog::getOpenFileName(this,tr("Otvori"),"",tr("LogicToolbox (*.json)"));
     putanja = imeFajla;
     JSONParser();
 }
 void GraphWidget::JSONParser() {

     //Čitanje iz JSON fajla
     QList<QMap<QString, Cvor*>> listaSvjetova;
     QList<Cvor*> listaCvorova;
     QFile file(putanja);
     file.open(QIODevice::ReadOnly);
     QByteArray rawData = file.readAll();
     QJsonDocument doc(QJsonDocument::fromJson(rawData));
     QJsonObject jObj = doc.object();

     int brojSvjetova;
     if(jObj["Worlds"].toArray().size() == 0) qDebug() << "Universe doesn't have \"Worlds\" tag!";
     else if(jObj["Worlds"].toArray().size() != 0) brojSvjetova = jObj["Worlds"].toArray().size();

     int posA = -100;
     int posB = -50;
     Cvor *cvor = new Cvor(this);
     QMap<QString, Cvor*> svijet;
     for (int i = 0; i<brojSvjetova; i++) {

         //Računanje broja dostižnih svjetova i broja varijabli za svaki svijet
         int brVar = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray().size();
         int brDostiznih = jObj["Worlds"].toArray()[i].toObject().value("AdjWorlds").toArray().size();
         QString imeSvijeta = jObj["Worlds"].toArray()[i].toObject().value("Name").toString();
         cvor = new Cvor(this);
         listaCvorova.append(cvor);
         svijet.clear();
         svijet.insert(imeSvijeta,cvor);

         //Dodavanje varijabli svjetova
         for (int j = 0; j< brVar; j++) {
             QString imeVarijable = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray()[j].toObject().value("Name").toString();
             bool istinitostVarijable = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray()[j].toObject().value("Value").toBool();
             QMap<QString, bool> mapa;
             mapa.insert(imeVarijable, istinitostVarijable);
             cvor->dodajVarijablu(mapa);
         }

         //Dodavanje dostižnih svjetova
         for (int j = 0; j<brDostiznih; j++) {
             QString dostizniSvijet = jObj["Worlds"].toArray()[i].toObject().value("AdjWorlds").toArray()[j].toString();
             cvor->dodajDostizniSvijet(dostizniSvijet);
         }

         //Kreiranje čvora
         cvor->setPos(posA, posB);
         cvor->postaviIme(imeSvijeta);
         posA += 60;
         posB += 2 * posA - 50 / 2;
         scena->addItem(cvor);
         listaSvjetova.append(svijet);
     }

     //Kreiranje grana i povezivanje
     for (int i = 0; i<listaCvorova.size(); i++) {
         if (listaCvorova[i]->vratiDostizne().size() != 0) {
             for (int j = 0; j<listaCvorova[i]->vratiDostizne().size(); j++) {
                 for (QMap<QString, Cvor*> mapa : listaSvjetova) {
                     QMap<QString, Cvor*>::iterator k;
                     for (k = mapa.begin(); k != mapa.end(); ++k) {
                         if (listaCvorova[i]->vratiDostizne()[j] == k.key()) {
                                  scena->addItem(new Grana(listaCvorova[i], k.value()));
                         }
                     }
                 }
             }
         }
     }
 }

 void GraphWidget::pomjeranje()
 {
     if (!timerId)
         timerId = startTimer(1000 / 25);
 }

 void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
 {
     Q_UNUSED(rect);

     // Shadow
     QRectF sceneRect = this->sceneRect();
     QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
     QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);

     //SJENE NA OKVIRU OD PROZORA
     if (rightShadow.intersects(rect) || rightShadow.contains(rect))
         painter->fillRect(rightShadow, Qt::darkGray);
     if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
         painter->fillRect(bottomShadow, Qt::darkGray);

     // Fill
     QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
     gradient.setColorAt(0, Qt::white);
     gradient.setColorAt(1, Qt::lightGray);
     painter->fillRect(rect.intersected(sceneRect), gradient);
     painter->setBrush(Qt::NoBrush);
     painter->drawRect(sceneRect);
 }

