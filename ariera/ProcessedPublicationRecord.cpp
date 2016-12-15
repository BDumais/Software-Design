#include "ProcessedPublicationRecord.h"
ProcessedPublicationRecord::ProcessedPublicationRecord(std::vector<std::string> fields){
  if(fields.size() != 9){
    std::cout << "In the constructor of ProcessedPublicationRecord, the input fields have wrong size\n";
    exit(1);
  }
  this->memberName = fields[0];
  this->primaryDomain = fields[1];
  this->publicationStatus = fields[2];
  this->type = fields[3];
  this->statusDate = fields[4];
  this->role = fields[5];
  this->journalName = fields[6];
  this->author = fields[7];
  this->title = fields[8];
}
std::string ProcessedPublicationRecord::getMemberName(){
  return this->memberName;
}
std::string ProcessedPublicationRecord::getPrimaryDomain(){
  return this->primaryDomain;
}
std::string ProcessedPublicationRecord::getPublicationStatus(){
  return this->publicationStatus;
}
std::string ProcessedPublicationRecord::getType(){
  return this->type;
}
std::string ProcessedPublicationRecord::getStatusDate(){
  return this->statusDate;
}
std::string ProcessedPublicationRecord::getRole(){
  return this->role;
}
std::string ProcessedPublicationRecord::getJournalName(){
  return this->journalName;
}
std::string ProcessedPublicationRecord::getAuthor(){
  return this->author;
}
std::string ProcessedPublicationRecord::getTitle(){
  return this->title;
}
void ProcessedPublicationRecord::setMemberName(std::string& newMemberName){
  this->memberName = newMemberName;
}
void ProcessedPublicationRecord::setPrimaryDomain(std::string& newPrimaryDomain){
  this->primaryDomain = newPrimaryDomain;
}
void ProcessedPublicationRecord::setPublicationStatus(std::string& newValue){
  this->publicationStatus = newValue;
}
void ProcessedPublicationRecord::setType(std::string& newValue){
  this->type = newValue;
}
void ProcessedPublicationRecord::setStatusDate(std::string& newValue){
  this->statusDate = newValue;
}
void ProcessedPublicationRecord::setRole(std::string& newValue){
  this->role = newValue;
}
void ProcessedPublicationRecord::setJournalName(std::string& newValue){
  this->journalName = newValue;
}
void ProcessedPublicationRecord::setAuthor(std::string& newValue){
  this->author = newValue;
}
void ProcessedPublicationRecord::setTitle(std::string& newValue){
  this->title = newValue;
}