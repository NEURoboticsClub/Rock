#include "api.h"
#include "commands/command.h"
#include <queue>

class CommandRunner {
public:
    CommandRunner(std::queue<Command> commands) : commands(commands) {}
    void run() {}

private:
    std::queue<Command> commands;
};
