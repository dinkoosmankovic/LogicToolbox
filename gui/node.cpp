//
// Created by Alma Ibrašimović, january 2019.
//

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
#include <QWidget>
#include <QFont>
#include <QMap>
#include <QDebug>
#include <QPen>
#include <QLinearGradient>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QLineEdit>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "../include/CoreEvaluator.h"
#include "../include/ResultTree.h"
#include "../include/Graph.h"

/*TODO
  PREPRAVITI SVE GETTER-E NA CONST ------ ZA SVAKU KLASU
 */

Node::Node(GraphWidget *graphWidget, QString pathA) : graphA(graphWidget) {
    radius = 25;
    path = pathA;
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setFlag(ItemIsMovable); //Moving nodes
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);
}

void Node::addEdge(Edge *edge) {
    edgesList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const {
    return edgesList;
}

QRectF Node::boundingRect() const {
   return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

QPainterPath Node::shape() const {
    QPainterPath temp;
    temp.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    return temp;
}

QList<QMap<string,char*>> Node::getResults() const  {
    CoreEvaluator coreEvaluator (path.toStdString().c_str());
    QList<QMap<string,char*>> a;

    //Available variables for the universe
    QString variables = "#(";
    auto temp = getVariables();
    for (int j = 0; j<temp.size(); j++) {
        variables+=temp[j];
        if (j != temp.size() -1) variables += "|";
    }
    variables += ")";

    if (variables.toStdString() != "#()") {
        ResultTree resultTree = coreEvaluator.returnResultTree(variables.toStdString());
        auto rootResult = resultTree.getFinalResult();
        for(auto i = rootResult.begin(); i != rootResult.end(); i++){
            char* color = (i->second? const_cast<char*>("green"): const_cast<char*>("red"));
            QMap<string, char*> tmp;
            tmp.insert(i->first->getName(), color);
            a.append(tmp);
        }
    }
   return a;
}

//Changing node color
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    static QList<QMap<string,char*>> a;
    QFont f("Arial", 11, QFont::Bold);
    painter->setFont(f);
    if (path != "UniverseConfig.json") a = getResults();
    QRadialGradient gradient(-3, -3, radius);
    if (a.size() != 0) {
        for (QMap<string, char*> mapa : a) {
            QMap<string, char*>::iterator i;
            for (i = mapa.begin(); i != mapa.end(); ++i) {
                string wrld = i.key();
                char* color = i.value();
                if(this->worldName.toStdString() == wrld) {
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::darkGray);
                    painter->drawEllipse( radius - 3, radius - 3, 2 * radius, 2 * radius );
                    if (option->state & QStyle::State_Sunken) {
                        gradient.setCenter(3, 3);
                        gradient.setFocalPoint(3, 3);
                        gradient.setColorAt(1, QColor(Qt::black).light(120));
                        gradient.setColorAt(0, QColor(color).light(120));
                    }
                    else {
                        gradient.setColorAt(0, Qt::black);
                        gradient.setColorAt(1, color);
                    }
                    painter->setBrush(gradient);
                    painter->setPen(QPen(Qt::black, 0));
                    painter->drawEllipse( -radius, -radius, 2 * radius, 2 * radius );
                    painter->setPen(Qt::white);
                    painter->drawText(boundingRect(),Qt::AlignCenter,this->worldName);
                }
            }
        }
    }
    else {
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::darkGray);
        painter->drawEllipse( radius - 3, radius - 3, 2 * radius, 2 * radius );
        if (option->state & QStyle::State_Sunken) {
            gradient.setCenter(3, 3);
            gradient.setFocalPoint(3, 3);
            gradient.setColorAt(1, QColor(Qt::black).light(120));
            gradient.setColorAt(0, QColor(Qt::darkCyan).light(120));
        }
        else {
            gradient.setColorAt(0, Qt::black);
            gradient.setColorAt(1, Qt::darkCyan);
        }
        painter->setBrush(gradient);
        painter->setPen(QPen(Qt::black, 0));
        painter->drawEllipse( -radius, -radius, 2 * radius, 2 * radius );
        painter->setPen(Qt::white);
        painter->drawText(boundingRect(),Qt::AlignCenter,this->worldName);
    }
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        foreach (Edge *edge, edgesList) edge->adjust();
        graphA->moving();
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }

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
    if(path == "UniverseConfig.json") {
        QFont f("Times New Roman", 13, QFont::Bold);
        widget = new QWidget;
        widget->resize(350,210);
        widget->setWindowTitle("Enter values of the variables");
        QLabel *lbl = new QLabel(widget);
        lbl->setGeometry(2,5,163,20);
        lbl->setFont(f);
        lbl->setText(" Available variables: ");
        QLineEdit *line =new  QLineEdit(widget);
        line->setFont(f);
        line->setGeometry(170,5,170,20);
        line->setReadOnly(true);
        QString var;
        auto temp = getVariableNames();
        for (int i = 0; i<temp.size(); i++) {
            if (i == temp.size()-1) var += temp[i];
            else var += temp[i] + ", ";
        }
        line->setText(var);
        line->setStyleSheet("QLineEdit{ "
                                "background-color:rgb(255,255,255);"
                                "border: 2px solid gray;"
                                "border-radius: 10px;"
                                "padding: 0 8px;"
                                "selection-background-color: darkgray;"
                                "font-size: 14px;}"
                                "QLineEdit:focus { "
                                "background-color:rgb(255,255,255);}"
                                );

        //TRUE
        QLabel *lblA = new QLabel(widget);
        lblA->setText(" Enter variables which\n are 'TRUE': ");
        lblA->setGeometry(2,40,196,50);
        lblA->setFont(f);
        lineA = new  QLineEdit(widget);
        lineA->setFont(f);
        lineA->setGeometry(170,43,170,20);
        lineA->setStyleSheet("QLineEdit{ "
                                "background-color:rgb(255,255,255);"
                                "border: 2px solid gray;"
                                "border-radius: 10px;"
                                "padding: 0 8px;"
                                "selection-background-color: darkgray;"
                                "font-size: 14px;}"
                                "QLineEdit:focus { "
                                "background-color:rgb(255,255,255);}"
                                );


        //FALSE
        QLabel *lblB = new QLabel(widget);
        lblB->setText(" Enter variables which\n are 'FALSE': ");
        lblB->setGeometry(2,100,196,50);
        lblB->setFont(f);
        lineB =new  QLineEdit(widget);
        lineB->setFont(f);
        lineB->setGeometry(170,103,170,20);
        lineB->setStyleSheet("QLineEdit{ "
                                "background-color:rgb(255,255,255);"
                                "border: 2px solid gray;"
                                "border-radius: 10px;"
                                "padding: 0 8px;"
                                "selection-background-color: darkgray;"
                                "font-size: 14px;}"
                                "QLineEdit:focus { "
                                "background-color:rgb(255,255,255);}"
                                );

        QPushButton *btn = new QPushButton(widget);
        btn->setText("Submit new values");
        btn->setGeometry(183,167,150,30);
        btn->setFont(f);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(changeValue()));

        QPushButton *btnA = new QPushButton(widget);
        btnA->setText("List old values");
        btnA->setGeometry(5,167,150,30);
        btnA->setFont(f);
        QObject::connect(btnA, SIGNAL(released()), this, SLOT(listValue()));
        widget->show();
    }
    else if(path != "UniverseConfig.json") {
        QWidget *wdg = new QWidget;
        wdg->setWindowTitle("World  \"" + this->worldName + "\" ");
        wdg->resize(200, 200);
        QString temp;
        for (QMap<QString, bool> mapa : this->worldVariables) {
            QMap<QString, bool>::iterator i;
            for (i = mapa.begin(); i != mapa.end(); ++i) {
                QString variable, value;
                if (this->worldVariables.size() >= 5) wdg->resize(250,400);
                variable = i.key();
                if (i.value()) value = "True";
                else value = "False";
                temp += " " + variable + " : " + value + "\n";
            }
        }
        QLabel *label = new QLabel(wdg);
        QFont f("Times New Roman", 17, QFont::Bold);
        label->setFont(f);
        label->setText(temp);
        wdg->show();
    }
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

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
   QString tooltip = QString("Right click to delete world\nDouble click to open details about world\nLeft click to move world around the scene");
   if (tooltip != toolTip()) setToolTip(tooltip);
   update();
   QGraphicsItem::hoverEnterEvent(event);
}

