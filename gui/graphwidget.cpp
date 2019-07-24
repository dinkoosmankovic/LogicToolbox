//
// Created by Alma Ibrašimović, january 2019.
//

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
#include <QLineEdit>

#include "mainwindow.h"
#include "graphwidget.h"
#include "node.h"
#include "edge.h"

static int counter = 0;
QLineEdit *lineEdit;
QLineEdit *lineEditA;
QList<QString> variables;

 //TODO
 // uradiiti validaciju pri čitanju i kreiranju json

 GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent),timerId(0){
     first = new Node(this);
     second = new Node(this);
     scene = new QGraphicsScene(this);
     scene->setItemIndexMethod(QGraphicsScene::NoIndex);
     scene->setSceneRect(-250,-250, 600, 600);
     setScene(scene);
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
     add->setToolTip("When the graph is not loaded, add more, unconnected worlds to the loaded graph!");
     connect(add, SIGNAL (released()), this, SLOT (addWorlds()));

     connectW = createButton(this, "Connect worlds", 530, 36);
     connectW->setToolTip("Click on the first and the second world, then click this button to connect them!");
     connect(connectW, SIGNAL(released()), this, SLOT(connectWorlds()));
 }

 void GraphWidget::loadFile() {
     static int i = 1;
     QString file = QFileDialog::getOpenFileName(this,tr("Open"),"",tr("LogicToolbox (*.json)"));
     pathLoc = file;
     add->setDisabled(false);
     if(pathLoc != "") {
         scene->clear();
         connectW->setDisabled(true);
         add->setDisabled(true);
     }
     JSONParser();
     this->scene->setSceneRect(-250,-250, 600, 600 - (i - 0.9));
     i++;
 }

 void GraphWidget::createFile() {
     MainWindow *win = new MainWindow(this);
     win->show();
 }

 void GraphWidget::setNewUniverseName() {
     if (lineEdit->text() != "" && lineEditA->text() != "") {
         this->setUniverseName(lineEdit->text());
         QString temp = lineEditA->text();
         if(temp.size() != 0) variables.append(temp.split(','));
         addWrlds = true;
         static int i = 1, x = -200;
         int y = 0;
         Node *n = new Node(this);
         n->setPos(x, y);
         n->setPosition(n->pos());
         n->setName("w" + QString::number(i));
         setNewNodes(n);
         x += 100; i++;
         QMap<QString, bool> value;
         foreach(auto a , variables) {
             value.clear();
             value.insert(a, false);
             n->addVariable(value);
         }
         this->scene->setSceneRect(-250,-250, 600, 600 - (i - 0.9));
         scene->addItem(n);
         wdgA->close();
     }
     if (lineEdit->text() == "") lineEdit->setPlaceholderText("Enter universe name first!");
     if (lineEditA->text() == "") lineEditA->setPlaceholderText("Enter available variables!");

 }

 void GraphWidget::addWorlds() {
     static int i = 0;
     if (i == 0) {
         wdgA = new QWidget;
         wdgA->setWindowTitle("Enter name and variables");
         wdgA->resize(400, 160);
         QPushButton *btnA = new QPushButton(wdgA);
         QLabel *label = new QLabel(wdgA);
         label->setGeometry(3,9,175,20);
         QFont f("Times New Roman", 13, QFont::Bold);
         label->setFont(f);
         label->setText("Enter universe name:");
         QLabel *labelA = new QLabel(wdgA);
         labelA->setGeometry(3,40,175,50);
         labelA->setFont(f);
         labelA->setText("Enter variables:\n(with comma):");
         lineEdit = new QLineEdit(wdgA);
         lineEditA = new QLineEdit(wdgA);
         lineEdit->setStyleSheet("QLineEdit{ "
                                 "background-color:rgb(255,255,255);"
                                 "border: 2px solid gray;"
                                 "border-radius: 10px;"
                                 "padding: 0 8px;"
                                 "selection-background-color: darkgray;"
                                 "font-size: 14px;}"
                                 "QLineEdit:focus { "
                                 "background-color:rgb(255,255,255);}"
                                 );
         lineEditA->setStyleSheet("QLineEdit{ "
                                 "background-color:rgb(255,255,255);"
                                 "border: 2px solid gray;"
                                 "border-radius: 10px;"
                                 "padding: 0 8px;"
                                 "selection-background-color: darkgray;"
                                 "font-size: 14px;}"
                                 "QLineEdit:focus { "
                                 "background-color:rgb(255,255,255);}"
                                 );
         lineEdit->setGeometry(182,9,200,20);
         lineEditA->setGeometry(182,40,200,20);
         btnA->setText("OK");
         btnA->setGeometry(210,95,150,35);
         btnA->setFont(QFont("Times New Roman", 12, QFont::Bold));
         connect(btnA, SIGNAL(released()), this, SLOT(setNewUniverseName()));
         wdgA->show();
     }
     if (i >= 1 && lineEdit->text() != "") {
         addWrlds = true;
         static int i = 2, x = -100, z = 1;
         int y = 0;
         Node *n = new Node(this);
         n->setPos(x, y);
         n->setPosition(n->pos());
         n->setName("w" + QString::number(i));
         setNewNodes(n);
         x += 100; i++;
         QMap<QString, bool> value;
         foreach(auto a , variables) {
            value.clear();
            value.insert(a, false);
            n->addVariable(value);
         }
         this->scene->setSceneRect(-250,-250, 600, 600 - (z - 0.9));
         z++;
         scene->addItem(n);
     }
     i++;
 }

 void GraphWidget::connectWorlds() {
     if(first && second) this->scene->addItem(new Edge(first, second));
     counter = 0;
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
     setUniverseName(jObj["Name"].toString()); // Universe name
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
             bool variableValue = jObj["Worlds"].toArray()[i].toObject().value("Variables").toArray()[j].toObject().value("Value").toBool();
             QMap<QString, bool> map;
             map.insert(variableName, variableValue);
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
         scene->addItem(node);
         worldList.append(world);
     }

     //Creating edges and connecting them
     for (int i = 0; i<nodeList.size(); i++) {
         if (nodeList[i]->getAdjacentWorlds().size() != 0) {
             for (int j = 0; j<nodeList[i]->getAdjacentWorlds().size(); j++) {
                 for (QMap<QString, Node*> map : worldList) {
                     QMap<QString, Node*>::iterator k;
                     for (k = map.begin(); k != map.end(); ++k) {
                         if (nodeList[i]->getAdjacentWorlds()[j] == k.key()) scene->addItem(new Edge(nodeList[i], k.value()));
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
     if (pathLoc == "" && !addWrlds) painter->drawText(textRect, message);
     else if (addWrlds || pathLoc != "") painter->drawText(textRect,Qt::AlignHCenter, getUniverseName());
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
         QGraphicsItem *dlt = itemAt(event->pos());
         Node *tmp = dynamic_cast<Node*>(dlt);
         if (tmp) {
             scene->removeItem(dlt);
             QList<Edge*> e = tmp->edges();
             for (int i = 0; i<e.size(); i++) {
                 Edge *tmpEdge = dynamic_cast<Edge*>(e[i]);
                 if (tmpEdge) {
                     scene->removeItem(e[i]);
                 }
             }
         }
     }
     else if (event->button() == Qt::LeftButton) {
         QGraphicsItem *clicked = itemAt(event->pos());
         Node *tmp = dynamic_cast<Node*>(clicked);
         if (pathLoc == "" && tmp) {
             auto newNodesList = getNewNodes();
             for (int i = 0; i<newNodesList.size(); i++) {
                 if (newNodesList[i]->pos() != newNodesList[i]->getPosition()) {
                     counter = 0;
                     newNodesList[i]->setPosition(newNodesList[i]->pos());
                 }
             }
             if (counter == 0) {
                 first = dynamic_cast<Node*>(clicked);
             }
             else if (counter == 1) {
                 second = dynamic_cast<Node*>(clicked);
             }
         }
         if(tmp) clicked->setFlag(QGraphicsItem::ItemIsMovable);
     }

     counter++;
     if(counter > 1) counter = 0;
     QGraphicsView::mousePressEvent(event);
 }
