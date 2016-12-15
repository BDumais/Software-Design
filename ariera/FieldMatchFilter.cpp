#include "FieldMatchFilter.h"

FieldMatchFilter::FieldMatchFilter(grantsAndFundingField field, std::string value){
  this->field = field;
  this->value = value;
}
int FieldMatchFilter::filter(ProcessedGrantsAndFundingRecord& record){
  std::string field_value;
  switch (this->field){
    case MEMBER_NAME:             field_value = record.getMemberName();
      break;
    case PRIMARY_DOMAIN:          field_value = record.getPrimaryDomain();
      break;
    case START_DATE:              field_value = record.getStartDate();
      break;
    case END_DATE:                field_value = record.getEndDate();
      break;
    case FUNDING_TYPE:            field_value = record.getFundingType();
      break;
    case STATUS:                  field_value = record.getStatus();
      break;
    case PEER_REVIEWED:           field_value = record.getPeerReviewed();
      break;
    case INDUSTRY_GRANT:          field_value = record.getIndustryGrant();
      break;
    case ROLE:                    field_value = record.getRole();
      break;
    case TITLE:                   field_value = record.getTitle();
      break;
    case PRINCIPAL_INVESTIGATOR:  field_value = record.getPrincipalInvestigator();
      break;
    case CO_INVESTIGATORS:        field_value = record.getCoInvestigators();
      break;
    case TOTAL_AMOUNT:            field_value = record.getTotalAmount();
      break;
  } 
  if (this->value.compare(field_value) == 0)
    return 0;
  else
    return 1;
}
int FieldMatchFilter::filter(ProcessedPublicationRecord& record){
  std::string field_value;
  switch (this->field){
    case MEMBER_NAME:             field_value = record.getMemberName();
      break;
    case PRIMARY_DOMAIN:          field_value = record.getPrimaryDomain();
      break;
    case PUBLICATION_STATUS:      field_value = record.getPublicationStatus();
      break;
    case TYPE:                    field_value = record.getType();
      break;
    case STATUS_DATE:             field_value = record.getStatusDate();
      break;
    case ROLE:                    field_value = record.getRole();
      break;
    case JOURNAL_NAME:            field_value = record.getJournalName();
      break;
    case AUTHOR:                  field_value = record.getAuthor();
      break;
    case TITLE:                   field_value = record.getTitle();
      break;
  } 
  if (this->value.compare(field_value) == 0)
    return 0;
  else
    return 1;
}
int FieldMatchFilter::filter(ProcessedPresentationRecord& record){
  std::string field_value;
  switch (this->field){
    case MEMBER_NAME:             field_value = record.getMemberName();
      break;
    case PRIMARY_DOMAIN:          field_value = record.getPrimaryDomain();
      break;
    case DATES:                    field_value = record.getDate();
      break;
    case TYPE:                    field_value = record.getType();
      break;
    case ROLE:                    field_value = record.getRole();
      break;
    case TITLE:                   field_value = record.getTitle();
      break;
  } 
  if (this->value.compare(field_value) == 0)
    return 0;
  else
    return 1;
}

void FieldMatchFilter::setValue(std::string val){
  this->value = val;
}
