#pragma once

#include <list>
#include <map>

class Queues {
    enum COMMAND
    {
        NONE,
        SA,
        SB,
        SS,
        PA,
        PB,
        RA,
        RB,
        RR,
        RRA,
        RRB,
        RRR
    };
    std::map<const std::string, COMMAND> commandMap;

public:
    Queues();
    ~Queues();

    void step();
    void start(std::list<int> start);

    std::list<std::string> commands;
    std::list<int> queueA;
    std::list<int> queueB;

private:
  void executeCommand(const std::string &cmd);
  void normalize();
  void sa();
  void sb();
  void ss();
  void pa();
  void pb();
  void ra();
  void rb();
  void rr();
  void rra();
  void rrb();
  void rrr();
};
