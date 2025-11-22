#include "subsystems.h"

RobotConfig config = hsky1Config;

//===================== DEVICES =====================
pros::Rotation xEncoder(11);
pros::Rotation yEncoder(-12);

pros::IMU imu1(0);
pros::IMU imu2(0);

//==================== SUBSYSTEMS ====================

OdometryPerpendicularIMU odom(&xEncoder, &yEncoder, &imu1, &imu2);

pros::Controller ctrl(pros::E_CONTROLLER_MASTER);

TankDrive tankdrive(config.drivebase, ctrl, &odom);
Transport intake(config.intake, ctrl);
Transport centerStageLower(config.centerStageLower, ctrl);
Transport centerStageUpper(config.centerStageUpper, ctrl);
Transport hood(config.hood, ctrl);
Pneumatics intakeLeft(config.intakeLeft, ctrl);
Pneumatics intakeRight(config.intakeRight, ctrl);
Pneumatics scoring(config.scoring, ctrl);

//====================== UTILS ======================

void deviceInit() {
    // IMU initialization
	imu1.reset();
	imu2.reset();
	while (imu1.is_calibrating() || imu2.is_calibrating()) pros::delay(10);

    // Encoder initialization
	xEncoder.reset_position();
	yEncoder.reset_position();
}

void robotInit() {
	deviceInit();
	odom.init();
}