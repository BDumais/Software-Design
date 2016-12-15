/**
  CS3307 Team Banana

  summary.cpp shows the summary of the excel data to the user
**/

#include "summary.h"
#include "ui_summary.h"

Summary::Summary(QString qs, vector<string> listititem, DashBoard *dashb, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Summary),
    stringTransfered(qs),
    dashBoardData(dashb),
    listVectorTransfered(listititem),
    PresentationSummary(NULL),
    GrantSummary(NULL),
    PublicationSummary(NULL)
{
    ui->setupUi(this);
    loadSettings();
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    graph = ui->graphWidget;
    graphTitleInit();

    foreach (string s, listVectorTransfered)
    {
        if(QString::fromStdString(s).contains("Grant"))
        {
            GrantSummary = new TreeWidgetForGrant();
            GrantSummary->AddRoot("", "", "Total $");
            GrantSummary->fillTreeWidgetForGrant(db, 1000, 3000); //shows all year, use filter to display desired time frame
            ui->tabWidget->addTab(GrantSummary->getCreateTreeWidget(), "Grants and Clinical");
        }
        else if(QString::fromStdString(s).contains("Presentation"))
        {
            PresentationSummary = new TreeWidgetForPresentation();
            PresentationSummary->AddRoot("", "");
            PresentationSummary->fillTreeWidgetForPresentation(db, 1000, 3000);;
            ui->tabWidget->addTab(PresentationSummary->getCreateTreeWidget(), "Presentations");
        }
        else if(QString::fromStdString(s).contains("Publication"))
        {
            PublicationSummary = new TreeWidgetForPublication();
            PublicationSummary->AddRoot("", "");
            PublicationSummary->fillTreeWidgetForPublication(db, 1000, 3000);;
            ui->tabWidget->addTab(PublicationSummary->getCreateTreeWidget(), "Publications");
        }
        else if(QString::fromStdString(s).contains("Teaching"))
        {
            QLabel *present = new QLabel();
            present->setText("UNDER CONSTRUCTION");
            ui->tabWidget->addTab(present, "Teaching");
        }
    }

}

Summary::~Summary()
{
    delete GrantSummary;
    delete PublicationSummary;
    delete PresentationSummary;
    delete ui;
}



/**
 * Generates a graph once the "Graph" button on the Summary page is clicked
 * NOTE: Currently generates its own data - not tied to Summary; should be refactored
 *
 * @brief Summary::on_pushButton_2_clicked create the graph form.
 */
