/********************************************************************************
** Form generated from reading UI file 'qtimagedisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTIMAGEDISPLAY_H
#define UI_QTIMAGEDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QClickLabel.hpp"

QT_BEGIN_NAMESPACE

class Ui_QTImageDisplayClass
{
public:
    QAction *actionOpen_iamge_file;
    QAction *actionExit;
    QWidget *centralWidget;
    QClickLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTImageDisplayClass)
    {
        if (QTImageDisplayClass->objectName().isEmpty())
            QTImageDisplayClass->setObjectName(QString::fromUtf8("QTImageDisplayClass"));
        QTImageDisplayClass->resize(600, 850);
        actionOpen_iamge_file = new QAction(QTImageDisplayClass);
        actionOpen_iamge_file->setObjectName(QString::fromUtf8("actionOpen_iamge_file"));
        actionExit = new QAction(QTImageDisplayClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(QTImageDisplayClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QClickLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 601, 791));
        QTImageDisplayClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTImageDisplayClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        QTImageDisplayClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTImageDisplayClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTImageDisplayClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTImageDisplayClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTImageDisplayClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_iamge_file);
        menuFile->addAction(actionExit);

        retranslateUi(QTImageDisplayClass);

        QMetaObject::connectSlotsByName(QTImageDisplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTImageDisplayClass)
    {
        QTImageDisplayClass->setWindowTitle(QApplication::translate("QTImageDisplayClass", "QTImageDisplay", nullptr));
        actionOpen_iamge_file->setText(QApplication::translate("QTImageDisplayClass", "open image file", nullptr));
        actionExit->setText(QApplication::translate("QTImageDisplayClass", "exit", nullptr));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("QTImageDisplayClass", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTImageDisplayClass: public Ui_QTImageDisplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTIMAGEDISPLAY_H
