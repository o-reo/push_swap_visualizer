#include "utils.h"
#include <list>
#include <sstream>
#include <string>

namespace Utils {
std::list<std::string> SplitStringToString(const std::string &s,
                                           const char delimitor) {
  std::stringstream ss(s);
  std::string item;
  std::list<std::string> elems;
  while (std::getline(ss, item, delimitor)) {
    elems.push_back(item);
  }
  return elems;
}

std::list<int> SplitStringToInt(const std::string &s, const char delimitor) {
  std::stringstream ss(s);
  std::string item;
  std::list<int> elems;
  while (std::getline(ss, item, delimitor)) {
    elems.push_back(std::stoi(item));
  }
  return elems;
}
} // namespace Utils
