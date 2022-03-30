#include <string>
#include <vector>

class PushSwap {
private:
    std::vector<std::string> _split(const std::string &input, const char delimitor);

public:
    PushSwap();
    ~PushSwap();
    void run(const std::string &numbers);

    std::string path;
    std::vector<std::string> commands;
};
