#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>

class Cvor;

class GraphWidget : public QGraphicsView {
    Q_OBJECT

public:
    GraphWidget (QWidget *roditelj = 0);
    void pomjeranje();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void JSONParser();

private slots:
     void ucitavanjeFajla();

private:
    int timerId;
    Cvor *sredisnjiCvor;

};
#endif // GRAPHWIDGET_H
