#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>

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
    int timerId;

private slots:
     void loadFile();
};
#endif // GRAPHWIDGET_H
