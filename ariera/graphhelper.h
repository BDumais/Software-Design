#ifndef GRAPHHELPER_H
#define GRAPHHELPER_H

#include <vector>
#include <string.h>
#include "qcustomplot.h"
//#include "Database.h"
//#include "dashboard.h"
//#include "summary.h"

#define BAR_GRAPH       0
//#define PIE_CHART       1
#define SCATTER_PLOT    1

#define GRANT           1
#define PUBLICATION     2
#define TEACHING        3
#define PRESENTATION     4

class GraphHelper
{
public:
    GraphHelper(int graphType,int graphChoice, int dataType,int dateChoice, int earliestDate,int latestDate);

    void makeGraph(QCustomPlot* plot, std::vector<std::vector<std::string>> &results);
    void setTitle(QCPPlotTitle* title);
private:
    int dataType;
    int typeGraph;                      //type of graph from combobox (bar,scatter etc)
    int dateChoice;                     //choice of date by combobox selector
    int earliest;
    int latest;
    int numYears;
    int graphChoice;                    //choice of graph from combobox
    bool bShowEmptyData = false;        //flag for displaying years that have no associated data

    void setYAxisTitle(QCustomPlot* plot);
    void setYAxis(QCustomPlot* plot);
    void setXAxis(QCustomPlot* plot, QVector<QString> labels,QVector<double> ticks);
    QVector<QString> getData(double* amount,std::vector<std::vector<std::string>> &results);
    void sumResultsAmount(double* barAmount,std::vector<std::vector<std::string>> &results);
    void sumResultsAmount2(double* pubType, std::vector<std::vector<std::string>> &results);
    QVector<QString> sumResultsType(double* barAmount, std::vector<std::vector<std::string>> &results);

    void graphSumAmtVsDate(QCustomPlot *plot, std::vector<std::vector<std::string> > &results);
    void graphAmtByType(QCustomPlot *plot, std::vector<std::vector<std::string> > &results);
};

#endif // GRAPHHELPER_H
