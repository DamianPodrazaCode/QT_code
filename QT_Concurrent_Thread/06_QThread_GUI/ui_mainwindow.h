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
#include <QtWidgets/QLabel>
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
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pb_th1;
    QPushButton *pb_th2;
    QLabel *l_th1;
    QLabel *l_th2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(451, 140);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pb_th1 = new QPushButton(centralwidget);
        pb_th1->setObjectName("pb_th1");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        pb_th1->setFont(font);
        pb_th1->setCheckable(true);

        gridLayout->addWidget(pb_th1, 0, 0, 1, 1);

        pb_th2 = new QPushButton(centralwidget);
        pb_th2->setObjectName("pb_th2");
        pb_th2->setFont(font);
        pb_th2->setCheckable(true);

        gridLayout->addWidget(pb_th2, 0, 1, 1, 1);

        l_th1 = new QLabel(centralwidget);
        l_th1->setObjectName("l_th1");
        l_th1->setFont(font);
        l_th1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(l_th1, 1, 0, 1, 1);

        l_th2 = new QLabel(centralwidget);
        l_th2->setObjectName("l_th2");
        l_th2->setFont(font);
        l_th2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(l_th2, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 451, 21));
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
        pb_th1->setText(QCoreApplication::translate("MainWindow", "Thread1 On", nullptr));
        pb_th2->setText(QCoreApplication::translate("MainWindow", "Thread1 On", nullptr));
        l_th1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        l_th2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
