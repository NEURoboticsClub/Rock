#include "commands/drive_commands.h"

// NOTE: This is an example of how we can implement commands.
DriveDeadReckon::DriveDeadReckon(TankDrive &drive, Odometry &odom, 
    int leftSpeed, int rightSpeed, int durationMs)
    : drive(&drive), odom(&odom), 
    leftSpeed(leftSpeed), rightSpeed(rightSpeed), durationMs(durationMs) {}

void DriveDeadReckon::initialize() {
    drive->driveMotors(leftSpeed, rightSpeed);
    startTime = pros::millis();
}

bool DriveDeadReckon::isFinished() {
    return pros::millis() - startTime >= durationMs;
}

void DriveDeadReckon::end() {
    drive->driveMotors(0, 0);
}