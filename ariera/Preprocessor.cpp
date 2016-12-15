#include "Preprocessor.h"
#define GRANTS_AND_FUNDING 0
#define PRESENTATION 1
#define PUBLICATION 2
#define TEACHING 3
#define ERROR 4
#define START_STATE 0
#define QUOTATION_STATE 1


Preprocessor::Preprocessor(const std::string& filename): grantsAndFundingRecord(), teachingRecord(), presentationRecord(), publicationRecord(){
  IOUtility::write(IOUtility::read(filename, grantsAndFundingRecord, teachingRecord, presentationRecord, publicationRecord), grantsAndFundingRecord, teachingRecord, presentationRecord, publicationRecord);
}

