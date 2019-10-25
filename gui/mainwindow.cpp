//
// Created by Alma Ibrašimović, january 2019.
//

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
#include <QLabel>
#include <QWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"
#include "node.h"

//PRILIKOM KREIRANJE JSONA ALFABETSKI KREIRA

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
    ui->pushButton->setDisabled(true);
    ui->pushButton->setToolTip("You have to enter all atributes for the universe before creating JSON file!");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_lineEdit_2_editingFinished() {
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("Error");
    wdg->resize(400, 60);
    QLabel *label = new QLabel(wdg);
    QFont f("Times New Roman", 12, QFont::Bold);
    label->setFont(f);
    listOfWorldNames.clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    bool cond = false;
    QString worlds = ui->lineEdit_2->text();
    QList<QString> wrldNms;
    wrldNms.append(worlds.split(','));
    setWorldNames(wrldNms);
    QList<QString> temp = getNamesOfTheWorlds();
    QList<QString> var = getVarNames();
    for (int i = 0; i<var.size(); i++) {
        foreach (auto j, getNamesOfTheWorlds()) {
            if (var[i] == j) cond = true;
        }
    }
    if (cond) {
        label->setText(" Name of the world cannot be the same as variable!");
        wdg->resize(380, 60);
        wdg->show();
    }
    if(!cond) {
        for (int i=0; i<getNumOfWorlds(); i++) {
            ui->comboBox_2->addItem(temp[i]);
            ui->comboBox_3->addItem(temp[i]);
        }
    }
}

void MainWindow::on_lineEdit_4_editingFinished() {

    QString variables = ui->lineEdit_4->text();
    ui->lineEdit_7->setText(variables);
    QList<QString> varNames;
    varNames.append(variables.split(','));
    setVarNames(varNames);
    QList<QString> temp = getNamesOfTheWorlds();
    if (temp.size() != 0 && adjcWorlds.size() == 0) {
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        for (int i=0; i<getNumOfWorlds(); i++) {
            ui->comboBox_2->addItem(temp[i]);
            ui->comboBox_3->addItem(temp[i]);
        }
    }
}

void MainWindow::on_pushButton_clicked() {
    bool condB = false;
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("Error");
    wdg->resize(400, 60);
    QLabel *label = new QLabel(wdg);
    QFont f("Times New Roman", 12, QFont::Bold);
    label->setFont(f);
    setLogicType(ui->comboBox->currentText());
    if (ui->lineEdit->text() != "") {
        condB = true;
        setUniverseName(ui->lineEdit->text());
    }

    if (!condB) {
        label->setText(" You didn't enter universe name!");
        wdg->resize(300, 60);
        wdg->show();
    }

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
    if(condB) {
        QJsonDocument doc(jsontx);
        QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Json File"), QString(), tr("JSON (*.json)"));
        QFileInfo fileInfo(saveFileName);
        QDir::setCurrent(fileInfo.path());
        QFile jsonFile(saveFileName+ ".json");
        if (!jsonFile.open(QIODevice::WriteOnly)) return;
        jsonFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
        jsonFile.close();   // Close file

        //Message box after creating file
        if(fileInfo.path() != "." ){
            wdg->setWindowTitle("Success");
            wdg->resize(263, 60);
            label->setText("  JSON file created successfully!");
            wdg->show();
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
    }
}

void MainWindow::on_pushButton_2_clicked() {

    QWidget *msg = new QWidget;
    msg->setWindowTitle("Error");
    QLabel *label = new QLabel(msg);
    QFont f("Times New Roman", 12, QFont::Bold);
    label->setFont(f);

    QString selectedWrld = ui->comboBox_2->currentText();
    QList<QString> availableWorlds = getNamesOfTheWorlds();
    QString temp = ui->lineEdit_3->text();
    QList<QString> adjWorlds;
    adjWorlds.append(temp.split(','));
    bool exists;
    bool same = false;

    for (int i = 0; i<adjWorlds.size(); i++) {
        exists = false;
        foreach (auto j, availableWorlds) {
            if (adjWorlds[i] == j) exists = true;
        }
    }
    for (int i = 0; i<adjWorlds.size(); i++) {
        if (selectedWrld == adjWorlds[i]) {
            same = true;
            break;
        }
    }

    QMap<QString, QList<QString>> mapOfAdjWrld;
    if(exists && !same) {
        ui->comboBox_2->removeItem(ui->comboBox_2->currentIndex());
        mapOfAdjWrld.insert(selectedWrld, adjWorlds);
        listAllAdjWrlds.append(mapOfAdjWrld);
        setAdjcWorlds(listAllAdjWrlds);
        ui->lineEdit_3->clear();
    }
    else if (!exists) {
        label->setText(" World in adjecent worlds doesn't exist in this universe!");
        msg->resize(390, 60);
        msg->show();
    }
    else if (same) {
        label->setText(" World cannot be connected to itself!");
        msg->resize(300, 60);
        msg->show();
    }
    if (ui->comboBox_2->count() == 0) ui->pushButton_2->setDisabled(true);
    if (ui->comboBox_3->count() == 0 && ui->comboBox_2->count() == 0) ui->pushButton->setDisabled(false);

}

void MainWindow::on_pushButton_3_clicked() {
    //trueVar -list with variables which are true
    //falseVar -list with variables which are false
     QWidget *msg = new QWidget;
     msg->setWindowTitle("Error");
     msg->resize(400, 60);
     QLabel *label = new QLabel(msg);
     QFont f("Times New Roman", 12, QFont::Bold);
     label->setFont(f);
     bool condA = true;
     bool condB = true;
     bool condD = true;
     bool condC = true;
     QString selectedWrld = ui->comboBox_3->currentText();
     QList<QString> allVariables = getVarNames();
     QList<QString> trueVar;
     QList<QString> falseVar;
     QString trueV = ui->lineEdit_5->text();
     QString falseV = ui->lineEdit_6->text();
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

     if(condA && condB && condC && condD) {
         ui->comboBox_3->removeItem(ui->comboBox_3->currentIndex());
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

         if (ui->comboBox_3->count() == 0 && ui->comboBox_2->count() == 0) {
             ui->pushButton->setDisabled(false);
             ui->pushButton->setToolTip("");
         }
    }
    else if (!condA) {
        label->setText("  Variable can't be TRUE and FALSE at the same time!");
        msg->show();
        ui->pushButton->setDisabled(true);
    }
    else if (!condB) {
        label->setText("  You didn't choose value for all variables!");
        msg->resize(300, 60);
        msg->show();
        ui->pushButton->setDisabled(true);
    }
    else if (!condC) {
         label->setText("  Some of the entered variables do not exist!");
         msg->resize(300, 60);
         msg->show();
         ui->pushButton->setDisabled(true);
    }
    else if (!condD) {
         label->setText("  You entered extra variables!");
         msg->resize(300, 60);
         msg->show();
         ui->pushButton->setDisabled(true);
    }
    if (ui->comboBox_3->count() == 0) ui->pushButton_3->setDisabled(true);
}
