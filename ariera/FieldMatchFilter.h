#ifndef FIELD_MATCH_FILTER_H
#define FIELD_MATCH_FILTER_H

#include "Filter.h"

class FieldMatchFilter: public Filter {
  grantsAndFundingField field;
  std::string value;
  public:
    FieldMatchFilter(grantsAndFundingField field, std::string value);
    int filter(ProcessedGrantsAndFundingRecord& record);

    int filter(ProcessedPublicationRecord& record);

    int filter(ProcessedPresentationRecord& record);

    void setValue(std::string val);
};
#endif
