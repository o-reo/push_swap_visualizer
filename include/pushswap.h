#pragma once

#include <string>
#include <list>

class PushSwap {
private:
    std::list<std::string> _split(const std::string &input, const char delimitor);

public:
    PushSwap();
    ~PushSwap();
    void run(const std::string &numbers);

    std::string path;
    std::list<std::string> commands;
};
