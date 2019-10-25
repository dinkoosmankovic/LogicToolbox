/*#include "hello.h"
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "RADIIIIII";
    hello();
    return 0;
}


*/
#include "gui/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "gui/graphwidget.h"
#include <QDesktopWidget>
#include "hello.h"
#include <iostream>
#include <QIcon>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWidget w;
   /* MainWindow w;
    w.size(5
    QDesktopWidget dw;
    MainWindow w;
    int x=dw.width()*0.5;
    int y=dw.height()*0.5;
    w.setFixedSize(x,y);*/
    QString icon =  QCoreApplication::applicationDirPath() + "/icon.png";
    w.setWindowIcon(QIcon(icon));
    w.show();
 //   hello();
    return a.exec();


}
