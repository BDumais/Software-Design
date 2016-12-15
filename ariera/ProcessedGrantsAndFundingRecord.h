#ifndef PROCESSED_GRANTS_AND_FUNDING_RECORD_H
#define PROCESSED_GRANTS_AND_FUNDING_RECORD_H

#include <string>
#include <vector>
#include <iostream>

class ProcessedGrantsAndFundingRecord{
private:
  std::string memberName;
  std::string primaryDomain;
  std::string startDate;
  std::string endDate;
  std::string fundingType;	//"Grants" or "Clinical Trials"
  std::string status;		//Applied, Funded, Declined, Rejected, Not Funded
  std::string peerReviewed;
  std::string industryGrant;
  std::string role;	//says data type is "Co-Applicant"
  std::string title;
  std::string principalInvestigator;
  std::string coInvestigators;
  std::string totalAmount;
public:
  // constructor
  ProcessedGrantsAndFundingRecord(std::vector<std::string>& fields);
  ProcessedGrantsAndFundingRecord(std::string memberName, std::string primaryDomain, std::string startDate, std::string endDate, std::string fundingType, std::string status, std::string peerReviewed, std::string industryGrant, std::string role, std::string title, std::string principalInvestigator, std::string coInvestigators, std::string totalAmount);
  // getter method
  std::string getMemberName();
  std::string getPrimaryDomain();
  std::string getStartDate();
  std::string getEndDate();
  std::string getFundingType();
  std::string getStatus();
  std::string getPeerReviewed();
  std::string getIndustryGrant();
  std::string getRole();
  std::string getTitle();
  std::string getPrincipalInvestigator();
  std::string getCoInvestigators();
  std::string getTotalAmount();
  // setter method
  void setMemberName(std::string& newMemberName);
  void setPrimaryDomain(std::string& newPrimaryDomain);
  void setStartDate(std::string& newStartDate);
  void setEndDate(std::string& newEndDate);
  void setFundingType(std::string& newFundingType);
  void setStatus(std::string& newStatus);
  void setPeerReviewed(std::string& newPeerReviewed);
  void setIndustryGrant(std::string& newIndustryGrant);
  void setRole(std::string& newRole);
  void setTitle(std::string& newTitle);
  void setPrincipalInvestigator(std::string& newPrincipalInvestigator);
  void setCoInvestigators(std::string& newCoInvestigators);
  void setTotalAmount(std::string& newTotalAmount);
  // filter
  bool filter(std::string& upperBoundStartDate, std::string& lowerBoundStartDate, std::string& upperBoundEndDate, std::string& lowerBoundEndDate, std::string& upperBoundTotalAmount, std::string& lowerBoundTotalAmount);
};

#endif