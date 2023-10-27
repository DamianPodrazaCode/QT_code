/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(738, 220);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border : none;\n"
"	color : white;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : red;\n"
"	border-radius : 10;\n"
"}\n"
"QPushButton::hover{\n"
"	border : 2px solid #4CAF50;\n"
"	color : grey;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : red;\n"
"	border-radius : 10;\n"
"}\n"
"QPushButton::pressed{\n"
"	border : none;\n"
"	color : white;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : blue;\n"
"	border-radius : 10;\n"
"}"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border : none;\n"
"	color : white;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : red;\n"
"	border-radius : 10;\n"
"}\n"
"QPushButton::hover{\n"
"	border : 2px solid #4CAF50;\n"
"	color : grey;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : red;\n"
"	border-radius : 10;\n"
"}\n"
"QPushButton::checked{\n"
"	border : 2px solid #4CAF50;\n"
"	color : red;\n"
"	font : italic 28pt \"Arial\";\n"
"	background :black;\n"
"	border-radius : 10;\n"
"}\n"
"QPushButton::pressed{\n"
"	border : none;\n"
"	color : white;\n"
"	font : italic 28pt \"Arial\";\n"
"	background : blue;\n"
"	border-radius : 10;\n"
"}"));
        pushButton_2->setCheckable(true);

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 738, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "ToggleButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