void Summary::graphs()
{
    ui->tabWidget->currentIndex();
    vector< vector<string> > results;
    vector<grantsAndFundingField> fields;
    FieldMatchFilter nameMatch(MEMBER_NAME,"");

    //Define filter of start dates within 2000 and 2001
    vector<Filter*> filters;
    ui->lineEdit->setValidator(new QIntValidator(1000, 3000, this));
    ui->lineEdit_2->setValidator(new QIntValidator(1000, 3000, this));
    int earliest = ui->lineEdit->text().toInt();
    int latest = ui->lineEdit_2->text().toInt();

    if(earliest > latest) //throw error and do not create graph
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Invalid Range");
        messageBox.setFixedSize(600,200);
    }
    else
    {
        //if range left blank set earliest to 1970, and latest to current year
        if(latest == 0)
        {
            time_t t = std::time(0);
            struct tm * now = localtime(&t);
            earliest = 1970;
            latest = now->tm_year + 1900;
            ui->lineEdit->setText(QString::number(earliest));
            ui->lineEdit_2->setText(QString::number(latest));
        }
        //title of the selected tab
        QString tabSelected = ui->tabWidget->tabText(ui->tabWidget->currentIndex());

        //Apply date filters
        DateFilter df(earliest,latest);
        filters.push_back(&df);

        int dateChoice = ui->dateSelector->currentText().toInt();
        int dataType = 0;
        if(tabSelected.contains("Grant",Qt::CaseInsensitive) == true){
            filters = chosenName(filters,&nameMatch);
            fields.push_back(START_DATE);
            fields.push_back(TOTAL_AMOUNT);
            fields.push_back(ROLE);
            db.getGrantsAndFunding(results,filters,fields);
            dataType = GRANT;
        }
        else if(tabSelected.contains("Pub",Qt::CaseInsensitive) == true){
            filters = chosenName(filters,&nameMatch);
            fields.push_back(STATUS_DATE);
            fields.push_back(TYPE);
            db.getPublications(results,filters,fields);
            dataType = PUBLICATION;
        }
        else if(tabSelected.contains("Teach",Qt::CaseInsensitive) == true){
            /*filters = chosenName(filters,&nameMatch);
            fields.push_back(STATUS_DATE);
            fields.push_back(TYPE);
            db.getTeaching(results,filters,fields);*/
            dataType = TEACHING;
        }
        else if(tabSelected.contains("Pres",Qt::CaseInsensitive) == true){
            filters = chosenName(filters,&nameMatch);
            fields.push_back(DATES);
            fields.push_back(TYPE);
            db.getPresentations(results,filters,fields);
            dataType = PRESENTATION;
        }
        else{
            exit(EXIT_FAILURE);
        }

        graph->clearPlottables();

        GraphHelper graphHelp(ui->graphSelector->currentIndex(),
                              ui->graphChoice->currentIndex(),
                              dataType,dateChoice,earliest,latest);
        graphHelp.makeGraph(graph,results);
        graphHelp.setTitle(graphTitle);
        graph->replot();
    }
}
//filter button
void Summary::on_pushButton_clicked()
{
    int tabindex = ui->tabWidget->currentIndex();
    QString currentTabText = ui->tabWidget->tabText(tabindex);

    ui->lineEdit->setValidator(new QIntValidator(1000, 3000, this));
    ui->lineEdit_2->setValidator(new QIntValidator(1000, 3000, this));
    int earliest = ui->lineEdit->text().toInt();
    int latest = ui->lineEdit_2->text().toInt();
    if(earliest > latest)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Invalid input !");
        messageBox.setFixedSize(600,200);
    }
    else
    {
        qDebug() << ui->tabWidget->tabText(tabindex);
        if(/*(GrantSummary !=NULL) &&*/ (ui->tabWidget->tabText(tabindex).contains("Grant")) && currentTabText.contains("Grant"))
        {
            GrantSummary->getCreateTreeWidget()->clear();
            GrantSummary->AddRoot("", "", "");
            GrantSummary->fillTreeWidgetForGrant(db, earliest, latest);
           // ui->tabWidget->addTab(GrantSummary->getCreateTreeWidget(), "Grants and Clinical");
        }
        if(/*(PublicationSummary != NULL) &&*/ (ui->tabWidget->tabText(tabindex).contains("Publication")) && currentTabText.contains("Publication"))
        {
            PublicationSummary->getCreateTreeWidget()->clear();
            PublicationSummary->AddRoot("", "");
            PublicationSummary->fillTreeWidgetForPublication(db, earliest, latest);
            //ui->tabWidget->addTab(PublicationSummary->getCreateTreeWidget(), "Publications");
        }
        if(/*(PresentationSummary != NULL) && */(ui->tabWidget->tabText(tabindex).contains("Presentation")) && currentTabText.contains("Presentation"))
        {
            PresentationSummary->getCreateTreeWidget()->clear();
            PresentationSummary->AddRoot("", "");
            PresentationSummary->fillTreeWidgetForPresentation(db, earliest, latest);
            //ui->tabWidget->addTab(PresentationSummary->getCreateTreeWidget(), "Presentations");
        }
        if(/*(PresentationSummary != NULL) && */(ui->tabWidget->tabText(tabindex).contains("Teaching")) && currentTabText.contains("Teaching"))
        {

        }
    }
    graphs();
    //ui->tabWidget->setCurrentIndex(tabindex);
}

void Summary::on_pushButton_3_clicked()
{
    saveSettings();
    this->close();
    dashBoardData->show();
}

void Summary::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setInformativeText("Are you sure you would like to quit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret)
    {
        case QMessageBox::Yes:
            this->close();
            break;
        case QMessageBox::No:
            break;
    }
}
//clear button
void Summary::on_pushButton_5_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit->setText("1975");
    ui->lineEdit_2->setText("2015");

    if(GrantSummary != NULL)
    {
        GrantSummary->getCreateTreeWidget()->clear();
        GrantSummary->AddRoot("", "", "");
        GrantSummary->fillTreeWidgetForGrant(db, 1000, 3000);
        ui->tabWidget->addTab(GrantSummary->getCreateTreeWidget(), "Grants and Clinical");
    }

    if(PublicationSummary != NULL)
    {
        PublicationSummary->getCreateTreeWidget()->clear();
        PublicationSummary->AddRoot("", "");
        PublicationSummary->fillTreeWidgetForPublication(db,1000, 3000);
        ui->tabWidget->addTab(PublicationSummary->getCreateTreeWidget(), "Publications");
    }

    if(PresentationSummary != NULL)
    {
        PresentationSummary->getCreateTreeWidget()->clear();
        PresentationSummary->AddRoot("", "");
        PresentationSummary->fillTreeWidgetForPresentation(db,1000, 3000);
        ui->tabWidget->addTab(PresentationSummary->getCreateTreeWidget(), "Presentations");
    }

}

