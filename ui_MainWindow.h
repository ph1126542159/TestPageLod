/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Model;
    QAction *actionOpen_File;
    QAction *actionSave_As_File;
    QAction *actionCreate_Model;
    QAction *actionBig_Scene;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuTestPageLod;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionLoad_Model = new QAction(MainWindow);
        actionLoad_Model->setObjectName("actionLoad_Model");
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName("actionOpen_File");
        actionSave_As_File = new QAction(MainWindow);
        actionSave_As_File->setObjectName("actionSave_As_File");
        actionCreate_Model = new QAction(MainWindow);
        actionCreate_Model->setObjectName("actionCreate_Model");
        actionBig_Scene = new QAction(MainWindow);
        actionBig_Scene->setObjectName("actionBig_Scene");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menuTestPageLod = new QMenu(menubar);
        menuTestPageLod->setObjectName("menuTestPageLod");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuTestPageLod->menuAction());
        menu->addAction(actionLoad_Model);
        menu->addAction(actionOpen_File);
        menu->addAction(actionSave_As_File);
        menuTestPageLod->addAction(actionCreate_Model);
        menuTestPageLod->addAction(actionBig_Scene);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad_Model->setText(QCoreApplication::translate("MainWindow", "Load Model", nullptr));
        actionOpen_File->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        actionSave_As_File->setText(QCoreApplication::translate("MainWindow", "Save As File", nullptr));
        actionCreate_Model->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\250\241\345\236\213", nullptr));
        actionBig_Scene->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\345\244\247\345\236\213\345\234\272\346\231\257", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\250\241\345\236\213", nullptr));
        menuTestPageLod->setTitle(QCoreApplication::translate("MainWindow", "TestPageLod", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
