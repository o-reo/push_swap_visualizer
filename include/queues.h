#pragma once

#include <list>
#include <map>
#include <string>

class Queues {
  enum COMMAND { NONE, SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR };
  std::map<const std::string, COMMAND> commandMap;

public:
  Queues();
  ~Queues();

  void step();
  void stepBack();
  void start(const std::list<int> &start);

  std::list<std::string> commands;
  std::list<std::string> executedCommands;
  std::list<int> queueA;
  std::list<int> queueB;

private:
  void _executeCommand(const std::string &cmd);
  void _executeReverseCommand(const std::string &cmd);
  std::list<int> _normalize(const std::list<int> &numbers);
  void _sa();
  void _sb();
  void _ss();
  void _pa();
  void _pb();
  void _ra();
  void _rb();
  void _rr();
  void _rra();
  void _rrb();
  void _rrr();
};
