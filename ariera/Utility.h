#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <sstream>

namespace Utility{
  double stringToDouble(std::string& str);
  bool stringToBool(std::string& str);
  int stringToInt(std::string& str);
  bool isGreaterThan(std::string& record, std::string& filterRange);
  bool isSmallerThan(std::string& record, std::string& filterRange);
}
#endif
