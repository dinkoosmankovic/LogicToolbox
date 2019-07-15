//
// Created by Alma Ibrašimović, january 2019.
//

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPointF>
#include <QPushButton>
#include <QString>
#include <QObject>
#include <QList>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
class Node;

class GraphWidget : public QGraphicsView {
    Q_OBJECT

public:
    GraphWidget (QWidget *parent = 0);
    void moving();
    void setUniverseName (QString name) { universeName = name; }
    QString getUniverseName() const { return universeName; }

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QMouseEvent *e);
    void JSONParser();

private:
    int timerId;
    QString pathLoc;
    QPushButton *add;
    QPushButton *connectW;
    Node *first;
    Node *second;
    QPushButton *createButton(QWidget *parent, QString text, int x, int y);
    QGraphicsScene *scene;
    QString universeName;
    QList<Node*> newNodes; //Worlds which are created on the button 'Add'
    void setNewNodes (Node *n) { newNodes.append(n);}
    QList<Node*> getNewNodes() const { return newNodes; }

private slots:

    //Methods for reading existing JSON file or creating new one
     void loadFile();
     void createFile();
     void addWorlds();
     void connectWorlds();
};


#endif // GRAPHWIDGET_H
