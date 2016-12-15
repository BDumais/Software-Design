#include "IOUtility.h"
#define DEBUG 0
#define GRANTS_AND_FUNDING 0
#define PRESENTATION 1
#define PUBLICATION 2
#define TEACHING 3
#define ERROR 4
#define START_STATE 0
#define QUOTATION_STATE 1

// method to count the number of comma in the record string that is in the front of the found field
int IOUtility::getNumberOFComma(int position, std::string& line){
  int result = 0;
  // if the comma is in the quote, dont count it
  bool isQuoteState = false;
  for(int i = 0; i < position; i++){
    // flip the flag if current char is quotation mark
    if(line[i] == '"'){
      isQuoteState ^= true;
    }
    if(!isQuoteState && (line[i] == ',')){
      result ++;
    }
  }
  return result;
}

// method to read from a file
// return the file type
int IOUtility::read(const std::string& filename, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord){
  // open the file with input file stream
  std::ifstream in;
  in.open(filename);
  if(!in.is_open()){
    std::cout << "In io utility, error open " << filename << std::endl;
    std::exit(1);
  }
  char buffer[1000];
  std::vector<std::string> lineVector, mandatoryLineVector;
  std::vector<int> mandatoryPosition;
  std::string line;
  // because the title is in the first line, can be read by line
  in.getline(buffer,999);
  line = buffer;
  // in order to support the getColumnPosition, insert a comma before and after the line
  for(int i = line.length() - 1; i > 0; i--){
    buffer[i] = buffer[i-1];
  }
  buffer[0] = ',';
  buffer[line.length()] = ',';
  buffer[line.length() + 1] =0;
  line = buffer;
#if DEBUG
  std::cout << line.length() << std::endl;
  std::cout << "The formatted title line for " << filename << " is:\n";
  std::cout << line << std::endl;
#endif
  // detect the file type with the title line
  int inputFileType = IOUtility::inputFileTypeDetector(line);
#if DEBUG
  switch(inputFileType){
    case GRANTS_AND_FUNDING:{
      std::cout << "It is a grants and clinical funding record\n";
      break;
    }
    case TEACHING:{
      std::cout << "It is a teaching record\n";
      break;
    }
    case PUBLICATION:{
      std::cout << "It is a publication record\n";
      break;
    }
    case PRESENTATION:{
      std::cout << "It is a presentation record\n";
      break;
    }
    case ERROR:
    default:{
      std::cout << "Unknown file type\n";
    }
  }
#endif
  getColumnPosition(mandatoryPosition, inputFileType, line);
#if DEBUG
  std::cout << "The order of mandatory field is:\n";
  for(int i = 0; i < mandatoryPosition.size(); i++){
    std::cout << mandatoryPosition[i];
    if(i < mandatoryPosition.size()-1) std::cout << ",";
    else std::cout << std::endl;
  }
#endif
  while(!in.eof()){
    IOUtility::lineToVector(in, lineVector);
#if DEBUG
    for(int i = 0; i < lineVector.size(); i++){
      std::cout << lineVector[i] << "\n\n";
    }
#endif
    // this vector is reused for each new reocrd, so clear the previous data
    mandatoryLineVector.clear();
    
    switch(inputFileType){
      case GRANTS_AND_FUNDING:{
        // for the grants and clinical funding record
        // there are 13 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 13; i++){
          mandatoryLineVector.push_back(lineVector[mandatoryPosition[i]]);
        }
        grantsAndFundingRecord.push_back(ProcessedGrantsAndFundingRecord(mandatoryLineVector));
        break;
      }
      case PRESENTATION:{
        // for the presentation record
        // there are 6 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 6; i++){
          mandatoryLineVector.push_back(lineVector[mandatoryPosition[i]]);
        }
        presentationRecord.push_back(ProcessedPresentationRecord(mandatoryLineVector));
        break;
      }
      case PUBLICATION:{
        // for the publication record
        // there are 9 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 9; i++){
          mandatoryLineVector.push_back(lineVector[mandatoryPosition[i]]);
        }
        publicationRecord.push_back(ProcessedPublicationRecord(mandatoryLineVector));
        break;
      }
      case TEACHING:{
        // for the teaching record
        // there are 10 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 10; i++){
          mandatoryLineVector.push_back(lineVector[mandatoryPosition[i]]);
        }
        teachingRecord.push_back(ProcessedTeachingRecord(mandatoryLineVector));
        break;
      }
      default:{
        std::cout << "Wrong input file type from database.\n";
        std::exit(1);
      }
    }
  }
  // return the input file type, so the write function can know the file type
  return inputFileType;
}
int IOUtility::readDatabase(const std::string& filename, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord){
  // open the file with input file stream
  std::ifstream in;
  in.open(filename);
  if(!in.is_open()){
    std::cout << "In io utility database, error open " << filename << std::endl;
    std::exit(1);
  }
  char buffer[1000];
  std::vector<std::string> lineVector, mandatoryLineVector;
  std::vector<int> mandatoryPosition;
  std::string line;
  // because the title is in the first line, can be read by line
  in.getline(buffer,999);
  line = buffer;
  // detect the file type with the title line
  int inputFileType = IOUtility::inputFileTypeDetector(line);
#if DEBUG
  switch(inputFileType){
    case GRANTS_AND_FUNDING:{
      std::cout << "It is a grants and clinical funding record\n";
      break;
    }
    case TEACHING:{
      std::cout << "It is a teaching record\n";
      break;
    }
    case PUBLICATION:{
      std::cout << "It is a publication record\n";
      break;
    }
    case PRESENTATION:{
      std::cout << "It is a presentation record\n";
      break;
    }
    case ERROR:
    default:{
      std::cout << "Unknown file type\n";
    }
  }
#endif
  while(!in.eof()){
    IOUtility::lineToVector(in, lineVector);
#if DEBUG
    for(int i = 0; i < lineVector.size(); i++){
      std::cout << lineVector[i] << "\n\n";
    }
#endif
    // this vector is reused for each new reocrd, so clear the previous data
    mandatoryLineVector.clear();
    
    switch(inputFileType){
      case GRANTS_AND_FUNDING:{
        // for the grants and clinical funding record
        // there are 13 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 13; i++){
          mandatoryLineVector.push_back(lineVector[i]);
        }
        grantsAndFundingRecord.push_back(ProcessedGrantsAndFundingRecord(mandatoryLineVector));
        break;
      }
      case PRESENTATION:{
        // for the presentation record
        // there are 6 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 6; i++){
          mandatoryLineVector.push_back(lineVector[i]);
        }
        presentationRecord.push_back(ProcessedPresentationRecord(mandatoryLineVector));
        break;
      }
      case PUBLICATION:{
        // for the publication record
        // there are 9 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 9; i++){
          mandatoryLineVector.push_back(lineVector[i]);
        }
        publicationRecord.push_back(ProcessedPublicationRecord(mandatoryLineVector));
        break;
      }
      case TEACHING:{
        // for the teaching record
        // there are 10 mandatory fields
        // the order of the fields in the title line is stored in the mandatoryPosition vector
        // the actual fields of a record is stored in the lineVector
        // push the fields of the record to the mandatoryLineVector in the correct order
        // create the ProcessedGrantsAndFundingRecord using the vector, and put it into the record vector of the preprocessor/database
        for(int i = 0; i < 10; i++){
          mandatoryLineVector.push_back(lineVector[i]);
        }
        teachingRecord.push_back(ProcessedTeachingRecord(mandatoryLineVector));
        break;
      }
      default:{
        std::cout << "Wrong input file type from database.\n";
        std::exit(1);
      }
    }
  }
  // return the input file type, so the write function can know the file type
  return inputFileType;
}

