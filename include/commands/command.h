#include "api.h"

class Command {
public:
    virtual void execute() {}
    virtual bool isFinished() {}
    ~Command() {}
};

class WaitCommand : public Command {
public:
    WaitCommand(int duration) : duration(duration) {}

    void execute() override {}

    bool isFinished() override {}

private:
    int duration;
    // vex::timer timer;
};
