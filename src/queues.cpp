#include "queues.h"
#include <algorithm>

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
  this->executeCommand(this->commands.front());
  this->commands.pop_front();
}

void Queues::start(std::list<int> start) {
  this->queueA = start;
  this->queueB.clear();
}

void Queues::executeCommand(const std::string &cmd) {
  COMMAND command{COMMAND::NONE};
  try {
    command = this->commandMap[cmd];
  } catch (...) {
  }
  switch (command) {
  case COMMAND::SA:
    this->sa();
    break;
  case COMMAND::SB:
    this->sb();
    break;
  case COMMAND::SS:
    this->ss();
    break;
  case COMMAND::PA:
    this->pa();
    break;
  case COMMAND::PB:
    this->pb();
    break;
  case COMMAND::RA:
    this->ra();
    break;
  case COMMAND::RB:
    this->rb();
    break;
  case COMMAND::RR:
    this->rr();
    break;
  case COMMAND::RRA:
    this->rra();
    break;
  case COMMAND::RRB:
    this->rrb();
    break;
  case COMMAND::RRR:
    this->rrr();
    break;
  default:
    break;
  }
}

void Queues::sa() {
  if (this->queueA.size() < 2) {
    return;
  }
  std::swap(*this->queueA.begin(), *(++this->queueA.begin()));
}

void Queues::sb() {
  if (this->queueB.size() < 2) {
    return;
  }
  std::swap(*this->queueB.begin(), *(++this->queueB.begin()));
}

void Queues::ss() {
  this->sa();
  this->sb();
}

void Queues::pa() {
  if (this->queueB.empty()) {
    return;
  }
  int firstElement = *this->queueA.begin();
  this->queueB.pop_front();
  this->queueA.push_front(firstElement);
}

void Queues::pb() {
  if (this->queueA.empty()) {
    return;
  }
  int firstElement = *this->queueB.begin();
  this->queueA.pop_front();
  this->queueB.push_front(firstElement);
}

void Queues::ra() {
  if (this->queueA.size() < 2) {
    return;
  }
  int firstElement = this->queueA.front();
  this->queueA.pop_front();
  this->queueA.push_back(firstElement);
}

void Queues::rb() {
  if (this->queueB.size() < 2) {
    return;
  }
  int firstElement = this->queueB.front();
  this->queueB.pop_front();
  this->queueB.push_back(firstElement);
}

void Queues::rr() {
  this->ra();
  this->rb();
}

void Queues::rra() {
  if (this->queueA.size() < 2) {
    return;
  }
  int lastElement = this->queueA.back();
  this->queueA.pop_back();
  this->queueA.push_front(lastElement);
}

void Queues::rrb() {
  if (this->queueB.size() < 2) {
    return;
  }
  int lastElement = this->queueB.back();
  this->queueB.pop_back();
  this->queueB.push_front(lastElement);
}

void Queues::rrr() {
  this->rra();
  this->rrb();
}
