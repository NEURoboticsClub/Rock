#include "api.h"

/**
 * A base class representing a command for the robot to execute.
 */
class Command {
    public:
        /**
         * Initializes the command. This should be a one-time setup implementation.
         */
        void initialize() {}

        /**
         * Executes the command. This should be a blocking implementation.
         */
        void execute() {}

        /**
         * Checks if the command has finished executing. This should be a non-blocking
         * implementation.
         * 
         * @return true if the command is finished, false otherwise.
         */
        virtual bool isFinished() {}

        /**
         * Cleans up after the command has finished executing. This should be a one-time
         * implementation.
         */
        bool end() {}
};

/**
 * A command that runs a sequence of commands in order.
 */
class SequentialCommandGroup : public Command {
    public:
    /**
     * Constructs a SequentialCommandGroup with a list of commands to run in sequence.
     * 
     * @param commands A vector of Command objects to be executed in sequence.
     */
        SequentialCommandGroup(std::vector<Command> commands) : commands(commands) {}

    private:
        std::vector<Command> commands;
};

/**
 * A command that runs multiple commands in parallel.
 */
class ParallelCommandGroup : public Command {
    public:
        /**
         * Constructs a ParallelCommandGroup with a list of commands to run in parallel.
         * 
         * @param commands A vector of Command objects to be executed in parallel.
         */
        ParallelCommandGroup(std::vector<Command> commands) : commands(commands) {}

    private:
        std::vector<Command> commands;
};
