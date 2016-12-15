#include "ProcessedGrantsAndFundingRecord.h"

ProcessedGrantsAndFundingRecord::ProcessedGrantsAndFundingRecord(std::vector<std::string>& fields){
  if(fields.size() != 13){
    std::cout << "In the constructor of ProcessedGrantsAndFundingRecord, the size of input fields is not correct.\n";
    exit(1);
  }
  this->memberName = fields[0];
  this->primaryDomain = fields[1];
  this->startDate = fields[2];
  this->endDate = fields[3];
  this->fundingType = fields[4];
  this->status = fields[5];
  this->peerReviewed = fields[6];
  this->industryGrant = fields[7];
  this->role = fields[8];
  this->title = fields[9];
  this->principalInvestigator = fields[10];
  this->coInvestigators = fields[11];
  this->totalAmount = fields[12];
}

ProcessedGrantsAndFundingRecord::ProcessedGrantsAndFundingRecord(std::string memberName, std::string primaryDomain, std::string startDate, std::string endDate, std::string fundingType, std::string status, std::string peerReviewed, std::string industryGrant, std::string role, std::string title, std::string principalInvestigator, std::string coInvestigators, std::string totalAmount){
  this->memberName = memberName;
  this->primaryDomain = primaryDomain;
  this->startDate = startDate;
  this->endDate = endDate;
  this->fundingType = fundingType;
  this->status = status;
  this->peerReviewed = peerReviewed;
  this->industryGrant = industryGrant;
  this->role = role;
  this->title = title;
  this->principalInvestigator = principalInvestigator;
  this->coInvestigators = coInvestigators;
  this->totalAmount = totalAmount;
}

std::string ProcessedGrantsAndFundingRecord::getMemberName(){
  return this->memberName;
}
std::string ProcessedGrantsAndFundingRecord::getPrimaryDomain(){
  return this->primaryDomain;
}
void ProcessedGrantsAndFundingRecord::setMemberName(std::string& newMemberName){
  this->memberName = newMemberName;
}
void ProcessedGrantsAndFundingRecord::setPrimaryDomain(std::string& newPrimaryDomain){
  this->primaryDomain = newPrimaryDomain;
}

std::string ProcessedGrantsAndFundingRecord::getStartDate(){
  return this->startDate;
}
std::string ProcessedGrantsAndFundingRecord::getEndDate(){
  return this->endDate;
}
std::string ProcessedGrantsAndFundingRecord::getFundingType(){
  return this->fundingType;
}
std::string ProcessedGrantsAndFundingRecord::getStatus(){
  return this->status;
}
std::string ProcessedGrantsAndFundingRecord::getPeerReviewed(){
  return this->peerReviewed;
}
std::string ProcessedGrantsAndFundingRecord::getIndustryGrant(){
  return this->industryGrant;
}
std::string ProcessedGrantsAndFundingRecord::getRole(){
  return this->role;
}
std::string ProcessedGrantsAndFundingRecord::getTitle(){
  return this->title;
}
std::string ProcessedGrantsAndFundingRecord::getPrincipalInvestigator(){
  return this->principalInvestigator;
}
std::string ProcessedGrantsAndFundingRecord::getCoInvestigators(){
  return this->coInvestigators;
}
std::string ProcessedGrantsAndFundingRecord::getTotalAmount(){
  return this->totalAmount;
}
void ProcessedGrantsAndFundingRecord::setStartDate(std::string& newStartDate){
  this->startDate = newStartDate;
}
void ProcessedGrantsAndFundingRecord::setEndDate(std::string& newEndDate){
  this->endDate = newEndDate;
}
void ProcessedGrantsAndFundingRecord::setFundingType(std::string& newFundingType){
  this->fundingType = newFundingType;
}
void ProcessedGrantsAndFundingRecord::setStatus(std::string& newStatus){
  this->status = newStatus;
}
void ProcessedGrantsAndFundingRecord::setPeerReviewed(std::string& newPeerReviewed){
  this->peerReviewed = newPeerReviewed;
}
void ProcessedGrantsAndFundingRecord::setIndustryGrant(std::string& newIndustryGrant){
  this->industryGrant = newIndustryGrant;
}
void ProcessedGrantsAndFundingRecord::setRole(std::string& newRole){
  this->role = newRole;
}

void ProcessedGrantsAndFundingRecord::setTitle(std::string& newTitle){
  this->title = newTitle;
}
void ProcessedGrantsAndFundingRecord::setPrincipalInvestigator(std::string& newPrincipalInvestigator){
  this->principalInvestigator = newPrincipalInvestigator;
}
void ProcessedGrantsAndFundingRecord::setCoInvestigators(std::string& newCoInvestigators){
  this->coInvestigators = newCoInvestigators;
}
void ProcessedGrantsAndFundingRecord::setTotalAmount(std::string& newTotalAmount){
  this->totalAmount = newTotalAmount;
}
/*
bool ProcessedGrantsAndFundingRecord::filter(std::string& upperBoundStartDate, std::string& lowerBoundStartDate, std::string& upperBoundEndDate, std::string& lowerBoundEndDate, std::string& upperBoundTotalAmount, std::string& lowerBoundTotalAmount){
  bool result = true;
  Utility::compare
}
*/
