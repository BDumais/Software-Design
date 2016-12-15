#include "treewidgetforpublication.h"

TreeWidgetForPublication::TreeWidgetForPublication():
    createtreewidget(new QTreeWidget())
{

}

TreeWidgetForPublication::~TreeWidgetForPublication()
{

}

QTreeWidget *TreeWidgetForPublication::getCreateTreeWidget()
{
    return createtreewidget;
}

QTreeWidgetItem* TreeWidgetForPublication::AddRoot(QString name, QString total)
{
    createtreewidget->setHeaderHidden(false); //set header QTreeWidget hidden
    createtreewidget->setColumnCount(2); //specify three columns for the tree widget
    createtreewidget->setColumnWidth(0, 200); //the first column width set
    createtreewidget->setColumnWidth(1, 50);
    QStringList list;
    list << "" << "Total";
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

QTreeWidgetItem* TreeWidgetForPublication::AddChild(QTreeWidgetItem *par, QString name, QString total)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    itm->setText(1, total);
    par->addChild(itm);
    return itm;
}

void TreeWidgetForPublication::fillTreeWidgetForPublication(Database &db, int earliest, int latest)
{
    struct publicationSummary sum;
    db.publicationSummary(sum, earliest, latest);

    QTreeWidgetItem *midRoot1 = AddRoot("Books", QString::number(sum.books.size()));
    PrintChildNodes(midRoot1, sum.books);

    QTreeWidgetItem *midRoot2 = AddRoot("Book Chapters", QString::number(sum.bookChapters.size()));
    PrintChildNodes(midRoot2, sum.bookChapters);

    QTreeWidgetItem *midRoot3 = AddRoot("Books Edited", QString::number(sum.booksEdited.size()));
    PrintChildNodes(midRoot3, sum.booksEdited);

    QTreeWidgetItem *midRoot4 = AddRoot("Case Reports", QString::number(sum.caseReports.size()));
    PrintChildNodes(midRoot4, sum.caseReports);

    QTreeWidgetItem *midRoot5 = AddRoot("Published Abstract", QString::number(sum.publishedAbstract.size()));
    PrintChildNodes(midRoot5, sum.publishedAbstract);

    QTreeWidgetItem *midRoot6 = AddRoot("Journal Article", QString::number(sum.journalArticle.size()));
    PrintChildNodes(midRoot6, sum.journalArticle);

    QTreeWidgetItem *midRoot7 = AddRoot("Letters to Editor", QString::number(sum.lettersToEditor.size()));
    PrintChildNodes(midRoot7, sum.lettersToEditor);

    QTreeWidgetItem *midRoot8 = AddRoot("Clinical Care Guidelines", QString::number(sum.lettersToEditor.size()));
    PrintChildNodes(midRoot8 , sum.lettersToEditor);

    QTreeWidgetItem *midRoot9 = AddRoot("Commentaries", QString::number(sum.commentaries.size()));
    PrintChildNodes(midRoot9, sum.commentaries);

    QTreeWidgetItem *midRoot10 = AddRoot("Conference Proceedings", QString::number(sum.conferenceProceedings.size()));
    PrintChildNodes(midRoot10, sum.conferenceProceedings);

    QTreeWidgetItem *midRoot11 = AddRoot("Editorials", QString::number(sum.editorials.size()));
    PrintChildNodes(midRoot11, sum.editorials);

    QTreeWidgetItem *midRoot12 = AddRoot("Invited Articles", QString::number(sum.invitedArticles.size()));
    PrintChildNodes(midRoot12, sum.invitedArticles);

    QTreeWidgetItem *midRoot13 = AddRoot("Magazine Entries", QString::number(sum.magazineEntries.size()));
    PrintChildNodes(midRoot13, sum.magazineEntries);

    QTreeWidgetItem *midRoot14 = AddRoot("Manuals", QString::number(sum.manuals.size()));
    PrintChildNodes(midRoot14, sum.manuals);

    QTreeWidgetItem *midRoot15 = AddRoot("Monographs", QString::number(sum.monographs.size()));
    PrintChildNodes(midRoot15, sum.monographs);

    QTreeWidgetItem *midRoot16 = AddRoot("Multimedia", QString::number(sum.multimedia.size()));
    PrintChildNodes(midRoot16, sum.multimedia);

    QTreeWidgetItem *midRoot17 = AddRoot("Newspaper Articles", QString::number(sum.newspaperArticles.size()));
    PrintChildNodes(midRoot17, sum.newspaperArticles);

    QTreeWidgetItem *midRoot18 = AddRoot("Supervised Student Publications", QString::number(sum.supervisedStudentPublications.size()));
    PrintChildNodes(midRoot18, sum.supervisedStudentPublications);

    QTreeWidgetItem *midRoot19 = AddRoot("Websites / Videos", QString::number(sum.websiteOrVideos.size()));
    PrintChildNodes(midRoot19, sum.websiteOrVideos);

    QTreeWidgetItem *midRoot20 = AddRoot("Working Papers", QString::number(sum.workingPapers.size()));
    PrintChildNodes(midRoot20, sum.workingPapers);
}

void TreeWidgetForPublication::PrintChildNodes(QTreeWidgetItem *parent, vector<vector<string>> &results)
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
