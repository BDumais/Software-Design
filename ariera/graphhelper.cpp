#include "graphhelper.h"
#include "iostream"

GraphHelper::GraphHelper(int graphType, int graphChoice, int dataType, int dateChoice, int earliestDate, int latestDate)
{
    this->dateChoice = dateChoice;
    this->dataType = dataType;
    this->graphChoice = graphChoice;
    typeGraph = graphType;
    earliest = earliestDate;
    latest = latestDate;
    numYears = latest - earliest + 1;
}

void GraphHelper::makeGraph(QCustomPlot* plot, std::vector<std::vector<std::string> > &results)
{
    switch(graphChoice){
    case 0:
        graphSumAmtVsDate(plot,results);
        break;
    case 1:
        if(dataType == PUBLICATION)
            graphAmtByType(plot,results);
        else if(dataType == PRESENTATION)
            graphAmtByType(plot,results);
        else if(dataType == GRANT)
            graphSumAmtVsDate(plot,results);
        break;
    case 2:
        if(dataType == GRANT)
            graphAmtByType(plot,results);
        break;
    }
}

void GraphHelper::setYAxis(QCustomPlot* plot)
{
    //Format y-axis
    plot->yAxis->grid()->setSubGridVisible(true);

}

void GraphHelper::setXAxis(QCustomPlot* plot, QVector<QString> labels, QVector<double> ticks)
{

    //Format x-axis
    plot->xAxis->setLabel("Year");
    //Remove auto ticks and labels
    plot->xAxis->setAutoTicks(false);
    plot->xAxis->setAutoTickLabels(false);

    //Add our ticks and labels
    plot->xAxis->setTickVector(ticks);
    plot->xAxis->setTickVectorLabels(labels);
    plot->xAxis->setTickLabelRotation(60);
    plot->xAxis->setSubTickCount(0);
    plot->xAxis->setTickLength(0, 4);
    plot->xAxis->grid()->setVisible(true);
    plot->xAxis->setRange(-0.5, numYears-0.4);
}

