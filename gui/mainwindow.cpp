#include <QPushButton>
#include <QMessageBox>
#include <QObject>
#include <QRegion>
#include <QWidget>
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QString>
#include <QList>
#include <QComboBox>
#include <QCheckBox>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <tuple>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"
#include "node.h"

QList<QMap<QString, QList<QString>>> listAllAdjWrlds;
QList<std::tuple<QString, QString, bool>> varValue;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->comboBox->addItem("K");
    ui->comboBox->addItem("T");
    ui->comboBox->addItem("S4");
    ui->comboBox->addItem("S5");
    ui->comboBox->addItem("D");
    this->setWindowTitle("Create .json file");
    ui->groupBox->setStyleSheet("QGroupBox {  border: 1px solid gray;}");
    ui->groupBox_2->setStyleSheet("QGroupBox {  border: 1px solid gray;}");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_lineEdit_2_editingFinished() {
    listOfWorldNames.clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    QString worlds = ui->lineEdit_2->text();
    QList<QString> wrldNms;
    wrldNms.append(worlds.split(','));
    setWorldNames(wrldNms);
    QList<QString> temp = getNamesOfTheWorlds();
   // QVBoxLayout *vbox = new QVBoxLayout;
    for (int i=0; i<getNumOfWorlds(); i++) {
        ui->comboBox_2->addItem(temp[i]);
        ui->comboBox_3->addItem(temp[i]);
        /*checkBox1 = new QCheckBox;
        checkBox1->setText(temp[i]);
        vbox->addWidget(checkBox1);*/
    }
   // ui->groupBox->setLayout(vbox);
}

void MainWindow::on_lineEdit_4_editingFinished() {
    QString variables = ui->lineEdit_4->text();
    ui->lineEdit_7->setText(variables);
    QList<QString> varNames;
    varNames.append(variables.split(','));
    setVarNames(varNames);
   /* QList<QString> temp = getVarNames();
    for (int i = 0; i<getNumOfVariables(); i++) {
        qDebug()<<temp[i];
    }*/
}

void MainWindow::on_pushButton_clicked() {

    setLogicType(ui->comboBox->currentText());
    setUniverseName(ui->lineEdit->text());

    //Creating JSON file
    QJsonObject jsontx;

    //Inserting universe name and type of logic
    jsontx.insert("Name", QJsonValue::fromVariant(getUniverseName()));
    jsontx.insert("Logic", QJsonValue::fromVariant(getLogicType()));

    //Inserting variables name
    QList<QString> temp = getVarNames();
    QJsonArray varName;
    for(int i = 0; i<temp.size(); i++) varName.push_back(temp[i]);
    jsontx.insert("VariableNames", varName);

    //Inserting info about each world
    QJsonArray worlds;
    QJsonObject wlrdInfo;
    QList<std::tuple<QString, QString, bool>> valueOfVariables = getValueOfVariable();
    temp =  getNamesOfTheWorlds();

    for(QMap<QString, QList<QString>> map : adjcWorlds) {
        QMap<QString,QList<QString>>::iterator i;
        for(i=map.begin(); i!=map.end(); ++i) {
            QList<QString> tmp = i.value();  //List of adjacent worlds od each world
            for (int k = 0; k<temp.size();k++) {
                 QJsonObject varsValue;
                 QJsonArray variablesValue;
                for (int m = 0; m < valueOfVariables.size(); m++) {
                    QString world, variable;
                    bool value;
                    std::tie(world, variable, value) = valueOfVariables[m];
                    if (i.key() == world) {
                        varsValue.insert("Name", QJsonValue::fromVariant(variable));
                        varsValue.insert("Value",QJsonValue::fromVariant(value));
                         variablesValue.push_back(varsValue);
                    }

                }
                wlrdInfo.insert("Variables",  variablesValue);
                if (i.key() == temp[k]) {
                    QJsonArray adjcWrld;
                    wlrdInfo.insert("Name", QJsonValue::fromVariant(temp[k]));
                    for(int e=0; e<tmp.size(); e++) adjcWrld.push_back(tmp[e]);
                    wlrdInfo.insert("AdjWorlds", adjcWrld);
                    worlds.push_back(wlrdInfo);
                }
           }
        }
    }
    jsontx.insert("Worlds", worlds);

    //Saving JSON file
    QJsonDocument doc(jsontx);
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Json File"), QString(), tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(saveFileName+ ".json");
    if (!jsonFile.open(QIODevice::WriteOnly)) return;
    jsonFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Close file
}

void MainWindow::on_pushButton_2_clicked() {
    QString selectedWrld = ui->comboBox_2->currentText();
    QString temp = ui->lineEdit_3->text();
    QList<QString> adjWorlds;
    adjWorlds.append(temp.split(','));
    QMap<QString, QList<QString>> mapOfAdjWrld;
    mapOfAdjWrld.insert(selectedWrld, adjWorlds);
    listAllAdjWrlds.append(mapOfAdjWrld);
    setAdjcWorlds(listAllAdjWrlds);
    ui->lineEdit_3->clear();
}

void MainWindow::on_pushButton_3_clicked() {
     QString selectedWrld = ui->comboBox_3->currentText();
     QList<QString> trueVar;
     QList<QString> falseVar;
     QString trueV = ui->lineEdit_5->text();
     QString falseV = ui->lineEdit_6->text();
     if(trueV.size() != 0) trueVar.append(trueV.split(','));
     if(falseV.size() != 0) falseVar.append(falseV.split(','));

     std::tuple<QString,QString, bool> vars;
     if(trueVar.size() != 0) {
         for (int i = 0; i< trueVar.size(); i++) {
             vars = std::make_tuple(selectedWrld, trueVar[i], true);
             varValue.append(vars);
         }
     }

     if(falseVar.size() != 0) {
         for (int i = 0; i< falseVar.size(); i++) {
              vars = std::make_tuple(selectedWrld, falseVar[i], false);
              varValue.append(vars);
         }
     }

     setValueOfVarible(varValue);
     ui->lineEdit_5->clear();
     ui->lineEdit_6->clear();
}
