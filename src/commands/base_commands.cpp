#include "commands/base_commands.h"

// Base Command class implementations
void Command::initialize() {}
void Command::execute() {}
bool Command::isFinished() { return true; }
void Command::end() {}

// TimeoutCommand implementation
TimeoutCommand::TimeoutCommand(std::uint32_t durationMs) : durationMs(durationMs), startTime(0) {}

void TimeoutCommand::initialize() {
    startTime = pros::millis();
}

bool TimeoutCommand::isFinished() {
    return (pros::millis() - startTime) >= durationMs;
}

// SequentialCommandGroup implementation
SequentialCommandGroup::SequentialCommandGroup(std::queue<Command*> commands)
    : commands(commands), currentTask(nullptr), currentCommand(nullptr) {}

void SequentialCommandGroup::initialize() {
    if (commands.empty()) {
        return;
    }
    currentCommand = commands.front();
    currentCommand->initialize();
}

void SequentialCommandGroup::execute() {
    while (!commands.empty()) {
        currentTask = new pros::Task([this]() {
            currentCommand->execute();
        });

        while (!currentCommand->isFinished()) {
            pros::delay(10);
        }

        currentCommand->end();
        currentTask->remove();
        delete currentTask;
        commands.pop();

        if (commands.empty()) {
            break;
        }
        currentCommand = commands.front();
        currentCommand->initialize();
    }
}

bool SequentialCommandGroup::isFinished() {
    return commands.empty();
}

void SequentialCommandGroup::end() {
    if (currentCommand != nullptr) {
        currentCommand->end();
    }
    if (currentTask != nullptr) {
        currentTask->remove();
        delete currentTask;
    }
}

SequentialCommandGroup::~SequentialCommandGroup() {
     end();
}

// ParallelCommandGroup implementation
ParallelCommandGroup::ParallelCommandGroup(std::vector<Command*> commands)
    : commands(commands) {}

void ParallelCommandGroup::initialize() {
    for (Command* command : commands) {
        command->initialize();
    }
}

void ParallelCommandGroup::execute() {
    for (Command* command : commands) {
        pros::Task* task = new pros::Task([command]() {
            command->execute();
        });
        currentTasks.push_back(task);
    }
}

bool ParallelCommandGroup::isFinished() {
    for (Command* command : commands) {
        if (!command->isFinished()) {
            return false;
        }
    }
    return true;
}

void ParallelCommandGroup::end() {
    for (Command* command : commands) {
        command->end();
    }
    for (pros::Task* task : currentTasks) {
        task->remove();
        delete task;
    }
}

ParallelCommandGroup::~ParallelCommandGroup() {
    end();
}

// InstantCommand implementation
InstantCommand::InstantCommand(std::function<void()> action) : action(action) {}

void InstantCommand::initialize() {
    action();
}