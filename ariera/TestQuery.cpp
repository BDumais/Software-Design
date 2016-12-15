#include "Database.h"
#include "Preprocessor.h"
#include "GrantsAndFundingFields.h"
#include "FieldMatchFilter.h"
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
void printResults(vector< vector<string> >& results);
int nextNameTotal(vector< vector<string> >* newList, vector<string>& result);
void printResultsWithTotal(vector< vector<string> >& results);


int main(void){

#define TEST_PRESENTATIONS
//#define TEST_PUBLICATIONS

  Preprocessor preprocessor0("GrantsClinicalFunding_sample.csv");
  Preprocessor preprocessor1("Presentations_sample.csv");
  Preprocessor preprocessor2("Publications_sample.csv");
  Preprocessor preprocessor3("Teaching_sample.csv");
  Database db;
  //Define result of query vector
  vector< vector<string> > results;

#ifdef TEST_GRANTS_AND_FUNDING
   
  // Contains 4 vectors for summary. Definition in Database.h
  struct grantsAndFundingSummary sum;

  // Should query database for all entire summary
  db.grantsAndFundingSummary(sum, 2000, 2012);

  // The following code just displays results
  std::cout << "Grants records (peer reviewed):" << sum.grantsPeerReviewed.size() << " results" << std::endl;
  printResults(sum.grantsPeerReviewed);
  std::cout << std::endl;
  std::cout << "Grants records (industry sponsored):" << sum.grantsIndustrySponsored.size() << " results" << std::endl;
  printResults(sum.grantsIndustrySponsored);
  std::cout << std::endl;
  std::cout << "Clinical trial records (peer reviewed):" << results.size() << " results" << std::endl;
  printResults(sum.clinicalPeerReviewed);
  std::cout << std::endl;
  std::cout << "Clinical trial records (industry sponsored): " << results.size() << " results"  << std::endl;
  printResults(sum.clinicalIndustrySponsored);
  std::cout << std::endl;

#endif

#ifdef TEST_PUBLICATIONS
  // Contains vectors for all the types of publications
  struct publicationSummary sum;
  db.publicationSummary(sum, 2000, 2018);

  std::cout << "Books: " << sum.books.size() << " results" << std::endl;
  printResults(sum.books);
  std::cout << std::endl;
  std::cout << "Book Chapters: " << sum.bookChapters.size() << " results" << std::endl;
  printResults(sum.bookChapters);
  std::cout << std::endl;
  std::cout << "Multimedia: " << sum.multimedia.size() << " results" << std::endl;
  printResults(sum.multimedia);
  std::cout << std::endl;
  std::cout << "Case Reports: " << sum.caseReports.size() << " results" << std::endl;
  printResults(sum.caseReports);
  std::cout << std::endl;
  std::cout << "Published Abstracts: " << sum.publishedAbstract.size() << " results" << std::endl;
  printResults(sum.publishedAbstract);
  std::cout << std::endl;
  std::cout << "Journal Articles: " << sum.journalArticle.size() << " results" << std::endl;
  printResults(sum.journalArticle);
  std::cout << std::endl;
  std::cout << "Working Papers: " << sum.workingPapers.size() << " results" << std::endl;
  printResults(sum.workingPapers);
  std::cout << std::endl;

  // There are more types of publications...
#endif

#ifdef TEST_PRESENTATIONS
  // Contains vectors for all the types of presentations
  struct presentationSummary sum;
  db.presentationSummary(sum, 2000, 2018);

  std::cout << "Invited Lectures: " << sum.invitedLectures.size() << " results" << std::endl;
  printResults(sum.invitedLectures);
  std::cout << std::endl;
  std::cout << "Abstract Presented: " << sum.abstractPresented.size() << " results" << std::endl;
  printResults(sum.abstractPresented);
  printResultsWithTotal(sum.abstractPresented);
  std::cout << std::endl;
  std::cout << "Visiting Professorship: " << sum.visitingProfessorship.size() << " results" << std::endl;
  printResultsWithTotal(sum.visitingProfessorship);
  std::cout << std::endl;

#endif

  return 0;
}

/**
 * Helper method: uses iterators to print out results
 */
void printResults(vector< vector<string> >& results){
  vector< vector<string> >::iterator resultIter;
  vector<string>::iterator fieldIter;
  resultIter = results.begin();
  while(resultIter != results.end()){
    fieldIter = resultIter->begin();
    std::cout << "\t";
    while (fieldIter != resultIter->end()){
      std::cout << *fieldIter << " | ";
      fieldIter++;
    }
    resultIter++;
    std::cout << std::endl;
  }
}
void printResultsWithTotal(vector< vector<string> >& results){

  vector<string>::iterator fieldIter;

  vector<string> nextName;

  nextNameTotal(&results, nextName);

  do {

    fieldIter = nextName.begin();

    std::cout << "\t";

    while (fieldIter != nextName.end()){
      std::cout << *fieldIter << " | ";
      fieldIter++;
    }
    std::cout << std::endl;
  }
  while(nextNameTotal(NULL, nextName) != 0);

}

int nextNameTotal(vector< vector<string> >* newList, vector<string>& result){

  result.clear();

  static vector< vector<string> > *list;
  static vector< vector<string> >::iterator iter;

  if (newList != NULL){
    list = newList;
    iter = list->begin();
  }

  string name = (*iter)[0];

  int count = 0;

  for (;;){

    if (iter == list->end())
      return 0;

    if ((*iter)[0].compare(name) != 0)
      break;

    count++;
    iter++;
  }
  
  std::ostringstream convert;
  convert << count;
    
  result.push_back(name);
  result.push_back(convert.str());
  return 1;
}
