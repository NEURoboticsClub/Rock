#include "commands/base_commands.h"

// Base Command class implementations
void Command::initialize() {}
void Command::execute() {
    while (true) {
        pros::delay(10);
    }
}
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
    while (true) {
        if (!commands.empty()) {
            currentTask = new pros::Task([this]() {
                currentCommand->execute();
            });

            while (!currentCommand->isFinished()) {
                pros::delay(10);
            }

            currentTask->remove();
            delete currentTask;
            currentCommand->end();
            commands.pop();

            if (!commands.empty()) {
                currentCommand = commands.front();
                currentCommand->initialize();
            }
        }
    }
}

bool SequentialCommandGroup::isFinished() {
    return commands.empty();
}

void SequentialCommandGroup::end() {
    if (currentTask != nullptr) {
        // Checks if task is running
        if (currentTask->get_state() == 0) {
            currentTask->remove();
        }
        delete currentTask;
    }
}

SequentialCommandGroup::~SequentialCommandGroup() {
     end();
     while (!commands.empty()) {
         delete commands.front();
         commands.pop();
     }
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

    while (true) {
        pros::delay(10);
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
        // Checks if task is running
        if (task->get_state() == 0) {
            task->remove();
        }
        delete task;
    }

    currentTasks.clear();
}

ParallelCommandGroup::~ParallelCommandGroup() {
    end();
    for (Command* command : commands) {
        delete command;
    }
}

// InstantCommand implementation
InstantCommand::InstantCommand(std::function<void()> action) : action(action) {}

void InstantCommand::initialize() {
    action();
}