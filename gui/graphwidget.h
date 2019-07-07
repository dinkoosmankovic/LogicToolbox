#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>
#include <QLabel>
#include <QString>
#include <QObject>
#include <QEvent>
#include "BarWidget.h"

class Node;

class GraphWidget : public QGraphicsView {
    Q_OBJECT

public:
    GraphWidget (QWidget *parent = 0);
    void moving();



protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void JSONParser();

private:
    BarWidget *bar;
    int timerId;
       QGraphicsView         * view;
    QLabel *createLabel(QWidget *parent, QString text);


private slots:

    //Methods for reading existing JSON file or creating new one
     void loadFile();
     void createFile();
};


#endif // GRAPHWIDGET_H
