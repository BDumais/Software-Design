#ifndef PROCESSED_TEACHING_RECORD_H
#define PROCESSED_TEACHING_RECORD_H

#include <vector>
#include <string>
#include <iostream>

class ProcessedTeachingRecord{
private:
  std::string memberName;
  std::string primaryDomain;
  std::string startDate;
  std::string endDate;
  std::string program;
  std::string typeOfCourse;
  std::string geographicalScope;
  std::string hoursPerTeachingSessionOrWeek;
  std::string numberOfTeachingSessionsOrWeek;
  std::string totalHours;
  
public:
  // constructor
  ProcessedTeachingRecord(std::vector<std::string>& fields);
  // getter method
  std::string getMemberName();
  std::string getPrimaryDomain();
  std::string getStartDate();
  std::string getEndDate();
  std::string getProgram();
  std::string getTypeOfCourse();
  std::string getGeographicalScope();
  std::string getHoursPerTeachingSessionOrWeek();
  std::string getNumberOfTeachingSessionsOrWeek();
  std::string getTotalHours();
  // setter method
  void setMemberName(std::string& newValue);
  void setPrimaryDomain(std::string& newValue);
  void setStartDate(std::string& newValue);
  void setEndDate(std::string& newValue);
  void setProgram(std::string& newValue);
  void setTypeOfCourse(std::string& newValue);
  void setGeographicalScope(std::string& newValue);
  void setHoursPerTeachingSessionOrWeek(std::string& newValue);
  void setNumberOfTeachingSessionsOrWeek(std::string& newValue);
  void setTotalHours(std::string& newValue);
};

#endif