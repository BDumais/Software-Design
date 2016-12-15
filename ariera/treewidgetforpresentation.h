#ifndef TREEWIDGETFORPRESENTATION_H
#define TREEWIDGETFORPRESENTATION_H

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

class TreeWidgetForPresentation
{
public:
    TreeWidgetForPresentation();
    ~TreeWidgetForPresentation();
    QTreeWidgetItem* AddRoot(QString name, QString total);
    QTreeWidgetItem* AddChild(QTreeWidgetItem *par, QString name, QString total);
    void fillTreeWidgetForPresentation(Database &db, int earliest, int latest);
    void PrintChildNodes(QTreeWidgetItem *parent, vector<vector<string>> &result);

    QTreeWidget* getCreateTreeWidget();

private:
    QTreeWidget *createtreewidget;
};

#endif // TREEWIDGETFORPUBLICATION_H
