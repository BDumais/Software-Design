#ifndef TREEWIDGETFORPUBLICATION_H
#define TREEWIDGETFORPUBLICATION_H

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

class Database;

class TreeWidgetForPublication
{
public:
    TreeWidgetForPublication();
    ~TreeWidgetForPublication();
    QTreeWidgetItem* AddRoot(QString name, QString total);
    QTreeWidgetItem* AddChild(QTreeWidgetItem *par, QString name, QString total);
    void fillTreeWidgetForPublication(Database &db, int earliest, int latest);
    void PrintChildNodes(QTreeWidgetItem *parent, vector<vector<string>> &result);

    QTreeWidget* getCreateTreeWidget();

private:
    QTreeWidget *createtreewidget;
    //struct publicationSummary sum;
   // Database *db;
};

#endif // TREEWIDGETFORPUBLICATION_H
