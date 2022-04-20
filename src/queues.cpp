#include "queues.h"
#include <algorithm>
#include <vector>
#include <string>

Queues::Queues()
    : commandMap{
          {"sa", COMMAND::SA},   {"sb", COMMAND::SB},   {"ss", COMMAND::SS},
          {"pa", COMMAND::PA},   {"pb", COMMAND::PB},   {"ra", COMMAND::RA},
          {"rb", COMMAND::RB},   {"rr", COMMAND::RR},   {"rra", COMMAND::RRA},
          {"rrb", COMMAND::RRB}, {"rrr", COMMAND::RRR},
      } {}
Queues::~Queues() {}

void Queues::step() {
  if (this->commands.empty()) {
    return;
  }
  this->_executeCommand(this->commands.front());
  this->executedCommands.push_front(this->commands.front());
  this->commands.pop_front();
}

void Queues::stepBack() {
  if (this->executedCommands.empty()) {
    return;
  }
  this->_executeReverseCommand(this->executedCommands.front());
  this->commands.push_front(this->executedCommands.front());
  this->executedCommands.pop_front();
}

std::list<int> Queues::_normalize(const std::list<int> &numbers) {
    std::list<int> normalized{numbers};
    std::vector<int> ordered(numbers.size());
    std::copy(numbers.begin(), numbers.end(), ordered.begin());
    std::sort(ordered.begin(), ordered.end());
    for (int &number : normalized) {
        const auto order = std::find(ordered.begin(), ordered.end(), number);
        number = order - ordered.begin();
    }
    return normalized;
}

void Queues::start(const std::list<int> &start) {
  this->queueA = this->_normalize(start);
  this->queueB.clear();
}

void Queues::_executeCommand(const std::string &cmd) {
  COMMAND command{COMMAND::NONE};
  try {
    command = this->commandMap[cmd];
  } catch (...) {
  }
  switch (command) {
  case COMMAND::SA:
    this->_sa();
    break;
  case COMMAND::SB:
    this->_sb();
    break;
  case COMMAND::SS:
    this->_ss();
    break;
  case COMMAND::PA:
    this->_pa();
    break;
  case COMMAND::PB:
    this->_pb();
    break;
  case COMMAND::RA:
    this->_ra();
    break;
  case COMMAND::RB:
    this->_rb();
    break;
  case COMMAND::RR:
    this->_rr();
    break;
  case COMMAND::RRA:
    this->_rra();
    break;
  case COMMAND::RRB:
    this->_rrb();
    break;
  case COMMAND::RRR:
    this->_rrr();
    break;
  default:
    break;
  }
}

void Queues::_executeReverseCommand(const std::string &cmd) {
  COMMAND command{COMMAND::NONE};
  try {
    command = this->commandMap[cmd];
  } catch (...) {
  }
  switch (command) {
  case COMMAND::SA:
    this->_sa();
    break;
  case COMMAND::SB:
    this->_sb();
    break;
  case COMMAND::SS:
    this->_ss();
    break;
  case COMMAND::PA:
    this->_pb();
    break;
  case COMMAND::PB:
    this->_pa();
    break;
  case COMMAND::RA:
    this->_rra();
    break;
  case COMMAND::RB:
    this->_rrb();
    break;
  case COMMAND::RR:
    this->_rrr();
    break;
  case COMMAND::RRA:
    this->_ra();
    break;
  case COMMAND::RRB:
    this->_rb();
    break;
  case COMMAND::RRR:
    this->_rr();
    break;
  default:
    break;
  }
}

void Queues::_sa() {
  if (this->queueA.size() < 2) {
    return;
  }
  std::swap(*this->queueA.begin(), *(++this->queueA.begin()));
}

void Queues::_sb() {
  if (this->queueB.size() < 2) {
    return;
  }
  std::swap(*this->queueB.begin(), *(++this->queueB.begin()));
}

void Queues::_ss() {
  this->_sa();
  this->_sb();
}

void Queues::_pa() {
  if (this->queueB.empty()) {
    return;
  }
  int firstElement = this->queueB.front();
  this->queueB.pop_front();
  this->queueA.push_front(firstElement);
}

void Queues::_pb() {
  if (this->queueA.empty()) {
    return;
  }
  int firstElement = this->queueA.front();
  this->queueA.pop_front();
  this->queueB.push_front(firstElement);
}

void Queues::_ra() {
  if (this->queueA.size() < 2) {
    return;
  }
  int firstElement = this->queueA.front();
  this->queueA.pop_front();
  this->queueA.push_back(firstElement);
}

void Queues::_rb() {
  if (this->queueB.size() < 2) {
    return;
  }
  int firstElement = this->queueB.front();
  this->queueB.pop_front();
  this->queueB.push_back(firstElement);
}

void Queues::_rr() {
  this->_ra();
  this->_rb();
}

void Queues::_rra() {
  if (this->queueA.size() < 2) {
    return;
  }
  int lastElement = this->queueA.back();
  this->queueA.pop_back();
  this->queueA.push_front(lastElement);
}

void Queues::_rrb() {
  if (this->queueB.size() < 2) {
    return;
  }
  int lastElement = this->queueB.back();
  this->queueB.pop_back();
  this->queueB.push_front(lastElement);
}

void Queues::_rrr() {
  this->_rra();
  this->_rrb();
}
