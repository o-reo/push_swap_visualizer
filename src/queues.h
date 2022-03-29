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
    std::map<const char *, COMMAND> commandMap;

public:
    Queues();
    ~Queues();

    void step();
    void start(std::list<int> start);

    std::list<const char *> commands;
    std::list<int> queueA;
    std::list<int> queueB;

private:
  void executeCommand(const char *cmd);
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
