#include "ProcessedTeachingRecord.h"

ProcessedTeachingRecord::ProcessedTeachingRecord(std::vector<std::string>& fields){
  if(fields.size() != 10){
    std::cout << "In the constructor of ProcessedTeachingRecord, the input fields vector has wrong size\n";
    exit(1);
  }
  this->memberName = fields[0];
  this->primaryDomain = fields[1];
  this->startDate = fields[2];
  this->endDate = fields[3];
  this->program = fields[4];
  this->typeOfCourse = fields[5];
  this->geographicalScope = fields[6];
  this->hoursPerTeachingSessionOrWeek = fields[7];
  this->numberOfTeachingSessionsOrWeek = fields[8];
  this->totalHours = fields[9];
}

std::string ProcessedTeachingRecord::getMemberName(){
  return this->memberName;
}
std::string ProcessedTeachingRecord::getPrimaryDomain(){
  return this->primaryDomain;
}
std::string ProcessedTeachingRecord::getStartDate(){
  return this->startDate;
}
std::string ProcessedTeachingRecord::getEndDate(){
  return this->endDate;
}
std::string ProcessedTeachingRecord::getProgram(){
  return this->program;
}
std::string ProcessedTeachingRecord::getTypeOfCourse(){
  return this->typeOfCourse;
}
std::string ProcessedTeachingRecord::getGeographicalScope(){
  return this->geographicalScope;
}
std::string ProcessedTeachingRecord::getHoursPerTeachingSessionOrWeek(){
  return this->hoursPerTeachingSessionOrWeek;
}
std::string ProcessedTeachingRecord::getNumberOfTeachingSessionsOrWeek(){
  return this->numberOfTeachingSessionsOrWeek;
}
std::string ProcessedTeachingRecord::getTotalHours(){
  return this->totalHours;
}
void ProcessedTeachingRecord::setMemberName(std::string& newMemberName){
  this->memberName = newMemberName;
}
void ProcessedTeachingRecord::setPrimaryDomain(std::string& newPrimaryDomain){
  this->primaryDomain = newPrimaryDomain;
}
void ProcessedTeachingRecord::setStartDate(std::string& newValue){
  this->startDate = newValue;
}
void ProcessedTeachingRecord::setEndDate(std::string& newValue){
  this->endDate = newValue;
}
void ProcessedTeachingRecord::setProgram(std::string& newValue){
  this->program = newValue;
}
void ProcessedTeachingRecord::setTypeOfCourse(std::string& newValue){
  this->typeOfCourse = newValue;
}
void ProcessedTeachingRecord::setGeographicalScope(std::string& newValue){
  this->geographicalScope = newValue;
}
void ProcessedTeachingRecord::setHoursPerTeachingSessionOrWeek(std::string& newValue){
  this->hoursPerTeachingSessionOrWeek = newValue;
}
void ProcessedTeachingRecord::setNumberOfTeachingSessionsOrWeek(std::string& newValue){
  this->numberOfTeachingSessionsOrWeek = newValue;
}
void ProcessedTeachingRecord::setTotalHours(std::string& newValue){
  this->totalHours = newValue;
}

