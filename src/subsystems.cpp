#include "subsystems.h"

RobotConfig config = hsky1Config;

//===================== DEVICES =====================
pros::Rotation xEncoder(5);
pros::Rotation yEncoder(10);

pros::IMU imu1(3);
pros::IMU imu2(7);

//==================== SUBSYSTEMS ====================

OdometryPerpendicularIMU odom(&xEncoder, &yEncoder, &imu1, &imu2);

pros::Controller ctrl(pros::E_CONTROLLER_MASTER);

TankDrive tankdrive(config.drivebase, ctrl, &odom);
Transport intake(config.intake, ctrl);
Transport scoring(config.scoring, ctrl);
Pneumatics mogoClamp(config.mogoClamp, ctrl);

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