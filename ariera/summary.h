#ifndef SUMMARY_H
#define SUMMARY_H

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
#include <string>
#include <QDebug>
#include <QtCore>
#include <cstdlib>
#include <QMessageBox>
#include <algorithm>
#include "dashboard.h"
#include "qcustomplot.h"
#include "treewidgetforgrant.h"
#include "treewidgetforpublication.h"
#include "treewidgetforpresentation.h"
#include "graphhelper.h"
#include <QSettings>
#include <ctime>
#include <QPrinter>

class DashBoard;
class TreeWidgetForGrant;
class TreeWidgetForPublication;
class TreeWidgetForPresentation;

namespace Ui {
class Summary;
}

class Summary : public QMainWindow
{
    Q_OBJECT

public:
    explicit Summary(QString qs,vector<string> listititem, DashBoard *dashb, QWidget *parent = 0);
    ~Summary();
    void testGraph(QCustomPlot *customPlot);
    void loadSettings();
    void saveSettings();
private slots:

    void on_pushButton_clicked(); //filter
    void on_pushButton_3_clicked(); //return back to main window
    void on_pushButton_4_clicked(); //close
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked(); // print graph

    void on_tabWidget_currentChanged(int index);
    void on_nameBox_activated(int index);

    void on_graphChoice_activated(int index);

    void on_graphSelector_activated(int index);

    void on_dateSelector_activated(int index);

private:
    Ui::Summary *ui;
    std::vector<std::string> listVectorTransfered; //contain array of strings with the full path all the file loaded in the main window
    QString stringTransfered;
    DashBoard *dashBoardData;
    Database db;
    TreeWidgetForGrant *GrantSummary;
    TreeWidgetForPublication *PublicationSummary;
    TreeWidgetForPresentation *PresentationSummary;
    QCustomPlot* graph;
    QCPPlotTitle* graphTitle;

    void graphTitleInit();
    void processChoices(std::vector<std::vector<std::string> > &results);
    vector<Filter *> chosenName(vector<Filter *> filters, FieldMatchFilter* nameMatch);
    QVector<QString> cleanDates(QVector<QString> years);
    QVector<QString> sortNames(QVector<QString> names);
    void graphs();
    void processDate(std::vector<std::vector<std::string> > &results);
};

#endif // summary_H
