#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "ProcessedGrantsAndFundingRecord.h"
#include "ProcessedPublicationRecord.h"
#include "ProcessedPresentationRecord.h"
#include "ProcessedTeachingRecord.h"
#include "IOUtility.h"

class Preprocessor{
private:
  std::vector<ProcessedGrantsAndFundingRecord> grantsAndFundingRecord;
  std::vector<ProcessedTeachingRecord> teachingRecord;
  std::vector<ProcessedPublicationRecord> publicationRecord;
  std::vector<ProcessedPresentationRecord> presentationRecord;
public:
  Preprocessor(const std::string& filename);
};

#endif