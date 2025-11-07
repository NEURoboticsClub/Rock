#include "commands/base_commands.h"

// Base Command class implementations
void Command::initialize() {}
void Command::execute() {}
bool Command::isFinished() { return true; }
void Command::end() {}

// SequentialCommandGroup implementation
void SequentialCommandGroup::initialize() {
    if (commands.empty()) {
        return;
    }
    Command currentCommand = commands.front();
    currentCommand.initialize();
}

void SequentialCommandGroup::execute() {
    while (!commands.empty()) {
        currentCommand = &commands.front();

        currentCommand->initialize();
        currentTask = new pros::Task([this]() {
            currentCommand->execute();
        });

        while (!currentCommand->isFinished()) {
            pros::delay(10);
        }

        currentCommand->end();
        currentTask->remove();
        commands.pop();
    }
}

bool SequentialCommandGroup::isFinished() {
    return commands.empty();
}

void SequentialCommandGroup::end() {
    delete currentTask;
}

// ParallelCommandGroup implementation
void ParallelCommandGroup::initialize() {
    for (Command& command : commands) {
        command.initialize();
    }
}

void ParallelCommandGroup::execute() {
    for (Command& command : commands) {
        pros::Task* task = new pros::Task([&command]() {
            command.execute();
        });
        currentTasks.push_back(task);
    }
}

bool ParallelCommandGroup::isFinished() {
    for (Command& command : commands) {
        if (!command.isFinished()) {
            return false;
        }
    }
    return true;
}

void ParallelCommandGroup::end() {
    for (Command& command : commands) {
        command.end();
    }
    for (pros::Task* task : currentTasks) {
        task->remove();
        delete task;
    }
}