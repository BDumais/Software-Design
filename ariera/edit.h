#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QSettings>
#include <QDesktopWidget>
#include <QtCore>
#include <QtGui>

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = 0);
    ~edit();
    void loadSettings();
    void saveSettings();

private:
    Ui::edit *ui;
};

#endif // EDIT_H
