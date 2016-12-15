#ifndef DATE_FILTER_H
#define DATE_FILTER_H

#include "Filter.h"
#include <sstream>

class DateFilter: public Filter {
  private:
    int earliestDate;
    int latestDate;

  public:
    DateFilter(int earliest, int latest);
    int filter(ProcessedGrantsAndFundingRecord& record);
    int filter(ProcessedPublicationRecord& record);
    int filter(ProcessedPresentationRecord& record);
};

#endif
