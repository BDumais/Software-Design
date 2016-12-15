/**
  CS3307 Team Banana
  
  dashboard.cpp implements the GUI
**/  

#include "dashboard.h"
#include "ui_dashboard.h"
#include "edit.h"
#include <QMessageBox>
#include <exception>

DashBoard::DashBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashBoard)
{
    ui->setupUi(this);
    loadSettings();
    img.load(":/new/img/image/banana.png");
    ui->label_2->setPixmap(QPixmap::fromImage(img)); //display the image on the form.
    ui->pushButton_2->setEnabled(false); //disable the button
    ui->pushButton_7->setEnabled(false); //edit
    ui->pushButton_6->setEnabled(false); //delete
    ui->pushButton_8->setEnabled(false); //disable deleteall
    ui->listWidget_2->clear();    

    //if a process file exists in the current directory load , other with select raw file
    //process it or reprocess the file and refresh the list widget.
    QDir dir(".");
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list)
    {
        QRegExp re("^Processed.*v$");
        if(info.fileName().contains(re))
        {
                ui->listWidget_2->addItem(info.fileName());
                listitmvec.push_back(info.absoluteFilePath().toStdString());
        }
    }

    if(ui->listWidget_2->count() > 0)
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
    }
}

DashBoard::~DashBoard()
{
    delete ui;
}

//open button
void DashBoard::on_pushButton_clicked()
{
    bool doesExists = false;
    filename = QFileDialog::getOpenFileName(this, "Open File ...", "", "csv(*.csv)" );
    if(!filename.contains("Processed"))
    {
        for(int i=0; i<ui->listWidget_2->count(); i++)
        {
            //splits the absolute path with forward slash and only displays the relative path
            //if the file is on the list widget it skips
            QListWidgetItem *itm = ui->listWidget_2->item(i);
            QStringList lst = filename.split("/");
            QString cmp = "Processed"+lst[lst.length()-1];
            //QString cmpSubStr = cmp.section("_", -2, -2)+".csv";


            if(((itm->text().contains("Grants") && filename.contains("Grants")) ||
               (itm->text().contains("Publication") && filename.contains("Publication")) ||
               (itm->text().contains("Teaching") && filename.contains("Teaching")) ||
               (itm->text().contains("Presentation") && filename.contains("Presentation"))))
            {
                doesExists = true;
                QMessageBox msgBox;
                msgBox.setText("The document " + cmp + " already exists.");
                msgBox.setInformativeText("Do you want to replace it?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                int ret = msgBox.exec();
                switch (ret) {
                case QMessageBox::Yes:
                    if(filename.contains("Grants"))
                    {
                        searchAndRemove("ProcessedGrantsClinicalFunding.csv");
                    }
                    else if(filename.contains("Publication"))
                    {
                        searchAndRemove("ProcessedPublication.csv");
                    }
                    else if(filename.contains("Teaching"))
                    {
                        searchAndRemove("ProcessedTeaching.csv");
                    }
                    else if(filename.contains("Presentation"))
                    {
                        searchAndRemove("ProcessedPresentation.csv");
                    }
                    ui->listWidget_2->clear();
                    doesExists = false;
                    break;
                case QMessageBox::No:
                    doesExists = true;
                    break;
                default:
                    break;
                }
                break;
            }

        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid file format, please choose another file.");
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.exec();
    }
    if(!doesExists)
    {
        //listitmvec.push_back(filename.toStdString());
        processFile(filename);
    }
    if(ui->listWidget_2->count() > 0 )
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
    }
}

void DashBoard::processFile(QString filename)
{
    listitmvec.clear();
    QStringList lst = filename.split("/");
    QString cmp = lst[lst.length()-1];
    QString theProcessedFileName;

    if(cmp.contains("Grants"))
    {
        Preprocessor preprocessor0(filename.toStdString());
        theProcessedFileName = "ProcessedGrantsClinicalFunding.csv";
    }
    else if(cmp.contains("Publication"))
    {
       Preprocessor preprocessor1(filename.toStdString());
       theProcessedFileName = "ProcessedPublication.csv";
    }
    else if(cmp.contains("Presentation"))
    {
        Preprocessor preprocessor2(filename.toStdString());
        theProcessedFileName = "ProcessedPresentation.csv";
    }
    else if(cmp.contains("Teaching"))
    {
        Preprocessor preprocessor3(filename.toStdString());
        theProcessedFileName = "ProcessedTeaching.csv";
    }
    else
    {
       qDebug() << "[?] " + filename + " is unknown file format.";
    }

    ui->listWidget_2->clear();
    QDir dir(".");
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);    
    foreach (QFileInfo info, list)
    {
       QRegExp re("^Processed.*v$");
       if((info.fileName().contains(re) && !info.fileName().contains(theProcessedFileName)) || (info.fileName().contains(re) && theProcessedFileName.isEmpty()))
       {
             ui->listWidget_2->addItem(info.fileName());
             listitmvec.push_back(info.absoluteFilePath().toStdString());
       }
       if(info.fileName().contains(theProcessedFileName))
       {
           listitmvec.push_back(info.absoluteFilePath().toStdString());
       }
    }
    if(!theProcessedFileName.isEmpty())
        ui->listWidget_2->addItem(theProcessedFileName);
}


bool DashBoard::searchAndRemove(QString filename)
{
    bool val;
    QDir dir(".");
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list)
    {
        QRegExp re(filename);
        if(info.fileName().contains(re))
        {
                val = dir.remove(filename);
        }
    }
    return val;
}


//quit button
void DashBoard::on_pushButton_3_clicked()
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
//summary button
void DashBoard::on_pushButton_2_clicked()
{
    QDir dir(".");
    listitmvec.clear();
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list)
    {
        QRegExp re("^Processed.*v$");
        if(info.fileName().contains(re))
        {
                listitmvec.push_back(info.absoluteFilePath().toStdString());
        }
    }

    QString tempString;
    m = new Summary(tempString, listitmvec, this);
    m->show();
    this->hide();
}

void DashBoard::on_listWidget_itemSelectionChanged()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
}

void DashBoard::on_listWidget_2_itemSelectionChanged()
{

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
}
//delete button
void DashBoard::on_pushButton_6_clicked()
{
    QDir dir(".");
    QListWidgetItem *currentselecteditem = ui->listWidget_2->currentItem();
    dir.remove(currentselecteditem->text());
    qDeleteAll(ui->listWidget_2->selectedItems());
    if(ui->listWidget_2->count() <= 0)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
    }
    ui->pushButton_6->setEnabled(false);

    ui->listWidget_2->clear();
    listitmvec.clear();
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list)
    {
        QRegExp re("^Processed.*v$");
        if(info.fileName().contains(re))
        {
                ui->listWidget_2->addItem(info.fileName());
                listitmvec.push_back(info.absoluteFilePath().toStdString());
        }
    }
}
//edit button
void DashBoard::on_pushButton_7_clicked()
{
    edit editWindow;
    editWindow.setModal(true);
    editWindow.exec();
}

void DashBoard::on_pushButton_8_clicked()
{
    QDir dir(".");
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list)
    {
        QRegExp re("^Processed.*v$");
        if(info.fileName().contains(re))
        {
                dir.remove(info.fileName());
        }
    }
    ui->listWidget_2->clear();
    if(ui->listWidget_2->count() <= 0)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
    }
    listitmvec.clear();
}

void DashBoard::loadSettings()
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

void DashBoard::saveSettings()
{
    QSettings appSetting("TeamBananaSetting", "TeamBanana");
    appSetting.beginGroup("SummaryWindows");
    appSetting.setValue("position", this->geometry());
    appSetting.endGroup();
}
