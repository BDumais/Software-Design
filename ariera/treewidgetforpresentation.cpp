#include "treewidgetforpresentation.h"

TreeWidgetForPresentation::TreeWidgetForPresentation():
    createtreewidget(new QTreeWidget())
{

}

TreeWidgetForPresentation::~TreeWidgetForPresentation()
{

}

QTreeWidget *TreeWidgetForPresentation::getCreateTreeWidget()
{
    return createtreewidget;
}

QTreeWidgetItem* TreeWidgetForPresentation::AddRoot(QString name, QString total)
{
    createtreewidget->setHeaderHidden(false); //set header QTreeWidget hidden
    createtreewidget->setColumnCount(2); //specify three columns for the tree widget
    createtreewidget->setColumnWidth(0, 200); //the first column width set
    createtreewidget->setColumnWidth(1, 50);
    QStringList list;
    list << "Faculty Name" << "# of Presentations";
    QTreeWidgetItem *headeritms = new QTreeWidgetItem(list);
    headeritms->setTextAlignment(0, Qt::AlignRight);
    headeritms->setTextAlignment(1, Qt::AlignCenter);

    createtreewidget->setHeaderItem(headeritms);
    createtreewidget->setHeaderLabels(list);


    QTreeWidgetItem *itm = new QTreeWidgetItem(createtreewidget);
    itm->setText(0, name); //first column
    itm->setText(1, total);
    createtreewidget->addTopLevelItem(itm);
    return itm;
}

QTreeWidgetItem* TreeWidgetForPresentation::AddChild(QTreeWidgetItem *par, QString name, QString total)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    itm->setText(1, total);
    par->addChild(itm);
    return itm;
}

void TreeWidgetForPresentation::fillTreeWidgetForPresentation(Database &db, int earliest, int latest)
{
    struct presentationSummary sum;
    db.presentationSummary(sum, earliest, latest);

    QTreeWidgetItem *midRoot1 = AddRoot("Invited Lectures", QString::number(sum.invitedLectures.size()));
    PrintChildNodes(midRoot1, sum.invitedLectures);

    QTreeWidgetItem *midRoot2 = AddRoot("Abstracts Presented", QString::number(sum.abstractPresented.size()));
    PrintChildNodes(midRoot2, sum.abstractPresented);

    QTreeWidgetItem *midRoot3 = AddRoot("Visiting Professorship", QString::number(sum.visitingProfessorship.size()));
    PrintChildNodes(midRoot3, sum.visitingProfessorship);

    QTreeWidgetItem *midRoot4 = AddRoot("Plenary Presentations", QString::number(sum.plenaryPresentation.size()));
    PrintChildNodes(midRoot4, sum.plenaryPresentation);

    QTreeWidgetItem *midRoot5 = AddRoot("Poster Presentations", QString::number(sum.posterPresentation.size()));
    PrintChildNodes(midRoot5, sum.posterPresentation);

    QTreeWidgetItem *midRoot6 = AddRoot("Student Presentations", QString::number(sum.studentPresentation.size()));
    PrintChildNodes(midRoot6, sum.studentPresentation);
}

void TreeWidgetForPresentation::PrintChildNodes(QTreeWidgetItem *parent, vector<vector<string>> &results)
{
  vector< vector<string> >::iterator iter = results.begin();

  if (iter == results.end())
    return;

  string currentName = (*iter)[0];
  int count = 1;
  iter++;
  while (1){
    
    if (iter != results.end() && (*iter)[0].compare(currentName) == 0){
      count++;
      iter++;
      continue;
    }
    else {
      std::ostringstream convert;
      convert << count;
      QString nameStr = QString::fromStdString(currentName);
      QString countStr = QString::fromStdString(convert.str());
      AddChild(parent, nameStr, countStr);

      if (iter == results.end())
        break;

      currentName = (*iter)[0];
      count = 1;
      iter++;
    }
  } 
}
