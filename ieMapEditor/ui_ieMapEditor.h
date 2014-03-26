/********************************************************************************
** Form generated from reading UI file 'ieMapEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IEMAPEDITOR_H
#define UI_IEMAPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ieMapEditor
{
public:
    QWidget *centralWidget;
    QWidget *oglWindow;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *ieMapEditor)
    {
        if (ieMapEditor->objectName().isEmpty())
            ieMapEditor->setObjectName(QStringLiteral("ieMapEditor"));
        ieMapEditor->resize(1024, 768);
        ieMapEditor->setMinimumSize(QSize(1024, 768));
        ieMapEditor->setMaximumSize(QSize(1024, 768));
        ieMapEditor->setStyleSheet(QStringLiteral("background-color: rgb(128, 128, 128);"));
        centralWidget = new QWidget(ieMapEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        oglWindow = new QWidget(centralWidget);
        oglWindow->setObjectName(QStringLiteral("oglWindow"));
        oglWindow->setGeometry(QRect(19, 9, 731, 721));
        ieMapEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ieMapEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 22));
        ieMapEditor->setMenuBar(menuBar);

        retranslateUi(ieMapEditor);

        QMetaObject::connectSlotsByName(ieMapEditor);
    } // setupUi

    void retranslateUi(QMainWindow *ieMapEditor)
    {
        ieMapEditor->setWindowTitle(QApplication::translate("ieMapEditor", "ieMapEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class ieMapEditor: public Ui_ieMapEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IEMAPEDITOR_H
