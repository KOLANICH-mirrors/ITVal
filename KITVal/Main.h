/********************************************************************************
** Form generated from reading ui file 'main.ui'
**
** Created: Tue Mar 6 00:46:49 2007
**      by: Qt User Interface Compiler version 4.2.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *actionOpen_Ruleset;
    QAction *actionOpen_Query;
    QAction *actionSave_Query;
    QAction *actionQuit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionSelect_All;
    QAction *actionExecute_Query;
    QAction *actionNew_Query;
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *queryButton;
    QLabel *label_2;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuExecute;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    actionOpen_Ruleset = new QAction(MainWindow);
    actionOpen_Ruleset->setObjectName(QString::fromUtf8("actionOpen_Ruleset"));
    actionOpen_Query = new QAction(MainWindow);
    actionOpen_Query->setObjectName(QString::fromUtf8("actionOpen_Query"));
    actionSave_Query = new QAction(MainWindow);
    actionSave_Query->setObjectName(QString::fromUtf8("actionSave_Query"));
    actionQuit = new QAction(MainWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionCut = new QAction(MainWindow);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    actionCopy = new QAction(MainWindow);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    actionPaste = new QAction(MainWindow);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    actionSelect_All = new QAction(MainWindow);
    actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
    actionExecute_Query = new QAction(MainWindow);
    actionExecute_Query->setObjectName(QString::fromUtf8("actionExecute_Query"));
    actionNew_Query = new QAction(MainWindow);
    actionNew_Query->setObjectName(QString::fromUtf8("actionNew_Query"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 270, 102, 19));
    queryButton = new QPushButton(centralwidget);
    queryButton->setObjectName(QString::fromUtf8("queryButton"));
    queryButton->setGeometry(QRect(650, 510, 141, 29));
    label_2 = new QLabel(centralwidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(0, 500, 116, 19));
    textBrowser_2 = new QTextBrowser(centralwidget);
    textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
    textBrowser_2->setGeometry(QRect(0, 300, 801, 201));
    textBrowser = new QTextBrowser(centralwidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setGeometry(QRect(0, 0, 801, 271));
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 31));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    menuExecute = new QMenu(menubar);
    menuExecute->setObjectName(QString::fromUtf8("menuExecute"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menubar->addAction(menuExecute->menuAction());
    menuFile->addAction(actionNew_Query);
    menuFile->addAction(actionOpen_Query);
    menuFile->addSeparator();
    menuFile->addAction(actionSave_Query);
    menuFile->addSeparator();
    menuFile->addAction(actionOpen_Ruleset);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addAction(actionSelect_All);
    menuExecute->addAction(actionExecute_Query);

    retranslateUi(MainWindow);

    QSize size(800, 600);
    size = size.expandedTo(MainWindow->minimumSizeHint());
    MainWindow->resize(size);


    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionOpen_Ruleset->setText(QApplication::translate("MainWindow", "Open Ruleset", 0, QApplication::UnicodeUTF8));
    actionOpen_Query->setText(QApplication::translate("MainWindow", "Open Query", 0, QApplication::UnicodeUTF8));
    actionSave_Query->setText(QApplication::translate("MainWindow", "Save Query", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    actionCut->setText(QApplication::translate("MainWindow", "Cut", 0, QApplication::UnicodeUTF8));
    actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
    actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
    actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", 0, QApplication::UnicodeUTF8));
    actionExecute_Query->setText(QApplication::translate("MainWindow", "Execute Query", 0, QApplication::UnicodeUTF8));
    actionNew_Query->setText(QApplication::translate("MainWindow", "New Query", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "Rule Window", 0, QApplication::UnicodeUTF8));
    queryButton->setToolTip(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Garamond [monotype]'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">Execute the query and generate new results.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    queryButton->setWhatsThis(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Garamond [monotype]'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">This button allows you to execute the query and generate a result set.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    queryButton->setText(QApplication::translate("MainWindow", "Execute Query", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "Query Window", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    menuExecute->setTitle(QApplication::translate("MainWindow", "Execute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAIN_H
