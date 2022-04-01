#include "pushswap.h"
#include "utils.h"
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

PushSwap::PushSwap() : path{"./push_swap"} {}
PushSwap::~PushSwap() {}

void PushSwap::run(const std::string &numbers) {
  this->commands.clear();
  std::array<char, 128> buffer;
  std::string result;
  std::string command = this->path + " " + numbers;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);

  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  this->commands = Utils::SplitStringToString(result, '\n');
}
