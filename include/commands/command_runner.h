#pragma once
#include "api.h"
#include "commands/base_commands.h"
#include <queue>

/**
 * A class that runs a sequence of commands.
 */
class CommandRunner {
public:
    /**
     * Constructs a CommandRunner with a queue of commands.
     * 
     * @param commands A queue of Command objects to be executed in sequence.
     */
    CommandRunner(std::queue<Command> commands) : commands(commands) {}

    /**
     * Runs the commands in sequence.
     */
    void run();

private:
    std::queue<Command> commands;
};
