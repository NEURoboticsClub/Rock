#pragma once
#include "api.h"
#include <queue>
#include <vector>

/**
 * A base class representing a command for the robot to execute.
 */
class Command {
    public:
        /**
         * Initializes the command. This should be a one-time setup implementation.
         */
        virtual void initialize();

        /**
         * Executes the command. This should be a blocking implementation.
         */
        virtual void execute();

        /**
         * Checks if the command has finished executing. This should be a non-blocking
         * implementation.
         * 
         * @return true if the command is finished, false otherwise.
         */
        virtual bool isFinished();

        /**
         * Cleans up after the command has finished executing. This should be a one-time
         * implementation.
         */
        virtual void end();

        virtual ~Command() = default;
};

class TimeoutCommand : public Command {
    public:
        /**
         * Constructs a TimeoutCommand with a specified duration.
         * 
         * @param durationMs The duration in milliseconds after which the command should time out.
         */
        TimeoutCommand(std::uint32_t durationMs);

        void initialize() override;
        bool isFinished() override;

    private:
        std::uint32_t durationMs;
        std::uint32_t startTime;
};

/**
 * A command that runs a sequence of commands in order.
 */
class SequentialCommandGroup : public Command {
    public:
        /**
         * Constructs a SequentialCommandGroup with a list of commands to run in sequence.
         * 
         * @param commands A queue of Command objects to be executed in sequence.
         */
        SequentialCommandGroup(std::queue<Command*> commands);

        void initialize() override;
        void execute() override;
        bool isFinished() override;
        void end() override;

    private:
        std::queue<Command*> commands;
        pros::Task* currentTask;
        Command* currentCommand;  // Pointer instead of reference
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
        ParallelCommandGroup(std::vector<Command*> commands);

        void initialize() override;
        void execute() override;
        bool isFinished() override;
        void end() override;

    private:
        std::vector<Command*> commands;
        std::vector<pros::Task*> currentTasks;
};

class InstantCommand : public Command {
    public:
        /**
         * Constructs an InstantCommand with a callable action.
         * 
         * @param action A callable object (e.g., lambda function) to be executed instantly.
         */
        InstantCommand(std::function<void()> action);

        void initialize() override;

    private:
        std::function<void()> action;
};
