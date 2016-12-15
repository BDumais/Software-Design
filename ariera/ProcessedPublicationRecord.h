#ifndef PROCESSED_PUBLICATION_RECORD_H
#define PROCESSED_PUBLICATION_RECORD_H

#include <string>
#include <vector>
#include <iostream>

class ProcessedPublicationRecord{
private:
  std::string memberName;
  std::string primaryDomain;
  std::string publicationStatus;
  std::string type;
  std::string statusDate;
  std::string role;
  std::string journalName;
  std::string author;
  std::string title;
public:
  ProcessedPublicationRecord(std::vector<std::string> fields);
  // getter method
  std::string getMemberName();
  std::string getPrimaryDomain();
  std::string getPublicationStatus();
  std::string getType();
  std::string getStatusDate();
  std::string getRole();
  std::string getJournalName();
  std::string getAuthor();
  std::string getTitle();
  // setter method
  void setMemberName(std::string& newValue);
  void setPrimaryDomain(std::string& newValue);
  void setPublicationStatus(std::string& newValue);
  void setType(std::string& newValue);
  void setStatusDate(std::string& newValue);
  void setRole(std::string& newValue);
  void setJournalName(std::string& newValue);
  void setAuthor(std::string& newValue);
  void setTitle(std::string& newValue);
};

#endif