#include "pushswap.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

PushSwap::PushSwap() : path{"./push_swap"}{};
PushSwap::~PushSwap(){};

std::list<std::string> PushSwap::_split(const std::string &s, const char delimitor) {
  std::stringstream ss(s);
  std::string item;
  std::list<std::string> elems;
  while (std::getline(ss, item, delimitor)) {
    elems.push_back(item);
  }
  return elems;
}

void PushSwap::run(const std::string &numbers){
    std::array<char, 128> buffer;
    std::string result;
    std::string command = this->path + " " + numbers;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    this->commands = this->_split(result, '\n');
};
