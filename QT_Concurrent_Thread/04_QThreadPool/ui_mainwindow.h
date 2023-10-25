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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_th1;
    QPushButton *pb_th2;
    QPushButton *pb_th3;
    QPushButton *pb_th4;
    QPushButton *pb_th5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *l_th1;
    QLabel *l_th2;
    QLabel *l_th3;
    QLabel *l_th4;
    QLabel *l_th5;
    QPushButton *pb_th_all;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(541, 157);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pb_th1 = new QPushButton(centralwidget);
        pb_th1->setObjectName("pb_th1");
        pb_th1->setCheckable(true);
        pb_th1->setChecked(false);

        horizontalLayout->addWidget(pb_th1);

        pb_th2 = new QPushButton(centralwidget);
        pb_th2->setObjectName("pb_th2");
        pb_th2->setCheckable(true);
        pb_th2->setChecked(false);

        horizontalLayout->addWidget(pb_th2);

        pb_th3 = new QPushButton(centralwidget);
        pb_th3->setObjectName("pb_th3");
        pb_th3->setCheckable(true);
        pb_th3->setChecked(false);

        horizontalLayout->addWidget(pb_th3);

        pb_th4 = new QPushButton(centralwidget);
        pb_th4->setObjectName("pb_th4");
        pb_th4->setCheckable(true);
        pb_th4->setChecked(false);

        horizontalLayout->addWidget(pb_th4);

        pb_th5 = new QPushButton(centralwidget);
        pb_th5->setObjectName("pb_th5");
        pb_th5->setCheckable(true);
        pb_th5->setChecked(false);

        horizontalLayout->addWidget(pb_th5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        l_th1 = new QLabel(centralwidget);
        l_th1->setObjectName("l_th1");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        l_th1->setFont(font);
        l_th1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(l_th1);

        l_th2 = new QLabel(centralwidget);
        l_th2->setObjectName("l_th2");
        l_th2->setFont(font);
        l_th2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(l_th2);

        l_th3 = new QLabel(centralwidget);
        l_th3->setObjectName("l_th3");
        l_th3->setFont(font);
        l_th3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(l_th3);

        l_th4 = new QLabel(centralwidget);
        l_th4->setObjectName("l_th4");
        l_th4->setFont(font);
        l_th4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(l_th4);

        l_th5 = new QLabel(centralwidget);
        l_th5->setObjectName("l_th5");
        l_th5->setFont(font);
        l_th5->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(l_th5);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        pb_th_all = new QPushButton(centralwidget);
        pb_th_all->setObjectName("pb_th_all");
        pb_th_all->setCheckable(true);
        pb_th_all->setChecked(false);

        verticalLayout_2->addWidget(pb_th_all);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 541, 21));
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
        pb_th1->setText(QCoreApplication::translate("MainWindow", "thread1 OFF", nullptr));
        pb_th2->setText(QCoreApplication::translate("MainWindow", "thread2 OFF", nullptr));
        pb_th3->setText(QCoreApplication::translate("MainWindow", "thread3 OFF", nullptr));
        pb_th4->setText(QCoreApplication::translate("MainWindow", "thread4 OFF", nullptr));
        pb_th5->setText(QCoreApplication::translate("MainWindow", "thread5 OFF", nullptr));
        l_th1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        l_th2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        l_th3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        l_th4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        l_th5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pb_th_all->setText(QCoreApplication::translate("MainWindow", "thread all OFF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
