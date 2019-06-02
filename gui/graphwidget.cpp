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
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>

#include "mainwindow.h"
#include "graphwidget.h"
#include "node.h"
#include "edge.h"

 QGraphicsScene *scena;
 QString path;

 //TODO
 // napisati neki tekst na početku ali neće!!!
 // kreirati klasu universe sa svim atributima???
 // uradiiti validaciju pri čitanju i kreiranju json

 GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent),timerId(0){
     scena = new QGraphicsScene(this);
     scena->setItemIndexMethod(QGraphicsScene::NoIndex);
     scena->setSceneRect(-250, -250, 600, 525);
     setScene(scena);
     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.35), qreal(1.1));
     setMinimumSize(800,750);

     QPushButton *load = new QPushButton("Load .json file", this);
     connect(load, SIGNAL (released()), this, SLOT(loadFile()));
     load->setGeometry(QRect(QPoint(0,33),QSize(150, 50)));
     QFont f("Times New Roman", 12, QFont::Bold);
     load->setFont(f);

     QPushButton *create = new QPushButton("Create .json file", this);
     connect(create, SIGNAL (released()), this, SLOT(createFile()));
     create->setGeometry(QRect(QPoint(180,33),QSize(150, 50)));
     create->setFont(f);

     /*Label *label = new QLabel(this);
     QFont fa("Times New Roman", 22, QFont::Bold);
     label->setFont(fa);
     label->setText("<font color='red'>Učitajte datoteku da bi se prikazo graf</font>");
     label->setGeometry(120,262,600,200);*/
 }

 void GraphWidget::loadFile() {
     scena->clear();
     QString file = QFileDialog::getOpenFileName(this,tr("Open"),"",tr("LogicToolbox (*.json)"));
     path = file;
     JSONParser();
 }

 void GraphWidget::createFile() {
    /* QWidget *wdg = new QWidget;
     wdg->setWindowTitle("Create .json file");
     wdg->resize(500, 500);
     QLabel *lbl = createLabel(wdg, "Enter logic type:");
     lbl = createLabel(wdg, "\nEnter universe name:");
     lbl = createLabel(wdg, "\n\nEnter number of variables:");
     QLineEdit *edit = new QLineEdit(wdg);
     edit->setGeometry(100,100,100,100);
     wdg->show();*/
     MainWindow *win = new MainWindow(this);
     win->show();
 }

 void GraphWidget::JSONParser() {

     //Reading JSON file
     QList<QMap<QString, Node*>> worldList;
     QList<Node*> nodeList;
     QFile file(path);
     file.open(QIODevice::ReadOnly);
     QByteArray rawData = file.readAll();
     QJsonDocument doc(QJsonDocument::fromJson(rawData));
     QJsonObject jObj = doc.object();

     int numOfWorlds;
     if(jObj["Worlds"].toArray().size() == 0) qDebug() << "Universe doesn't have \"Worlds\" tag!";
     else if(jObj["Worlds"].toArray().size() != 0) numOfWorlds = jObj["Worlds"].toArray().size();

     int posA = -100;
     int posB = -50;
     Node *node = new Node(this);
     QMap<QString, Node*> world;
     for (int i = 0; i<numOfWorlds; i++) {

         //Counting adjacent worlds and corresponding variables
         int numOfVariables = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray().size();
         int numOfAdjacent = jObj["Worlds"].toArray()[i].toObject().value("AdjWorlds").toArray().size();
         QString worldName = jObj["Worlds"].toArray()[i].toObject().value("Name").toString();
         node = new Node(this);
         nodeList.append(node);
         world.clear();
         world.insert(worldName,node);

         //Adding variables to the worlds
         for (int j = 0; j< numOfVariables; j++) {
             QString variableName = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray()[j].toObject().value("Name").toString();
             bool istinitostVarijable = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray()[j].toObject().value("Value").toBool();
             QMap<QString, bool> map;
             map.insert(variableName, istinitostVarijable);
             node->addVariable(map);
         }

         //Adding adjacent worlds to the list
         for (int j = 0; j<numOfAdjacent; j++) {
             QString adjacentworld = jObj["Worlds"].toArray()[i].toObject().value("AdjWorlds").toArray()[j].toString();
             node->addAdjacentWorlds(adjacentworld);
         }

         //Creating nodes
         node->setPos(posA, posB);
         node->setName(worldName);
         posA += 60;
         posB += 2 * posA - 50 / 2;
         scena->addItem(node);
         worldList.append(world);
     }

     //Creating edges and connecting them
     for (int i = 0; i<nodeList.size(); i++) {
         if (nodeList[i]->getAdjacentWorlds().size() != 0) {
             for (int j = 0; j<nodeList[i]->getAdjacentWorlds().size(); j++) {
                 for (QMap<QString, Node*> map : worldList) {
                     QMap<QString, Node*>::iterator k;
                     for (k = map.begin(); k != map.end(); ++k) {
                         if (nodeList[i]->getAdjacentWorlds()[j] == k.key()) {
                                  scena->addItem(new Edge(nodeList[i], k.value()));
                         }
                     }
                 }
             }
         }
     }
 }

 void GraphWidget::moving()
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

 QLabel *GraphWidget::createLabel(QWidget *parent,QString text) {
     QLabel *label = new QLabel(parent);
     QFont fa("Times New Roman", 12, QFont::DemiBold);
     label->setFont(fa);
     label->setText(text);
     return label;
 }
