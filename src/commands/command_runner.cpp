#include "commands/command_runner.h"

CommandRunner::CommandRunner(std::queue<Command*> commands)
    : commands(commands), currentTask(nullptr), currentCommand(nullptr) {}

void CommandRunner::run() {
    while (!commands.empty()) {
        currentCommand = commands.front();

        currentCommand->initialize();
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
    }
    delete currentCommand;
}

CommandRunner::~CommandRunner() {
    if (currentCommand != nullptr) {
        currentCommand->end();
    }
    if (currentTask != nullptr) {
        currentTask->remove();
        delete currentTask;
    }
}