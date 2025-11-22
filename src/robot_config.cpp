#include "robot_config.h"

/*

Odom Front-back 11
Odom left-right 12

Lower stage 13
Next Stage 21
Before hood 6
Hood 1

Left intake 2
Right intake 10
Front Left 4
Front back top 5
Left back bottom 16


Front right 9
Right back top 8
Right back bottom 20
*/


//================== HSKY 1 CONFIG ==================

AutonConstants hsky1AutonConstants = {
	3.25,
	12.376,
	300.0 * 57.0 / 39.0,  // encoder ticks per revolution

	5,
	0,
	0.1,

	50,
	0,
	0,

	0.5,
	1.0,

	1.0,  // velocity units
	1.0	  // velocity units
};

DrivebaseConfig hsky1Drivebase = {
	{-4, 5, -16, 14}, // left
	{9, -8, 20, -3}, // right
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	ARCADE,
	0.75,
	hsky1AutonConstants
};

TransportConfig hsky1Intake = {
	{-2, 10, -13}, // left, right, roller
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	pros::E_CONTROLLER_DIGITAL_L1, // up
	pros::E_CONTROLLER_DIGITAL_L2, // down
	0.75 // duty cycle
};

TransportConfig hsky1CenterStageLower = {
	{21}, // motor ports
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	pros::E_CONTROLLER_DIGITAL_L1, // up
	pros::E_CONTROLLER_DIGITAL_L2, // down
	0.75 // duty cycle
};

TransportConfig hsky1CenterStageUpper = {
	{-6}, // motor ports
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	pros::E_CONTROLLER_DIGITAL_L1, // up
	pros::E_CONTROLLER_DIGITAL_L2, // down
	0.25 // duty cycle
};

TransportConfig hsky1Hood = {
	{-1}, // motor ports
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	pros::E_CONTROLLER_DIGITAL_R1, // up
	pros::E_CONTROLLER_DIGITAL_R2, // down
	0.75 // duty cycle
};

PneumaticsConfig hsky1IntakeLeft = {
	'a', // port
	pros::E_CONTROLLER_DIGITAL_RIGHT, // extend
	pros::E_CONTROLLER_DIGITAL_LEFT // retract
};

PneumaticsConfig hsky1IntakeRight = {
	'b', // port
	pros::E_CONTROLLER_DIGITAL_RIGHT, // extend
	pros::E_CONTROLLER_DIGITAL_LEFT // retract
};

PneumaticsConfig hsky1Scoring = {
	'c', // port
	pros::E_CONTROLLER_DIGITAL_UP, // extend
	pros::E_CONTROLLER_DIGITAL_DOWN // retract
};

RobotConfig hsky1Config = {
	hsky1Drivebase,
	hsky1Intake,
	hsky1CenterStageLower,
	hsky1CenterStageUpper,
	hsky1Hood,
	hsky1IntakeLeft,
	hsky1IntakeRight,
	hsky1Scoring
};

//================== HSKY 2 CONFIG ==================
AutonConstants hsky2AutonConstants = {
	3.25,
	12.376,
	300.0 * 57.0 / 39.0,  // encoder ticks per revolution

	1,
	0.0,
	0.1,

	2,
	0.05,
	0.1,

	0.5,
	1.0,

	1.0,  // velocity units
	1.0	  // velocity units
};

DrivebaseConfig hsky2Drivebase = {
	{-10, -1, 18},
	{4, 5, -2},
	pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600,
	ARCADE,
	0.25,
	hsky2AutonConstants
};

RobotConfig hsky2Config = {
	
};