void Node::addVariable (QMap<QString, bool> var) {
    worldVariables.append(var);
}

QList<QString> Node::getVariables() const {
    QList<QString> var;
    for (QMap<QString, bool> mapa : this->worldVariables) {
        QMap<QString, bool>::iterator i;
        for (i = mapa.begin(); i != mapa.end(); ++i) {
            var.append(i.key());
        }
    }
    return var;
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

void Node::changeValue() {
    auto allVariables = getVariableNames();
    bool condA = true;
    bool condB = true;
    bool condD = true;
    bool condC = true;
    QWidget *msg = new QWidget;
    msg->setWindowTitle("Error");
    msg->resize(400, 60);
    QLabel *label = new QLabel(msg);
    QFont f("Times New Roman", 12, QFont::Bold);
    label->setFont(f);
    QList<QString> trueVar;
    QList<QString> falseVar;
    QString trueV = lineA->text();
    QString falseV = lineB->text();
    if(trueV.size() != 0) trueVar.append(trueV.split(','));
    if(falseV.size() != 0) falseVar.append(falseV.split(','));

    if (trueVar.size() != 0 && falseVar.size() != 0) {
        for (int i = 0; i<trueVar.size(); i++) {
            for (int j = 0; j<falseVar.size(); j++) {
                if (trueVar[i] == falseVar[j]) condA = false;
            }
        }
    }

    if (trueVar.size() + falseVar.size() == allVariables.size()) {
        qStableSort(allVariables.begin(), allVariables.end());
        QList<QString> temp = trueVar + falseVar;
         qStableSort(temp.begin(), temp.end());
         if (temp != allVariables) condC = false;
    }
    if(trueVar.size() + falseVar.size() > allVariables.size()) condD = false;
    if(trueVar.size() + falseVar.size() < allVariables.size()) condB = false;
    if (condA && condB && condC && condD) {
        QMap<QString, bool> map;
        foreach (auto i, trueVar) {
            map.clear();
            map.insert(i, 1);
            addVariable(map);
        }
        foreach (auto i, falseVar) {
            map.clear();
            map.insert(i, 0);
            addVariable(map);
        }
        listValue();
        widget->close();
    }
    else if (!condA) {
        label->setText("  Variable can't be TRUE and FALSE at the same time!");
        msg->show();
    }
    else if (!condB) {
        label->setText("  You didn't choose value for all variables!");
        msg->resize(300, 60);
        msg->show();
    }
    else if (!condC) {
         label->setText("  Some of the entered variables do not exist!");
         msg->resize(300, 60);
         msg->show();
    }
    else if (!condD) {
         label->setText("  You entered extra variables!");
         msg->resize(300, 60);
         msg->show();
    }
}

void Node::listValue() {
    widget->close();
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("World  \"" + this->worldName + "\" ");
    wdg->resize(200, 200);
    QString temp;
    for (QMap<QString, bool> mapa : this->worldVariables) {
        QMap<QString, bool>::iterator i;
        for (i = mapa.begin(); i != mapa.end(); ++i) {
            QString variable, value;
            if (this->worldVariables.size() >= 5) wdg->resize(200,400);
            variable = i.key();
            if (i.value()) value = "True";
            else value = "False";
            temp += " " + variable + " : " + value + "\n";
        }
    }
    QLabel *label = new QLabel(wdg);
    QFont f("Times New Roman", 17, QFont::Bold);
    label->setFont(f);
    label->setText(temp);
    wdg->show();
}