QVector<QString> GraphHelper::getData(double *amount, std::vector<std::vector<std::string> > &results)
{
    QVector<QString> xLabels;
    switch(dataType){
    case GRANT:
        if(graphChoice == 0)
            sumResultsAmount(amount,results);
        else if(graphChoice == 1)
            sumResultsAmount2(amount,results);
        else if(graphChoice == 2)
            xLabels = sumResultsType(amount,results);
        break;
    case PUBLICATION:
        if(graphChoice == 1)
            xLabels = sumResultsType(amount,results);
        else
            sumResultsAmount2(amount,results);
        break;
    case TEACHING:
        //
        break;
    case PRESENTATION:
        if(graphChoice == 1)
            xLabels = sumResultsType(amount,results);
        else
            sumResultsAmount2(amount,results);
        break;
    }
    return xLabels;
}

 void GraphHelper::sumResultsAmount(double* barAmount, std::vector<std::vector<std::string>> &results)
 {
     std::vector< std::vector<std::string> >::iterator resultIter;
     std::vector<std::string>::iterator fieldIter;
     resultIter = results.begin();

     while(resultIter != results.end())
     {
       fieldIter = resultIter->begin();
       std::string date = *(fieldIter +0);
       std::string amount = *(fieldIter +1);
       std::string dollarSignStrippedAmount = amount;
       double dbAmount = 0;

         //removes the dollar sign and comma to convert string to double
       if(amount.compare("") != 0)
       {
          dollarSignStrippedAmount = amount.substr(1, amount.length()-1);
          dollarSignStrippedAmount.erase(std::remove(dollarSignStrippedAmount.begin(), dollarSignStrippedAmount.end(), ','), dollarSignStrippedAmount.end());
          dbAmount = std::atof(dollarSignStrippedAmount.c_str());
       }

       //loop through the filtered date range to find the correct year to add amount to
       for (int i = earliest,k = 0;i<=latest;i++,k++)
       {
        if(date.find(std::to_string(i)) != std::string::npos)
        {
             //Add amount to date
               barAmount[k] += dbAmount;
        }
       }
       resultIter++;
     }
 }

 void GraphHelper::sumResultsAmount2(double* barAmount, std::vector<std::vector<std::string>> &results)
 {
     std::vector< std::vector<std::string> >::iterator resultIter;
     std::vector<std::string>::iterator fieldIter;
     resultIter = results.begin();
     while(resultIter != results.end())
     {
       fieldIter = resultIter->begin();
       std::string date = *(fieldIter +0);
       //std::string amount = *(fieldIter +1);

       //loop through the filtered date range to find the correct year to add amount to
       for (int i = earliest,k = 0;i<=latest;i++,k++)
       {
        if(date.find(std::to_string(i)) != std::string::npos)
        {
             //Add amount to date
               barAmount[k] += 1;
        }
       }
       resultIter++;
     }
 }

 QVector<QString> GraphHelper::sumResultsType(double* barAmount, std::vector<std::vector<std::string>> &results)
 {
     std::vector< std::vector<std::string> >::iterator resultIter;
     std::vector<std::string>::iterator fieldIter;
     resultIter = results.begin();
     QVector<QString> found;
     while(resultIter != results.end())
     {
       fieldIter = resultIter->begin();
       std::string date = *(fieldIter +0);
       std::string amount = *(fieldIter + graphChoice);

       if(date.find(std::to_string(dateChoice)) != std::string::npos)
       {
           if(amount.compare("") == 0)
               amount = "Type Missing";

           if(found.contains(QString::fromStdString(amount)) == false)
               found.push_back(QString::fromStdString(amount));

            //Add amount to date
              barAmount[found.indexOf(QString::fromStdString(amount))] += 1;
       }

       resultIter++;
     }
     return found;
 }

 void GraphHelper::setTitle(QCPPlotTitle* title)
 {
     //TODO:needs to switch on type of data when implemented
     title->setText("Funded Research vs Date Range");
 }

 void GraphHelper::setYAxisTitle(QCustomPlot *plot)
 {
     QString yLabel;
     switch (dataType){
     case PUBLICATION:
         if(graphChoice == 0)
            yLabel = "Number of each publication";
         else if(graphChoice == 1)
            yLabel = "Number of each publication type";
         break;
     case GRANT:
         if(graphChoice == 0)
            yLabel = "Amount of funding ($)";
         else if(graphChoice == 1)
             yLabel = "Number of grants";
         else if(graphChoice == 2)
             yLabel = "Number of each role";
         break;
     case PRESENTATION:
         if(graphChoice == 0)
            yLabel = "Number of each presentaion";
         else if(graphChoice == 1)
            yLabel = "Number of each presentation type";
         break;
     case TEACHING:
         if(graphChoice == 0)
            yLabel = "Number of each publication";
         else if(graphChoice == 1)
            yLabel = "Number of each publication type";
         break;
     }

     plot->yAxis->setLabel(yLabel);

 }

 void GraphHelper::graphAmtByType(QCustomPlot* plot, std::vector<std::vector<std::string>> &results)
 {
     switch(typeGraph)
     {
     case 0:
     {
         //Initialize myBars
         QCPBars *myBars = new QCPBars(plot->xAxis, plot->yAxis);

         plot->addPlottable(myBars);

         //create the array that will hold the summed amounts for each year
         double amount[25]= {0};
         QVector<QString> xLabels = getData(amount,results);

         QVector<double> years, yValues;
         int maxYVal = 0;
         QString yLabel = "Number of each publication type";
         for (int k = 0,t=0;k<25;k++)
         {
             //TODO: Maybe add option for user to choose bShowEmptyData(button on ui)
             //only adds the year to the graph if it has an amount
             if(bShowEmptyData || amount[k] != 0)
             {
                 //creates the bars and its associated data
                 yValues << amount[k];
                 //used to set the y axis range
                 if(maxYVal < amount[k])
                     maxYVal = amount[k];
                 years << t++;
                 numYears = t;
             }
         }

         //Modify properties of myBars:
         myBars->setData(years, yValues);

         //settings for the x and y axis
         plot->rescaleAxes();
         setYAxis(plot);
         setYAxisTitle(plot);
         setXAxis(plot, xLabels,years);
         plot->yAxis->setRange(0, maxYVal+0.5);
         plot->xAxis->setRange(-0.5, numYears-0.5);
         plot->xAxis->setLabel(QString::number(dateChoice));
         //plot->xAxis->scaleRange(1.025, plot->xAxis->range().center());
         //plot->yAxis->scaleRange(1.1, plot->yAxis->range().center());

         plot->replot();

         break;
     }
     case 1:
     {
         plot->addGraph();
         plot->graph()->setLineStyle(QCPGraph::lsLine);
         QPen pen;
         pen.setColor(QColor(Qt::blue));

         pen.setWidth(2.5);
         plot->graph()->setPen(pen);

         //create the array that will hold the summed amounts for each year
         double amount[25]= {0};
         QVector<QString> xLabels = getData(amount,results);

         QVector<double> years, yValues;
         int maxYVal = 0;
         for (int k = 0,t=0;k<25;k++)
         {
             //TODO: Maybe add option for user to choose bShowEmptyData(button on ui)
             //only adds the year to the graph if it has an amount
             if(bShowEmptyData || amount[k] != 0)
             {
                 //creates the bars and its associated data
                 yValues << amount[k];
                 //used to set the y axis range
                 if(maxYVal < amount[k])
                     maxYVal = amount[k];
                 years << t++;
                 numYears = t;
             }
         }
         //add data to graph
         plot->graph()->setData(years, yValues);
         plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
         plot->rescaleAxes();

         //format x and y axis
         setXAxis(plot,xLabels,years);
         setYAxis(plot);
         setYAxisTitle(plot);
         plot->yAxis->setRange(0, maxYVal+0.5);
         plot->xAxis->setRange(-0.5, numYears-0.5);
         plot->xAxis->setLabel(QString::number(dateChoice));

         plot->replot();
         break;
     }
   }
 }

 void GraphHelper::graphSumAmtVsDate(QCustomPlot* plot, std::vector<std::vector<std::string> > &results)
 {
     switch(typeGraph)
     {
     case 0: //Bar graph
     {
         //Initialize myBars
         QCPBars *myBars = new QCPBars(plot->xAxis, plot->yAxis);

         plot->addPlottable(myBars);

         //create the array that will hold the summed amounts for each year
         double* barAmount = new double[numYears];
         for(int i=0; i<numYears;i++){
             barAmount[i] = 0;
         }
         getData(barAmount,results);

         QVector<QString> xLabels;
         QVector<double> years, yValues;

         for (int i = earliest,k = 0,t=0;i<=latest;i++,k++)
         {
             //TODO: add option for user to choose bShowEmptyData(button on ui maybe)
             //only adds the year to the graph if it has an amount
             if(bShowEmptyData || barAmount[k] != 0)
             {
                 //creates the bars and its associated data
                 yValues << barAmount[k];
                 xLabels << QString::number(i);
                 years << t++;
                 numYears = t;
             }
         }
         //Modify properties of myBars:
         myBars->setData(years, yValues);

         //settings for the x and y axis
         plot->rescaleAxes();
         setYAxis(plot);
         setYAxisTitle(plot);
         setXAxis(plot, xLabels,years);

         plot->replot();

         free(barAmount);
         break;
     }
     case 1:
     {
         plot->addGraph();
         plot->graph()->setLineStyle(QCPGraph::lsLine);
         QPen pen;
         pen.setColor(QColor(Qt::blue));
         pen.setWidth(2.5);
         plot->graph()->setPen(pen);

         //create the array that will hold the summed amounts for each year
         double* amount = new double[numYears];
         for(int i=0; i<numYears;i++){
             amount[i] = 0;
         }
         getData(amount,results);

         QVector<QString> xLabels;
         QVector<double> years, yValues;
         for (int i = earliest,k = 0,t=0;i<=latest;i++,k++)
         {
             //TODO: Maybe add option for user to choose bShowEmptyData(button on ui)
             //only adds the year to the graph if it has an amount
             if(bShowEmptyData || amount[k] != 0)
             {
                 //creates the bars and its associated data
                 yValues << amount[k];
                 xLabels << QString::number(i);
                 years << t++;
                 numYears = t;
             }
         }
         //add data to graph
         plot->graph()->setData(years, yValues);
         plot->rescaleAxes();

         //format x and y axis
         setXAxis(plot,xLabels,years);
         setYAxis(plot);
         setYAxisTitle(plot);
         plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));


         plot->replot();
         free(amount);
         break;
     }
     default:
         break;

     }
 }
