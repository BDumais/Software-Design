#ifndef IOUTILITY_H
#define IOUTILITY_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "ProcessedGrantsAndFundingRecord.h"
#include "ProcessedPublicationRecord.h"
#include "ProcessedPresentationRecord.h"
#include "ProcessedTeachingRecord.h"
#include <cstdlib>

namespace IOUtility {
  int inputFileTypeDetector(std::string& line);
  void lineToVector(std::ifstream& in, std::vector<std::string>& result);
  int read(const std::string& filename, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord);
  int readDatabase(const std::string& filename, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord);
  void getColumnPosition(std::vector<int>& mandatoryPosition, int inputFileType, std::string& line);
  int getNumberOFComma(int position, std::string& line);
  void write(int fileType, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord);
  std::string formatQuotationMark(std::string& field);
}

#endif