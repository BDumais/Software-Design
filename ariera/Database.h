#ifndef DATABASE_H
#define DATABASE_H


#include "ProcessedGrantsAndFundingRecord.h"
#include "ProcessedTeachingRecord.h"
#include "ProcessedPublicationRecord.h"
#include "ProcessedPresentationRecord.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "IOUtility.h"
#include "GrantsAndFundingFields.h"
#include "Filter.h"
#include "DateFilter.h"
#include "FieldMatchFilter.h"
#include "QtCore"

using std::vector;
using std::string;

struct grantsAndFundingSummary {

  vector< vector<string> > grantsPeerReviewed;
  vector< vector<string> > grantsIndustrySponsored;
  vector< vector<string> > clinicalPeerReviewed;
  vector< vector<string> > clinicalIndustrySponsored;

};
struct presentationSummary {

  vector< vector<string> > invitedLectures;
  vector< vector<string> > abstractPresented;
  vector< vector<string> > visitingProfessorship;
  vector< vector<string> > plenaryPresentation;
  vector< vector<string> > posterPresentation;
  vector< vector<string> > studentPresentation;
  vector< vector<string> > other;
};
/*
struct teachingSummary {

  vector< vector<string> > grantsPeerReviewed;
  vector< vector<string> > grantsIndustrySponsored;
  vector< vector<string> > clinicalPeerReviewed;
  vector< vector<string> > clinicalIndustrySponsored;

};

*/
struct publicationSummary {

  vector< vector<string> > books;
  vector< vector<string> > bookChapters;
  vector< vector<string> > booksEdited;
  vector< vector<string> > caseReports;
  vector< vector<string> > publishedAbstract;
  vector< vector<string> > journalArticle;
  vector< vector<string> > lettersToEditor;
  vector< vector<string> > clinicalCareGuidelines;
  vector< vector<string> > commentaries;
  vector< vector<string> > conferenceProceedings;
  vector< vector<string> > editorials;
  vector< vector<string> > invitedArticles;
  vector< vector<string> > magazineEntries;
  vector< vector<string> > manuals;
  vector< vector<string> > monographs;
  vector< vector<string> > multimedia;
  vector< vector<string> > newspaperArticles;
  vector< vector<string> > supervisedStudentPublications;
  vector< vector<string> > websiteOrVideos;
  vector< vector<string> > workingPapers;

};

class Database{

private:
  // the container for all the entries
  std::vector<ProcessedGrantsAndFundingRecord> grantsAndFundingRecord;
  std::vector<ProcessedTeachingRecord> teachingRecord;
  std::vector<ProcessedPublicationRecord> publicationRecord;
  std::vector<ProcessedPresentationRecord> presentationRecord;
public:
  // all the database request will be here for front end

  Database();
  void getGrantsAndFunding(vector< vector<string> >& results, vector<Filter*>& filters, vector<grantsAndFundingField>& fields);
  void grantsAndFundingSummary(struct grantsAndFundingSummary& sum, int earliestDate, int latestDate);

  void getPresentations(vector< vector<string> >& results, vector<Filter*>& filters, vector<grantsAndFundingField>& fields);
  void presentationSummary(struct presentationSummary& sum, int earliestDate, int latestDate);

  /*
  void getTeaching(vector< vector<string> >& results, vector<Filter*>& filters, vector<grantsAndFundingField>& fields);
  void teachingSummary(struct teachingSummary& sum, int earliestDate, int latestDate);
  */

  void getPublications(vector< vector<string> >& results, vector<Filter*>& filters, vector<grantsAndFundingField>& fields);
  void publicationSummary(struct publicationSummary& sum, int earliestDate, int latestDate);
};
#endif
