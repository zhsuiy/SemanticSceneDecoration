/********************************************************************************
** Form generated from reading UI file 'displayscene.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYSCENE_H
#define UI_DISPLAYSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplaySceneClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DisplaySceneClass)
    {
        if (DisplaySceneClass->objectName().isEmpty())
            DisplaySceneClass->setObjectName(QStringLiteral("DisplaySceneClass"));
        DisplaySceneClass->resize(600, 400);
        menuBar = new QMenuBar(DisplaySceneClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DisplaySceneClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DisplaySceneClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DisplaySceneClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DisplaySceneClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DisplaySceneClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DisplaySceneClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DisplaySceneClass->setStatusBar(statusBar);

        retranslateUi(DisplaySceneClass);

        QMetaObject::connectSlotsByName(DisplaySceneClass);
    } // setupUi

    void retranslateUi(QMainWindow *DisplaySceneClass)
    {
        DisplaySceneClass->setWindowTitle(QApplication::translate("DisplaySceneClass", "DisplayScene", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplaySceneClass: public Ui_DisplaySceneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYSCENE_H
