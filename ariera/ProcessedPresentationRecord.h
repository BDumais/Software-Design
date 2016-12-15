#ifndef PROCESSED_PRESENTATION_RECORD_H
#define PROCESSED_PRESENTATION_RECORD_H

#include <string>
#include <vector>
#include <iostream>

class ProcessedPresentationRecord{
private:
  std::string memberName;
  std::string primaryDomain;
  std::string date;
  std::string type;
  std::string role;
  std::string title;
  
public:
  // constructor
  ProcessedPresentationRecord(std::vector<std::string>& fields);
  // getter method
  std::string getMemberName();
  std::string getPrimaryDomain();
  std::string getDate();
  std::string getType();
  std::string getRole();
  std::string getTitle();
  // setter method
  void setMemberName(std::string& newValue);
  void setPrimaryDomain(std::string& newValue);
  void setDate(std::string& newValue);
  void setType(std::string& newValue);
  void setRole(std::string& newValue);
  void setTitle(std::string& newValue);
};
#endif