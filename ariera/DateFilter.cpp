#include "DateFilter.h"

DateFilter::DateFilter(int earliestYear, int latestYear): earliestDate(earliestYear), latestDate(latestYear) {
  ;
}
int DateFilter::filter(ProcessedGrantsAndFundingRecord& record){
  std::string date = record.getStartDate();
  if (date.compare("") == 0)
    return 1;
  std::istringstream yearStream(date.substr(0,4));
  int year;
  if (!(yearStream >> year))
    return 1;
  if (year >= earliestDate)
    if (year <= latestDate)
      return 0;
  return 1;
}
int DateFilter::filter(ProcessedPublicationRecord& record){
  std::string date = record.getStatusDate();
  if (date.compare("") == 0)
    return 1;
  std::istringstream yearStream(date.substr(0,4));
  int year;
  if (!(yearStream >> year))
    return 1;
  if (year >= earliestDate)
    if (year <= latestDate)
      return 0;
  return 1;
}
int DateFilter::filter(ProcessedPresentationRecord& record){
  std::string date = record.getDate();
  if (date.compare("") == 0)
    return 1;
  std::istringstream yearStream(date.substr(0,4));
  int year;
  if (!(yearStream >> year))
    return 1;
  if (year >= earliestDate)
    if (year <= latestDate)
      return 0;
  return 1;
}
