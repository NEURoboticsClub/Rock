#ifndef SUBSYSTEMS_SUBSYSTEMS_H
#define SUBSYSTEMS_SUBSYSTEMS_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "odometry.h"
#include "odometry_drivebase.h"
#include "pneumatics.h"
#include "robot_config.h"
#include "tank_drive.h"
#include "transport.h"

/**
 * Subsystems are initialized here. All subsystems should take a configuration
 * (either the whole robot configuration or one of its composite structs) and
 * the controller, both defined here, in their constructor.
 */

extern pros::Controller ctrl;
extern RobotConfig config;
extern TankDrive tankdrive;
extern OdometryPerpendicularIMU odom;
extern Transport intake;
extern Transport centerStageLower;
extern Transport centerStageUpper;
extern Transport hood;
extern Pneumatics intakeLeft;
extern Pneumatics intakeRight;
extern Pneumatics scoring;

void robotInit();

#endif