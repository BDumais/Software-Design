#include "edit.h"
#include "ui_edit.h"

edit::edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
    loadSettings();
}

edit::~edit()
{
    delete ui;
}

void edit::loadSettings()
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

void edit::saveSettings()
{
    QSettings appSetting("TeamBananaSetting", "TeamBanana");
    appSetting.beginGroup("SummaryWindows");
    appSetting.setValue("position", this->geometry());
    appSetting.endGroup();
}