// Print graph button
void Summary::on_pushButton_6_clicked()
{
    // Option 1: Export to PDF
    QString filename = QFileDialog::getSaveFileName(0,"Export Graph as PDF","",".pdf");
    filename.append(".pdf");
    graph->savePdf(filename);

    // Option 2: Print using print dialog - but scale is way off

//    QPrinter printer(QPrinter::HighResolution);
//    QPrintDialog *dialog = new QPrintDialog(&printer, this);
//    dialog->setWindowTitle(tr("Print Graph"));
//    if(dialog->exec() ==  QDialog::Accepted) {
//        // Print
//        QCPPainter painter;
//        painter.begin(&printer);

//        double xscale = printer.pageRect().width()/graph->width();
//        double yscale = printer.pageRect().height()/graph->height();
//        double scale = qMin(xscale, yscale);
//        painter.translate(printer.paperRect().x() + printer.pageRect().width()/2, printer.paperRect().y() + printer.pageRect().height()/2);
//        painter.scale(scale, scale);
//        painter.translate(-width()/2, -height()/2);

//        graph->toPainter(&painter);
//        painter.end();
//    }
}

void Summary::graphTitleInit()
{
   graph->plotLayout()->insertRow(0);
   graphTitle = new QCPPlotTitle(graph,"");
   graph->plotLayout()->addElement(0, 0, graphTitle);
}

void Summary::on_tabWidget_currentChanged(int index)
{
    ui->graphChoice->clear();
    ui->dateSelector->setEnabled(false);
    vector<grantsAndFundingField> nameFields;
    nameFields.push_back(MEMBER_NAME);
    vector<vector<string>> nameResults;
    vector<Filter*> filters;
    int earliest = ui->lineEdit->text().toInt();
    int latest = ui->lineEdit_2->text().toInt();
    if(latest == 0){
        time_t t = std::time(0);
        struct tm * now = localtime(&t);
        earliest = 1970;
        latest = now->tm_year + 1900;
        ui->lineEdit->setText(QString::number(earliest));
        ui->lineEdit_2->setText(QString::number(latest));
    }
    DateFilter df(earliest,latest);
    filters.push_back(&df);

    if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pub",Qt::CaseInsensitive) == true){
        ui->graphChoice->addItem("Number of Publications by Year");
        ui->graphChoice->addItem("Number of Publications by Type");
        nameFields.push_back(STATUS_DATE);
        db.getPublications(nameResults,filters,nameFields);
        processChoices(nameResults);

        graphs();
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Grant",Qt::CaseInsensitive) == true){
        ui->graphChoice->addItem("Amount of Grant Funding by Year");
        ui->graphChoice->addItem("Number of Grants per Year");
        ui->graphChoice->addItem("Roles taken in Grants for single year");
        nameFields.push_back(START_DATE);
        db.getGrantsAndFunding(nameResults,filters,nameFields);
        processChoices(nameResults);

        graphs();
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pres",Qt::CaseInsensitive) == true){
        ui->graphChoice->addItem("Number of Presentations by Year");
        ui->graphChoice->addItem("Number of Presentations by Type");
        nameFields.push_back(DATES);
        db.getPresentations(nameResults,filters,nameFields);
        processChoices(nameResults);

        graphs();
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Teach",Qt::CaseInsensitive) == true){
        //nameFields.push_back(STATUS_DATE);
       // db.getTeaching(nameResults,filters,nameFields);
       // processName(nameResults);
    }

}

void Summary::processChoices(std::vector<std::vector<std::string> > &results){
    std::vector< std::vector<std::string> >::iterator resultIter;
    std::vector<std::string>::iterator fieldIter;
    QVector<QString> names;
    QVector<QString> years;
    resultIter = results.begin();
    ui->nameBox->clear();
    ui->nameBox->addItem("All Names");
    ui->dateSelector->clear();
    while(resultIter != results.end())
    {
      fieldIter = resultIter->begin();
      QString name = QString::fromStdString(*(fieldIter));
      QString year = QString::fromStdString(*(fieldIter + 1));

      if(QString::compare(name,"") != 0 && names.contains(name) == false)
          names.push_back(name);

      if(QString::compare(year,"") != 0)
          years.push_back(year);

      resultIter++;
    }

    names = sortNames(names);
    for(int i=0;i<names.size();i++){
        ui->nameBox->addItem(names[i]);
    }

    years = cleanDates(years);
    for(int i=0;i<years.size();i++){
        ui->dateSelector->addItem(years[i]);
    }
}

void Summary::processDate(std::vector<std::vector<std::string> > &results){
    std::vector< std::vector<std::string> >::iterator resultIter;
    std::vector<std::string>::iterator fieldIter;
    QVector<QString> years;
    resultIter = results.begin();
    ui->dateSelector->clear();
    while(resultIter != results.end())
    {
      fieldIter = resultIter->begin();
      QString year = QString::fromStdString(*(fieldIter));

      if(QString::compare(year,"") != 0)
          years.push_back(year);

      resultIter++;
    }

    years = cleanDates(years);
    for(int i=0;i<years.size();i++){
        ui->dateSelector->addItem(years[i]);
    }
}

