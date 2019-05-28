#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QObject>
#include<QRegion>
#include "graphwidget.h"
#include "cvor.h"
#include <QWidget>
#include <iostream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    GraphWidget *w = new GraphWidget();
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("ToDo validiranje....");

    //NEĆE DA SE RESIZE URADI????
    msgBox.resize(1000,1000);
    msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
     QString imeFajla = QFileDialog::getOpenFileName(this,tr("Otvori"),"",tr("LogicToolbox (*.json)"));
}
/*
void MainWindow::postaviPutanju(QString s) {
    this->putanja = s;
}

QString MainWindow::vratiPutanju() {
    return putanja;
}*/

