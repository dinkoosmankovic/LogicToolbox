/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox;
    QComboBox *comboBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_4;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QComboBox *comboBox_3;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1135, 660);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 131, 17));
        QFont font;
        font.setFamily(QStringLiteral("Arimo"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 181, 17));
        label_2->setFont(font);
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(240, 10, 221, 33));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(240, 60, 221, 33));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 130, 221, 51));
        label_3->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 210, 201, 61));
        label_5->setFont(font);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(240, 210, 221, 33));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 340, 451, 241));
        groupBox->setFont(font);
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(10, 110, 171, 33));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 171, 17));
        QFont font1;
        font1.setPointSize(11);
        label_6->setFont(font1);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(210, 50, 231, 61));
        label_7->setFont(font1);
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(210, 110, 221, 33));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 180, 191, 51));
        QFont font2;
        font2.setPointSize(10);
        pushButton_2->setFont(font2);
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(240, 120, 221, 33));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(580, 10, 511, 491));
        groupBox_2->setFont(font);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 50, 171, 17));
        label_8->setFont(font1);
        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(260, 40, 241, 33));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 220, 251, 61));
        label_9->setFont(font1);
        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(260, 220, 241, 33));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 340, 251, 61));
        label_10->setFont(font1);
        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(260, 340, 241, 33));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 130, 161, 17));
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(260, 120, 241, 33));
        lineEdit_7->setReadOnly(true);
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 440, 171, 41));
        pushButton_3->setFont(font2);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(740, 540, 201, 51));
        QFont font3;
        font3.setFamily(QStringLiteral("Arimo"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1135, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LogicToolbox", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Select logic type:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Enter universe name:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Enter names of the variables</p><p>(with comma):</p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Enter names of the worlds </p><p>(with comma):</p></body></html>", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Adjacent worlds", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Select world:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Enter it's adjacent worlds</p><p>(with comma):</p></body></html>", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add adjacent world", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Variables value", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Select world:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Enter variables which are 'TRUE'</p><p>(with comma):</p></body></html>", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Enter variables which are 'FALSE'</p><p>(with comma):</p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Available variables:", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Add variables", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Create file", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