vector<Filter*> Summary::chosenName(vector<Filter*> filters,FieldMatchFilter* nameMatch){
    QString selected = ui->nameBox->currentText();

    if(QString::compare(selected,"All Names",Qt::CaseInsensitive) != 0){
      std::string name = selected.toStdString();
      nameMatch->setValue(name);
      filters.push_back(nameMatch);
    }
    return filters;
}


void Summary::loadSettings()
{
    QDesktopWidget *desktop =  QApplication::desktop();
    int screenwidth = (desktop->width()-this->width())/2;
    int screenheight = (desktop->height()-this->height())/2;

    QSettings appSetting("TeamBananaSetting", "TeamBanana");
    appSetting.beginGroup("SummaryWindows");
    QRect summarySize = appSetting.value("position", QRect(QPoint(screenwidth, screenheight), QSize(this->width(), this->height()))).toRect();
    setGeometry(summarySize);
    appSetting.endGroup();
}

void Summary::saveSettings()
{
    QSettings appSetting("TeamBananaSetting", "TeamBanana");
    appSetting.beginGroup("SummaryWindows");
    appSetting.setValue("position", this->geometry());
    appSetting.endGroup();
}

QVector<QString> Summary::cleanDates(QVector<QString> years){
    QString temp;
    QVector<QString> orderedYear;
    for(int i =0;i<years.size();i++){
        temp = years[i];
        if(temp.size() > 4){
            temp = temp.left(4);
        }
        if(orderedYear.contains(temp)== false)
            orderedYear.push_back(temp);
    }

    for(int i =0;i<orderedYear.size()-1;i++){
        if(orderedYear[i].toInt() < orderedYear[i+1].toInt()){
            qSwap(orderedYear[i],orderedYear[i+1]);
            i =-1;
        }
    }
    return orderedYear;
}

QVector<QString> Summary::sortNames(QVector<QString> names){
    QVector<QString> ordered = names;

    for(int i =0;i<ordered.size()-1;i++){
            if(ordered[i] > ordered[i+1]){
            qSwap(ordered[i],ordered[i+1]);
            i =-1;
        }
    }
    return ordered;
}

void Summary::on_nameBox_activated(int index)
{
        FieldMatchFilter nameMatch(MEMBER_NAME, "");
        vector<grantsAndFundingField> nameFields;;
        vector<vector<string>> nameResults;
        vector<Filter*> filters;

        int earliest = ui->lineEdit->text().toInt();
        int latest = ui->lineEdit_2->text().toInt();
        if(latest == 0){
            time_t t = std::time(0);
            struct tm * now = localtime(&t);
            earliest = 1970;
            latest = now->tm_year + 1900;
            ui->lineEdit->setText(QString::number(earliest));
            ui->lineEdit_2->setText(QString::number(latest));
        }
        DateFilter df(earliest,latest);
        filters.push_back(&df);
        filters = chosenName(filters, &nameMatch);

        if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pub",Qt::CaseInsensitive) == true){
            nameFields.push_back(STATUS_DATE);
            db.getPublications(nameResults,filters,nameFields);
        }
        else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Grant",Qt::CaseInsensitive) == true){
            nameFields.push_back(START_DATE);
            db.getGrantsAndFunding(nameResults,filters,nameFields);

        }
        else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pres",Qt::CaseInsensitive) == true){
            nameFields.push_back(DATES);
            db.getPresentations(nameResults,filters,nameFields);
        }
        else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Teach",Qt::CaseInsensitive) == true){
            //nameFields.push_back(STATUS_DATE);
           // db.getTeaching(nameResults,filters,nameFields);
        }

        processDate(nameResults);
        graphs();
    graphs();
}

void Summary::on_graphChoice_activated(int index)
{
    if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Grant",Qt::CaseInsensitive) == true){
        if(index == 2)
            ui->dateSelector->setEnabled(true);
        else
            ui->dateSelector->setEnabled(false);
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pub",Qt::CaseInsensitive) == true){
        if(index == 1)
            ui->dateSelector->setEnabled(true);
        else
            ui->dateSelector->setEnabled(false);
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Pres",Qt::CaseInsensitive) == true){
        if(index == 1)
            ui->dateSelector->setEnabled(true);
        else
            ui->dateSelector->setEnabled(false);
    }
    else if(ui->tabWidget->tabText(ui->tabWidget->currentIndex()).contains("Teach",Qt::CaseInsensitive) == true){

    }
    graphs();
}

void Summary::on_graphSelector_activated(int index)
{
    graphs();
}

void Summary::on_dateSelector_activated(int index)
{
    graphs();
}
