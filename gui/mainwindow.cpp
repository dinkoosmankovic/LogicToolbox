#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QObject>
#include<QRegion>
#include "graphwidget.h"
#include "node.h"
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

QList<QMap<QString, QList<QString>>> listAllAdjWrlds;
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

    /*QJsonObject recordObject;
      recordObject.insert("FirstName", QJsonValue::fromVariant("John"));
      recordObject.insert("LastName", QJsonValue::fromVariant("Doe"));
      recordObject.insert("Age", QJsonValue::fromVariant(43));

      QJsonObject addressObject;
      addressObject.insert("Street", "Downing Street 10");
      addressObject.insert("City", "London");
      addressObject.insert("Country", "Great Britain");
      recordObject.insert("Address", addressObject);

      QJsonArray phoneNumbersArray;
      phoneNumbersArray.push_back("+44 1234567");
      phoneNumbersArray.push_back("+44 2345678");
      recordObject.insert("Phone Numbers", phoneNumbersArray);

      QJsonDocument doc(recordObject);
      qDebug() << doc.toJson();*/
    setLogicType(ui->comboBox->currentText());
    setUniverseName(ui->lineEdit->text());

    QJsonObject jsontx;

    //Inserting universe name and type of logic
    jsontx.insert("Name", QJsonValue::fromVariant(getUniverseName()));
    jsontx.insert("Logic", QJsonValue::fromVariant(getLogicType()));

    //Inserting variables name
    QList<QString> temp = getVarNames();
    QJsonArray varName;
    for(int i = 0; i<temp.size(); i++) varName.push_back(temp[i]);
    jsontx.insert("VariablesName", varName);

    QJsonDocument doc(jsontx);

    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Json File"), QString(), tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(saveFileName+ ".json");
    if (!jsonFile.open(QIODevice::WriteOnly)) return;
    jsonFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Close file
}

void MainWindow::on_pushButton_2_clicked()
{

    ui->lineEdit_3->clear();
    QString selectedWrld = ui->comboBox_2->currentText();
    QString temp = ui->lineEdit_3->text();
    QList<QString> adjWorlds;
    adjWorlds.append(temp.split(','));
    QMap<QString, QList<QString>> mapOfAdjWrld;
    mapOfAdjWrld.insert(selectedWrld, adjWorlds);
    listAllAdjWrlds.append(mapOfAdjWrld);
    setAdjcWorlds(listAllAdjWrlds);

   /* QList<QMap<QString, bool>> worldVariables;

    for(QMap<)
    for (QMap<QString, bool> mapa : this->worldVariables) {
        QMap<QString, bool>::iterator i;
        for (i = mapa.begin(); i != mapa.end(); ++i) {
            QString varijabla = i.key();
            QString vrijednost;
            if (i.value()) vrijednost = "True";
            else vrijednost = "False";
            temp += " " + varijabla + " : " + vrijednost + "\n";
        }
    }*/
}

void MainWindow::on_pushButton_3_clicked() {
     QString selectedWrld = ui->comboBox_3->currentText();
     QList<QString> trueVar;
     QList<QString> falseVar;
     QString trueV = ui->lineEdit_5->text();
     QString falseV = ui->lineEdit_6->text();
     trueVar.append(trueV.split(','));
     falseVar.append(falseV.split(','));
     for (int i = 0; i< trueVar.size(); i++) trueVar[i] = trueVar[i] + "T";
     for (int i = 0; i< falseVar.size(); i++) falseVar[i] = falseVar[i] + "F";
     for (int i = 0; i<trueVar.size(); i++) qDebug() << trueVar[i];


    // qDebug() << selectedWrld;
}
