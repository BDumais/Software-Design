#include "Utility.h"

double Utility::stringToDouble(std::string& str){
  std::istringstream instream(str);
  double result;
  if (!(instream >> result))
  {
    return 0;
  }
  return result;
}
bool Utility::stringToBool(std::string& str){
  if (0 == str.compare("False"))
    return false;
  else
    return true;
}
int Utility::stringToInt(std::string& str){
  std::istringstream instream(str);
  int result;
  if (!(instream >> result)){
    return 0;
  }
  return result;
}
