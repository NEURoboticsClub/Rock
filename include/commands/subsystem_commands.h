#pragma once
#include "base_commands.h"
#include "subsystems.h"

class EngageIntake : public InstantCommand {
  public:
    /**
     * Constructs an EngageIntake command with specified parameters, meant to set
     * the intake pneumatics to intake from the loader.
     *
     * @param intakeLeft Reference to the Pneumatics object controlling the left intake.
     * @param intakeRight Reference to the Pneumatics object controlling the right intake.
     */
    EngageIntake(Pneumatics &intakeLeft, Pneumatics &intakeRight);
};

class DisengageIntake : public InstantCommand {
  public:
    /**
     * Constructs a DisengageIntake command with specified parameters, meant to set
     * the intake pneumatics to disengage from the loader.
     *
     * @param intakeLeft Reference to the Pneumatics object controlling the left intake.
     * @param intakeRight Reference to the Pneumatics object controlling the right intake.
     */
    DisengageIntake(Pneumatics &intakeLeft, Pneumatics &intakeRight);
};

class RunIntake : public TimeoutCommand {
  public:
    /**
     * Constructs a RunIntake command with specified parameters, meant to run the
     * intake motors at a given speed.
     *
     * @param intake Reference to the Intake subsystem.
     * @param centerStageLower Reference to the Center Stage Lower subsystem.
     * @param centerStageUpper Reference to the Center Stage Upper subsystem.
     * @param durationMs Duration in milliseconds for which to run the intake.
     */
    RunIntake(Transport &intake, Transport &centerStageLower, 
        Transport &centerStageUpper, uint32_t durationMs);

    void initialize() override;
    void end() override;

  private:
    Transport *intake;
    Transport *centerStageLower;
    Transport *centerStageUpper;
};

class SortOutIntake : public TimeoutCommand {
  public:
    /**
     * Constructs a SortOut command with specified parameters, meant to run the
     * sorting mechanism motors at a given speed.
     *
     * @param intake Reference to the Intake subsystem.
     * @param centerStageLower Reference to the Center Stage Lower subsystem.
     * @param durationMs Duration in milliseconds for which to run the sorting mechanism.
     */
    SortOutIntake(Transport &intake, Transport &centerStageLower, uint32_t durationMs);

    void initialize() override;
    void end() override;

  private:
    Transport *intake;
    Transport *centerStageLower;
};

class RunScoring : public TimeoutCommand {
  public:
    /**
     * Constructs a RunScoring command with specified parameters, meant to run the
     * scoring mechanism motors at a given speed.
     *
     * @param intake Reference to the Intake subsystem.
     * @param centerStageLower Reference to the Center Stage Lower subsystem.
     * @param centerStageUpper Reference to the Center Stage Upper subsystem.
     * @param hood Reference to the Hood subsystem.
     * @param durationMs Duration in milliseconds for which to run the scoring mechanism.
     */
    RunScoring(Transport &intake, Transport &centerStageLower, Transport &centerStageUpper, 
        Transport &hood, uint32_t durationMs);

    void initialize() override;
    void end() override;

  private:
    Transport *intake;
    Transport *centerStageLower;
    Transport *centerStageUpper;
    Transport *hood;
};