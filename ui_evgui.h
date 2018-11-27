/********************************************************************************
** Form generated from reading UI file 'evgui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVGUI_H
#define UI_EVGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EVgui
{
public:
    QWidget *centralWidget;
    QLabel *pic1;
    QLabel *label_9;
    QLineEdit *ratio;
    QLabel *label_8;
    QLabel *label_12;
    QLabel *pic;
    QLabel *label_10;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EVgui)
    {
        if (EVgui->objectName().isEmpty())
            EVgui->setObjectName(QStringLiteral("EVgui"));
        EVgui->resize(588, 351);
        centralWidget = new QWidget(EVgui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pic1 = new QLabel(centralWidget);
        pic1->setObjectName(QStringLiteral("pic1"));
        pic1->setGeometry(QRect(290, 0, 291, 241));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(230, 270, 71, 20));
        label_9->setFrameShadow(QFrame::Plain);
        label_9->setLineWidth(4);
        ratio = new QLineEdit(centralWidget);
        ratio->setObjectName(QStringLiteral("ratio"));
        ratio->setGeometry(QRect(300, 270, 31, 21));
        ratio->setFrame(false);
        ratio->setCursorPosition(1);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(860, 110, 31, 20));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(860, 150, 31, 16));
        pic = new QLabel(centralWidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(0, 0, 281, 241));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(330, 270, 16, 20));
        label_10->setLineWidth(5);
        EVgui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EVgui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 588, 26));
        EVgui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EVgui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EVgui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EVgui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EVgui->setStatusBar(statusBar);

        retranslateUi(EVgui);
        QObject::connect(pic, SIGNAL(linkActivated(QString)), EVgui, SLOT(start()));
        QObject::connect(pic1, SIGNAL(linkActivated(QString)), EVgui, SLOT(process()));

        QMetaObject::connectSlotsByName(EVgui);
    } // setupUi

    void retranslateUi(QMainWindow *EVgui)
    {
        EVgui->setWindowTitle(QApplication::translate("EVgui", "EVgui", Q_NULLPTR));
        pic1->setText(QApplication::translate("EVgui", "\345\244\204\347\220\206\347\224\273\351\235\242", Q_NULLPTR));
        label_9->setText(QApplication::translate("EVgui", "\347\247\270\347\247\206\345\215\240\346\257\224\357\274\232", Q_NULLPTR));
        ratio->setText(QApplication::translate("EVgui", "0", Q_NULLPTR));
        label_8->setText(QApplication::translate("EVgui", "mm", Q_NULLPTR));
        label_12->setText(QApplication::translate("EVgui", "mm", Q_NULLPTR));
        pic->setText(QApplication::translate("EVgui", "\345\216\237\345\233\276", Q_NULLPTR));
        label_10->setText(QApplication::translate("EVgui", "%", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EVgui: public Ui_EVgui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVGUI_H
