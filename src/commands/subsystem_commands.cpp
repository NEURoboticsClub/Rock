#include "subsystem_commands.h"

// EngageIntake Command Implementation
EngageIntake::EngageIntake(Pneumatics &intakeLeft, Pneumatics &intakeRight)
    : InstantCommand([&intakeLeft, &intakeRight]() {
          intakeLeft.extendPiston();
          intakeRight.extendPiston();
      }) {}

// DisengageIntake Command Implementation
DisengageIntake::DisengageIntake(Pneumatics &intakeLeft, Pneumatics &intakeRight)
    : InstantCommand([&intakeLeft, &intakeRight]() {
          intakeLeft.retractPiston();
          intakeRight.retractPiston();
      }) {}

// RunIntake Command Implementation
RunIntake::RunIntake(Transport &intake, Transport &centerStageLower, uint32_t durationMs)
    : TimeoutCommand(durationMs), intake(&intake), centerStageLower(&centerStageLower) {}

void RunIntake::initialize() {
    TimeoutCommand::initialize();
    intake->moveIn();
    centerStageLower->moveIn();
}

// RunScoring Command Implementation
RunScoring::RunScoring(Transport &scoring, Transport &centerStageUpper, uint32_t durationMs)
    : TimeoutCommand(durationMs), scoring(&scoring), centerStageUpper(&centerStageUpper) {}

void RunScoring::initialize() {
    TimeoutCommand::initialize();
    scoring->moveIn();
    centerStageUpper->moveIn();
}