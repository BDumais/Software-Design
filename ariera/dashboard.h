#ifndef DASHBOARD1_H
#define DASHBOARD1_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include "summary.h"

class Summary;

namespace Ui {
class DashBoard;
}

class DashBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashBoard(QWidget *parent = 0);
    void processFile(QString filename);
    bool searchAndRemove(QString filename);
    ~DashBoard();
    void loadSettings();
    void saveSettings();

private slots:
    /**
     * @brief on_pushButton_clicked open a file to be processed.
     */
    void on_pushButton_clicked();
    /**
     * @brief on_pushButton_3_clicked close the application.
     */
    void on_pushButton_3_clicked();
    /**
     * @brief on_pushButton_2_clicked display the summary form.
     */
    void on_pushButton_2_clicked();
    /**
     * @brief on_listWidget_itemSelectionChanged if any change occurs on the list view it activate the process button
     */
    void on_listWidget_itemSelectionChanged();

    /**
     * @brief on_listWidget_2_itemSelectionChanged any activty on the second list window will activate the summary button
     */
    void on_listWidget_2_itemSelectionChanged();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::DashBoard *ui;
    QString filename; //store the current opened file
    std::vector<std::string> listitmvec; //array of opened files with there absolute path
    QImage img; //class to process icon
    Summary *m; //summary variable to transition to the summary form.
};

#endif // DashBoard_H
