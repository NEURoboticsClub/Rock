#include "robot_config.h"

//================== HSKY 1 CONFIG ==================

AutonConstants hsky1AutonConstants = {
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

DrivebaseConfig hsky1Drivebase = {
	{-12, -11, 13},			{2, 1, -3}, pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600, ARCADE,		0.25,
	hsky1AutonConstants};

TransportConfig hsky1Intake = {{21, -18},
							   pros::E_MOTOR_BRAKE_COAST,
							   pros::E_MOTOR_GEAR_600,
							   pros::E_CONTROLLER_DIGITAL_L1,
							   pros::E_CONTROLLER_DIGITAL_L2,
							   1.0};

TransportConfig hsky1Scoring = {{15, -16},
								pros::E_MOTOR_BRAKE_COAST,
								pros::E_MOTOR_GEAR_600,
								pros::E_CONTROLLER_DIGITAL_R1,
								pros::E_CONTROLLER_DIGITAL_R2,
								0.25};

PneumaticsConfig hsky1MogoClamp = {'a', pros::E_CONTROLLER_DIGITAL_B,
								   pros::E_CONTROLLER_DIGITAL_X};

RobotConfig hsky1Config = {hsky1Drivebase, hsky1Intake, hsky1Scoring,
						   hsky1MogoClamp};

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
	{-10, -1, 18},			{4, 5, -2}, pros::E_MOTOR_BRAKE_COAST,
	pros::E_MOTOR_GEAR_600, ARCADE,		0.25,
	hsky2AutonConstants};

TransportConfig hsky2Intake = {{-16, 6},
							   pros::E_MOTOR_BRAKE_COAST,
							   pros::E_MOTOR_GEAR_600,
							   pros::E_CONTROLLER_DIGITAL_L1,
							   pros::E_CONTROLLER_DIGITAL_L2,
							   1.0};

TransportConfig hsky2Scoring = {{9, -14},
								pros::E_MOTOR_BRAKE_COAST,
								pros::E_MOTOR_GEAR_600,
								pros::E_CONTROLLER_DIGITAL_R1,
								pros::E_CONTROLLER_DIGITAL_R2,
								0.25};

PneumaticsConfig hsky2MogoClamp = {'a', pros::E_CONTROLLER_DIGITAL_X,
								   pros::E_CONTROLLER_DIGITAL_B};

RobotConfig hsky2Config = {hsky2Drivebase, hsky2Intake, hsky2Scoring,
						   hsky2MogoClamp};