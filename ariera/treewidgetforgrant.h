#ifndef TREEWIDGETFORGRANT_H
#define TREEWIDGETFORGRANT_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <vector>
#include "Database.h"
#include "Preprocessor.h"
#include "GrantsAndFundingFields.h"
#include "FieldMatchFilter.h"
#include <iostream>
#include <vector>
#include <string>
#include <QDebug>
#include <QtCore>
#include <cstdlib>
#include <QMessageBox>
#include <algorithm>
#include "dashboard.h"
#include "qcustomplot.h"
#include "treewidgetforgrant.h"



class TreeWidgetForGrant
{
public:
    TreeWidgetForGrant();
    ~TreeWidgetForGrant();
    QTreeWidgetItem* AddRoot(QString name, QString totalResearch, QString totalFund);
    QTreeWidgetItem* AddChild(QTreeWidgetItem *par, QString name, QString totalResearch, QString totalFund);
    void fillTreeWidgetForGrant(Database &db, int earliest, int latest);
    void PrintChildNodes(QTreeWidgetItem *parent, vector<vector<string>> &result);

    QTreeWidget* getCreateTreeWidget();
private:
    QTreeWidget *createtreewidget;

};

#endif // TREEWIDGETFORGRANT_H