// method to go through the title line to detect the type of the file
int IOUtility::inputFileTypeDetector(std::string& line){
  // if the line contains Funding Type, it is GrantsAndFundingRecord
  std::size_t found = line.find(",Funding Type,");
  if(found != std::string::npos) return GRANTS_AND_FUNDING;
  // if the line contains Publication Status, it is PublicationRecord
  found = line.find(",Publication Status,");
  if(found != std::string::npos) return PUBLICATION;
  // if the line contains Program, it is TeachingRecord
  found = line.find(",Program,");
  if(found != std::string::npos) return TEACHING;
  // if the line contains, Role, and it is not other record, so it is PresentationRecord
  found = line.find(",Role,");
  if(found != std::string::npos) return PRESENTATION;
  // otherwise, it is an error
  return ERROR;
}

// because the order of column can be changed, we need to read the order from the title line
void IOUtility::getColumnPosition(std::vector<int>& mandatoryPosition, int inputFileType, std::string& line){
  // use the buildin find function for string, it return the index of the first match position
  // Member Name and Primary Domain are common to all the records
  std::size_t found = line.find(",Member Name,");
  mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
  found = line.find(",Primary Domain,");
  mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
  switch(inputFileType){
    case GRANTS_AND_FUNDING:{
      // push the position of mandatory fields of grants and funding in the standard order
      found = line.find(",Start Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",End Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Funding Type,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Status,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Peer Reviewed?,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Industry Grant?,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Role,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Title,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Principal Investigator,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Co-Investigators,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Total Amount,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      break;
    }
    case PRESENTATION:{
      // push the position of mandatory fields of presentation in the standard order
      found = line.find(",Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Type,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Role,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Title,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      break;
    }
    case PUBLICATION:{
      // push the position of mandatory fields of publication in the standard order
      found = line.find(",Publication Status,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Type,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Status Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Role,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Journal Name | Published In | Book Title | etc.,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Author(s),");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Title,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      break;
    }
    case TEACHING:{
      // push the position of mandatory fields of teaching in the standard order
      found = line.find(",Start Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",End Date,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Program,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Type of Course / Activity,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Geographical Scope,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Hours per Teaching Session or Week,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Number of Teaching Sessions or Weeks,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      found = line.find(",Total Hours,");
      mandatoryPosition.push_back(IOUtility::getNumberOFComma(found, line));
      break;
    }
    default:{
      std::cout << "In the io utility getColumnPosition, get wrong file type\n";
      std::exit(1);
    }
  }
}
// write function for preprocessor to write the processed record to a csv file in a formatted way
void IOUtility::write(int fileType, std::vector<ProcessedGrantsAndFundingRecord>& grantsAndFundingRecord, std::vector<ProcessedTeachingRecord>& teachingRecord, std::vector<ProcessedPresentationRecord>& presentationRecord, std::vector<ProcessedPublicationRecord>& publicationRecord){

  switch(fileType){
    case GRANTS_AND_FUNDING:{
      // open the output file stream
      std::ofstream out;
      out.open("ProcessedGrantsClinicalFunding.csv", std::ios::out);
      if(!out.is_open()){
        out << "Error writing file\n";
        out.close();
        std::exit(1);
      }
      // first write the title line
      out << "Member Name,Primary Domain,Start Date,End Date,Funding Type,Status,Peer Reviewed?,Industry Grant?,Role,Title,Principal Investigator,Co-Investigators,Total Amount\n";
      // write all the record to the file with the field in the order defined by the title line
      // all the field are surrounded by quotation mark
      // use formatQuotationmark to make quotation mark in the field to double quotation mark
      for(int i = 0; i < grantsAndFundingRecord.size(); i++){
        std::string currentString = grantsAndFundingRecord[i].getMemberName();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getPrimaryDomain();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getStartDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getEndDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getFundingType();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getStatus();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getPeerReviewed();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getIndustryGrant();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getRole();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getTitle();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getPrincipalInvestigator();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getCoInvestigators();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = grantsAndFundingRecord[i].getTotalAmount();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\"" << std::endl;
      }
      break;
    }
    case TEACHING:{
      // open the output file stream
      std::ofstream out;
      out.open("ProcessedTeaching.csv", std::ios::out);
      if(!out.is_open()){
        out << "Error writing file\n";
        out.close();
        std::exit(1);
      }
      // first write the title line
      out << "Member Name,Primary Domain,Start Date,End Date,Program,Type of Course / Activity,Geographical Scope,Hours per Teaching Session or Week,Number of Teaching Sessions or Weeks,Total Hours" << std::endl;
      // write all the record to the file with the field in the order defined by the title line
      // all the field are surrounded by quotation mark
      // use formatQuotationmark to make quotation mark in the field to double quotation mark
      for(int i = 0; i < teachingRecord.size(); i++){
        std::string currentString = teachingRecord[i].getMemberName();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getPrimaryDomain();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getStartDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getEndDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getProgram();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getTypeOfCourse();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getGeographicalScope();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getHoursPerTeachingSessionOrWeek();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getNumberOfTeachingSessionsOrWeek();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = teachingRecord[i].getTotalHours();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\"" << std::endl;
      }
      break;
    }
    case PUBLICATION:{
      std::ofstream out;
      out.open("ProcessedPublication.csv", std::ios::out);
      if(!out.is_open()){
        out << "Error writing file\n";
        out.close();
        std::exit(1);
      }
      out << "Member Name,Primary Domain,Publication Status,Type,Status Date,Role,Journal Name | Published In | Book Title | etc.,Author(s),Title" << std::endl;
      // write all the record to the file with the field in the order defined by the title line
      // all the field are surrounded by quotation mark
      // use formatQuotationmark to make quotation mark in the field to double quotation mark
      for(int i = 0; i < publicationRecord.size(); i++){
        std::string currentString = publicationRecord[i].getMemberName();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getPrimaryDomain();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getPublicationStatus();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getType();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getStatusDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getRole();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getJournalName();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getAuthor();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = publicationRecord[i].getTitle();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\"" << std::endl;
      }
      break;
    }
    case PRESENTATION:{
      std::ofstream out;
      out.open("ProcessedPresentation.csv", std::ios::out);
      if(!out.is_open()){
        out << "Error writing file\n";
        out.close();
        std::exit(1);
      }
      out << "Member Name,Primary Domain,Date,Type,Role,Title" << std::endl;
      // write all the record to the file with the field in the order defined by the title line
      // all the field are surrounded by quotation mark
      // use formatQuotationmark to make quotation mark in the field to double quotation mark
      for(int i = 0; i < presentationRecord.size(); i++){
        std::string currentString = presentationRecord[i].getMemberName();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = presentationRecord[i].getPrimaryDomain();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = presentationRecord[i].getDate();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = presentationRecord[i].getType();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = presentationRecord[i].getRole();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\",";
        currentString = presentationRecord[i].getTitle();
        out << "\"" << IOUtility::formatQuotationMark(currentString) << "\"" << std::endl;
      }
      break;
    }
    default:{
      std::cout << "Wrong input file type from database.\n";
      std::exit(1);
    }
  }
}

// method to make all the quotation mark in the field to become double quotaion mark
std::string IOUtility::formatQuotationMark(std::string& field){
  std::string result = "";
  for(int i = 0; i < field.length(); i++){
    if(field[i] == '"'){
      result.push_back('"');
    }
    result.push_back(field[i]);
  }
  return result;
}
// method to read character one by one from input file stream
void IOUtility::lineToVector(std::ifstream& in, std::vector<std::string>& result){
  result.clear();
  char currentCharacter;
  std::string currentString;
  int state = START_STATE;
  // read until reach the end of the file
  while(!in.eof()){
    // get a character
    currentCharacter = in.get();
    switch(state){
      case START_STATE:{
        // if get a comma that is not in the quote, we get a full field, push it to the stack
        // after pushing, clean the string
        if(currentCharacter == ','){
          result.push_back(currentString);
          currentString.clear();
        }
        else if(currentCharacter == '\n'){
          result.push_back(currentString);
          currentString.clear();
          goto end;
        }
        else if(currentCharacter == '"'){
          state = QUOTATION_STATE;
        }
        else{
          // if the current character is not quote or comma, append the character to the end of string
          currentString.push_back(currentCharacter);
        }
        break;
      }
      case QUOTATION_STATE:{
        if(currentCharacter == '"'){
          // if we have two quote in a row, it is a quote mark in the field
          if(in.peek() == '"'){
            currentString.push_back(currentCharacter); //add to string
            in.get(); //skip the next quotation
          }
          else{
            state = START_STATE;
          }
        }
        else{
          currentString.push_back(currentCharacter);
        }
      }
    }
  }
end:
  return;
  
}
