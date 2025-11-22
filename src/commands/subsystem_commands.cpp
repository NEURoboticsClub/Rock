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
RunIntake::RunIntake(Transport &intake, Transport &centerStageLower, 
    Transport &centerStageUpper, uint32_t durationMs)
    : TimeoutCommand(durationMs), intake(&intake), 
      centerStageLower(&centerStageLower), centerStageUpper(&centerStageUpper) {}

void RunIntake::initialize() {
    TimeoutCommand::initialize();
    intake->moveIn();
    centerStageLower->moveIn();
    centerStageUpper->moveIn();
}

void RunIntake::end() {
    intake->stop();
    centerStageLower->stop();
    centerStageUpper->stop();
}

// SortOutIntake Command Implementation
SortOutIntake::SortOutIntake(Transport &intake, Transport &centerStageLower, uint32_t durationMs)
    : TimeoutCommand(durationMs), intake(&intake), centerStageLower(&centerStageLower) {}

void SortOutIntake::initialize() {
    TimeoutCommand::initialize();
    intake->moveIn();
    centerStageLower->moveOut();
}

void SortOutIntake::end() {
    intake->stop();
    centerStageLower->stop();
}

// RunScoring Command Implementation
RunScoring::RunScoring(Transport &intake, Transport &centerStageLower, 
    Transport &centerStageUpper, Transport &hood, uint32_t durationMs)
    : TimeoutCommand(durationMs), intake(&intake), centerStageLower(&centerStageLower),
      centerStageUpper(&centerStageUpper), hood(&hood) {}

void RunScoring::initialize() {
    TimeoutCommand::initialize();
    intake->moveIn();
    centerStageLower->moveIn();
    centerStageUpper->moveIn();
    hood->moveIn();
}

void RunScoring::end() {
    intake->stop();
    centerStageLower->stop();
    centerStageUpper->stop();
    hood->stop();
}