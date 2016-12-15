#ifndef FILTER_H
#define FILTER_H

#include "ProcessedGrantsAndFundingRecord.h"
#include "ProcessedPublicationRecord.h"
#include "ProcessedPresentationRecord.h"

#include "GrantsAndFundingFields.h"
#include <string>

class Filter {
  public:
    virtual int filter(ProcessedGrantsAndFundingRecord& record);
    virtual int filter(ProcessedPublicationRecord& record);
    virtual int filter(ProcessedPresentationRecord& record);

};


#endif
