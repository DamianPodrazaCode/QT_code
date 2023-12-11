/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
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
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *le_send_ip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *le_send_port;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_send;
    QPushButton *pb_send;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *le_read_port;
    QPushButton *pb_bind;
    QListWidget *lw_read;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(653, 388);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        le_send_ip = new QLineEdit(groupBox);
        le_send_ip->setObjectName("le_send_ip");
        le_send_ip->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(le_send_ip);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        le_send_port = new QLineEdit(groupBox);
        le_send_port->setObjectName("le_send_port");
        le_send_port->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(le_send_port);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        le_send = new QLineEdit(groupBox);
        le_send->setObjectName("le_send");

        horizontalLayout_3->addWidget(le_send);

        pb_send = new QPushButton(groupBox);
        pb_send->setObjectName("pb_send");

        horizontalLayout_3->addWidget(pb_send);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        le_read_port = new QLineEdit(groupBox_2);
        le_read_port->setObjectName("le_read_port");
        le_read_port->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(le_read_port);

        pb_bind = new QPushButton(groupBox_2);
        pb_bind->setObjectName("pb_bind");
        pb_bind->setCheckable(true);

        horizontalLayout_4->addWidget(pb_bind);


        verticalLayout->addLayout(horizontalLayout_4);

        lw_read = new QListWidget(groupBox_2);
        lw_read->setObjectName("lw_read");

        verticalLayout->addWidget(lw_read);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 653, 21));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Send UDP", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP adress:", nullptr));
        le_send_ip->setText(QCoreApplication::translate("MainWindow", "255.255.255.255", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        le_send_port->setText(QCoreApplication::translate("MainWindow", "3333", nullptr));
        le_send->setText(QCoreApplication::translate("MainWindow", "TEXT to send", nullptr));
        pb_send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Read UDP", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        le_read_port->setText(QCoreApplication::translate("MainWindow", "3333", nullptr));
        pb_bind->setText(QCoreApplication::translate("MainWindow", "Bind", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
