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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->comboBox->addItem("K-logic");
    ui->comboBox->addItem("T-logic");
    ui->comboBox->addItem("S4-logic");
    ui->comboBox->addItem("S5-logic");
    ui->comboBox->addItem("D-logic");
    this->setWindowTitle("Create .json file");
    ui->groupBox->setStyleSheet("QGroupBox {  border: 1px solid gray;}");
    ui->groupBox_2->setStyleSheet("QGroupBox {  border: 1px solid gray;}");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_lineEdit_2_editingFinished() {
    listOfWorldNames.clear();
    ui->comboBox_2->clear();
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
