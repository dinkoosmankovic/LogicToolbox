#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMap>
#include <tuple>

class QGraphicsSceneMouseEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_2_editingFinished();
    void on_lineEdit_4_editingFinished();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    //SET
    void setLogicType (QString type) { logicType = type; }
    void setUniverseName (QString name) { universeName = name; }
    void setVarNames (QList<QString> name) { listOfVaribles = name; }
    void setWorldNames (QList<QString> name) { listOfWorldNames.append(name); }
    void setValueOfVarible ( QList<std::tuple<QString, QString, bool>> val) { varValue = val; }
    void setAdjcWorlds (QList<QMap<QString,QList<QString>>> world) {adjcWorlds = world; }

    //GET
    QString getLogicType() const { return logicType; }
    QString getUniverseName() const { return universeName; }
    int getNumOfVariables() const { return listOfVaribles.size(); }
    QList<QString> getVarNames() const { return listOfVaribles; }
    int getNumOfWorlds() const { return listOfWorldNames.size(); }
    QList<QString> getNamesOfTheWorlds() const { return listOfWorldNames; }
    QList<QMap<QString, QList<QString>>> getAdjcWorlds() const { return adjcWorlds; }
    QList<std::tuple<QString, QString, bool>> getValueOfVariable() const { return  varValue; }

    //Atributes
    Ui::MainWindow *ui;
    QString logicType;
    QString universeName;
    QList<QString> listOfVaribles;
    QList<QString> listOfWorldNames;
    QList<QMap<QString, QList<QString>>> adjcWorlds;
    QList<std::tuple<QString, QString, bool>> varValue;
};

#endif // MAINWINDOW_H
