#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
class QGraphicsSceneMouseEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
   // QString vratiPutanju();
    ~MainWindow();
private slots:

    void on_pushButton_clicked();


public slots:
    void on_pushButton_2_clicked();
private:
  //     void postaviPutanju(QString s);
   //     QString putanja;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
