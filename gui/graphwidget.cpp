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
#include <QRectF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QObject>
#include <QEvent>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMouseEvent>

#include "mainwindow.h"
#include "graphwidget.h"
#include "node.h"
#include "edge.h"

QString pathLoc;
QPushButton *add;

 //TODO
 // uradiiti validaciju pri čitanju i kreiranju json

 GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent),timerId(0){

     scena = new QGraphicsScene(this);
     scena->setItemIndexMethod(QGraphicsScene::NoIndex);
     scena->setSceneRect(-250,-250, 600, 600);
     setScene(scena);
     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(1.35), qreal(1.1));
     setMinimumSize(800,950);

     //Creating buttons
     QPushButton *load = createButton(this, "Load .json file", 5,36);
     connect(load, SIGNAL (released()), this, SLOT(loadFile()));
     load->setToolTip("All nodes in the graph are movable!");

     QPushButton *create = createButton(this, "Create .json file", 180, 36);
     connect(create, SIGNAL (released()), this, SLOT(createFile()));

     add = createButton(this, "Add more worlds", 355, 36);
     add->setToolTip("When you load the graph, add more, unconnected worlds to the loaded graph!");
     connect(add, SIGNAL (released()), this, SLOT (addWorlds()));
     if (pathLoc == "") add->setDisabled(true);
 }

 void GraphWidget::loadFile() {
     QString file = QFileDialog::getOpenFileName(this,tr("Open"),"",tr("LogicToolbox (*.json)"));
     pathLoc = file;
     add->setDisabled(false);
     if(pathLoc != "") scena->clear();
     JSONParser();
 }

 void GraphWidget::createFile() {
     MainWindow *win = new MainWindow(this);
     win->show();
 }

 void GraphWidget::addWorlds() {
     static int x =-200;
     int y = 0;
     Node *n = new Node(this, pathLoc);
     n->setPos(x, y);
     x += 40;
     scena->addItem(n);
 }

 void GraphWidget::JSONParser() {

     //Reading JSON file
     QList<QMap<QString, Node*>> worldList;
     QList<Node*> nodeList;
     QFile file(pathLoc);
     file.open(QIODevice::ReadOnly);
     QByteArray rawData = file.readAll();
     QJsonDocument doc(QJsonDocument::fromJson(rawData));
     QJsonObject jObj = doc.object();
     int numOfWorlds;
     if(jObj["Worlds"].toArray().size() == 0) qDebug() << "Universe doesn't have \"Worlds\" tag!";
     else if(jObj["Worlds"].toArray().size() != 0) numOfWorlds = jObj["Worlds"].toArray().size();

     int posA = -100;
     int posB = 0;
     Node *node = new Node(this,pathLoc);
     QMap<QString, Node*> world;
     for (int i = 0; i<numOfWorlds; i++) {

         //Counting adjacent worlds and corresponding variables
         int numOfVariables = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray().size();
         int numOfAdjacent = jObj["Worlds"].toArray()[i].toObject().value("AdjWorlds").toArray().size();
         QString worldName = jObj["Worlds"].toArray()[i].toObject().value("Name").toString();

         node = new Node(this,pathLoc);
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
         posB += 3.5 * posA + 30 / 2;
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
     if (!timerId) timerId = startTimer(1000 / 25);
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

     //Text
     QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,sceneRect.width() - 4, sceneRect.height() - 4);
     QString message(tr("Click 'Load file' to show existing graph or 'Create file' to create a new one"));
     QFont font = painter->font();
     font.setBold(true);
     font.setPointSize(14);
     painter->setFont(font);
     painter->setPen(Qt::black);
     painter->drawText(textRect, message);
 }

 QPushButton *GraphWidget::createButton(QWidget *parent, QString text, int x, int y) {
     QPushButton *btn = new QPushButton(text, parent);
     btn->setGeometry(QRect(QPoint(x,y),QSize(160, 60)));
     QFont f("Times New Roman", 12, QFont::Bold);
     btn->setFont(f);
     return btn;
 }

 void GraphWidget::mousePressEvent(QMouseEvent *event){
    // n->setPos(pt.x(), pt.y()); // get the position of click on scene

     if(event->button() == Qt::RightButton) {
     //    QPointF pt = mapToScene(event->pos());
         QGraphicsItem *dlt = itemAt(event->pos());
         Node *tmp = dynamic_cast<Node*>(dlt);
         if (tmp) {
             scena->removeItem(dlt);
             QList<Edge*> e = tmp->edges();
             for (int i = 0; i<e.size(); i++) {
                 Edge *tmpEdge = dynamic_cast<Edge*>(e[i]);
                 if (tmpEdge) {
                     scena->removeItem(e[i]);
                 }
             }
         }
     }
     else if (event->button() == Qt::LeftButton) {
         QGraphicsItem *dlt = itemAt(event->pos());
         Node *tmp = dynamic_cast<Node*>(dlt);
         /*dlt->setFlag(QGraphicsItem::ItemIsFocusable);
         dlt->setFlag(QGraphicsItem::ItemIsSelectable);*/
         if(tmp)dlt->setFlag(QGraphicsItem::ItemIsMovable);
     }

     QGraphicsView::mousePressEvent(event);
 }

