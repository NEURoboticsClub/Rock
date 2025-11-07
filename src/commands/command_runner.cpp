#include "commands/command_runner.h"

void CommandRunner::run() {
    pros::Task* currentTask;
    while (!commands.empty()) {
        Command* currentCommand = commands.front();

        currentCommand->initialize();
        currentTask = new pros::Task([&currentCommand]() {
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
}