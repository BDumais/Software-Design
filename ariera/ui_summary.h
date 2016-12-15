/********************************************************************************
** Form generated from reading UI file 'summary.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMMARY_H
#define UI_SUMMARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Summary
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *graphSelector;
    QComboBox *graphChoice;
    QComboBox *nameBox;
    QComboBox *dateSelector;
    QPushButton *pushButton_6;
    QCustomPlot *graphWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Summary)
    {
        if (Summary->objectName().isEmpty())
            Summary->setObjectName(QStringLiteral("Summary"));
        Summary->resize(1011, 609);
        Summary->setMinimumSize(QSize(1000, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/img/image/banana.png"), QSize(), QIcon::Normal, QIcon::Off);
        Summary->setWindowIcon(icon);
        centralWidget = new QWidget(Summary);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout_3->addWidget(label_2);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(0, 25));
        label_4->setMaximumSize(QSize(16777215, 25));
        QFont font1;
        font1.setPointSize(14);
        label_4->setFont(font1);

        verticalLayout_3->addWidget(label_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(label_3);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(100, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(lineEdit);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(100, 30));
        lineEdit_2->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(lineEdit_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 30));
        pushButton_5->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(400, 400));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphSelector = new QComboBox(widget);
        graphSelector->setObjectName(QStringLiteral("graphSelector"));
        graphSelector->setMinimumSize(QSize(100, 25));
        graphSelector->setMaximumSize(QSize(130, 22));

        horizontalLayout_2->addWidget(graphSelector);

        graphChoice = new QComboBox(widget);
        graphChoice->setObjectName(QStringLiteral("graphChoice"));
        graphChoice->setMinimumSize(QSize(150, 25));
        graphChoice->setMaximumSize(QSize(350, 16777215));

        horizontalLayout_2->addWidget(graphChoice);

        nameBox = new QComboBox(widget);
        nameBox->setObjectName(QStringLiteral("nameBox"));
        nameBox->setMinimumSize(QSize(0, 25));
        nameBox->setMaximumSize(QSize(350, 16777215));

        horizontalLayout_2->addWidget(nameBox);

        dateSelector = new QComboBox(widget);
        dateSelector->setObjectName(QStringLiteral("dateSelector"));
        dateSelector->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(dateSelector);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout_2);

        graphWidget = new QCustomPlot(widget);
        graphWidget->setObjectName(QStringLiteral("graphWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphWidget->sizePolicy().hasHeightForWidth());
        graphWidget->setSizePolicy(sizePolicy);
        graphWidget->setMinimumSize(QSize(500, 378));
        graphWidget->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(graphWidget);

        splitter->addWidget(widget);

        verticalLayout_2->addWidget(splitter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(16777215, 28));

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(16777215, 28));

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        Summary->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Summary);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 21));
        Summary->setMenuBar(menuBar);
        statusBar = new QStatusBar(Summary);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Summary->setStatusBar(statusBar);

        retranslateUi(Summary);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Summary);
    } // setupUi

    void retranslateUi(QMainWindow *Summary)
    {
        Summary->setWindowTitle(QApplication::translate("Summary", "Summary", 0));
        label_2->setText(QApplication::translate("Summary", "Summary", 0));
        label_4->setText(QApplication::translate("Summary", "Department of Medicine", 0));
        label_3->setText(QApplication::translate("Summary", "Date Range Selected: ", 0));
        label->setText(QApplication::translate("Summary", ":", 0));
        pushButton->setText(QApplication::translate("Summary", "Filter", 0));
        pushButton_5->setText(QApplication::translate("Summary", "Clear", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Summary", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Summary", "Tab 2", 0));
        graphSelector->clear();
        graphSelector->insertItems(0, QStringList()
         << QApplication::translate("Summary", "Bar Graph", 0)
         << QApplication::translate("Summary", "Scatter Plot", 0)
        );
        pushButton_6->setText(QApplication::translate("Summary", "Export to PDF", 0));
        pushButton_3->setText(QApplication::translate("Summary", "Back", 0));
        pushButton_4->setText(QApplication::translate("Summary", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class Summary: public Ui_Summary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMMARY_H
