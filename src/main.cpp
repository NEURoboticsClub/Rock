#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	printf("starting opcontrol");

	robotInit();

	tankdrive.initialize(config.drivebase.driveStyle);
	intake.initialize();
	centerStageLower.initialize();
	centerStageUpper.initialize();
	hood.initialize();
	intakeLeft.initialize();
	intakeRight.initialize();
	scoring.initialize();


	// // // left auto
	// Pose* startPose = new Pose(0.0, 0.0, M_PI/4.0);
	// odom.setPose(startPose);
	// delete startPose;

	// std::queue<Command*> commandQueue;

	// commandQueue.push(new SequentialCommandGroup(std::queue<Command*>({
	// 	new DriveDistance(tankdrive, odom, 30, 2000),
	// 	new TurnToHeading(tankdrive, odom, 135.0, 2000),
		
	// 	// new DriveDistance(tankdrive, odom, 12, 2000),
		
	// 	// new EngageIntake(intakeLeft, intakeRight),
	// 	// new RunIntake(intake, centerStageLower, centerStageUpper,1000),
	// 	// new DisengageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, -26, 2000),

	// 	// new RunScoring(intake, centerStageLower, centerStageUpper, hood, 2000),

	// 	// new DriveDistance(tankdrive, odom, 26, 2000),
	// 	// new SortOutIntake(intake, centerStageLower, 2000),


	// 	// new RunIntake(intake, centerStageLower, centerStageUpper,2000),
	// 	// new DisengageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, -26, 2000),
	// 	// new TimeoutCommand(200),
	// 	// new RunScoring(intake, centerStageLower, centerStageUpper, hood, 2000)


	// 	// // Drive to the loader
	// 	// new TimeoutCommand(500),
	// 	// new DriveDistance(tankdrive, odom, 26.0, 2000),
	// 	// new TurnToHeading(tankdrive, odom, 90.0, 2000),

	// 	// // Intake from the loader
	// 	// new DriveDistance(tankdrive, odom, 12.0, 2000),
	// 	// new EngageIntake(intakeLeft, intakeRight), 
	// 	// new RunIntake(intake, centerStageLower, centerStageUpper,2000),

	// 	// // Drive to scoring zone
	// 	// new DisengageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, -26.0, 1000),

	// 	// new TimeoutCommand(2000),

	// 	// // Score
	// 	// new RunScoring(intake, centerStageLower, centerStageUpper, hood, 2000),

	// 	// // Intake more, discard opposite color 
	// 	// new EngageIntake(intakeLeft, intakeRight), 
	// 	// new DriveDistance(tankdrive, odom, 5.0, 500),
	// 	// new SortOutIntake(intake, centerStageLower, 2000),

	// 	// // Wait and intake again
	// 	// new TimeoutCommand(1000),
	// 	// new RunIntake(intake, centerStageLower, centerStageUpper, 2000),

	// 	// // Drive to scoring zone
	// 	// new DisengageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, -26.0, 1000),

	// 	// // Score
	// 	// new RunScoring(intake, centerStageLower, centerStageUpper, hood, 2000),

	// 	// // Intake again
	// 	// new EngageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, 5.0, 500),
	// 	// new RunIntake(intake, centerStageLower, centerStageUpper, 2000),

	// 	// // Drive to scoring zone
	// 	// new DisengageIntake(intakeLeft, intakeRight),
	// 	// new DriveDistance(tankdrive, odom, -26.0, 1000),

	// 	// // Score
	// 	// new RunScoring(intake, centerStageLower, centerStageUpper, hood, 2000)
	// })));

	// CommandRunner commandRunner(commandQueue);
	// commandRunner.run();

	while (true) {
		pros::delay(50);
	}
}