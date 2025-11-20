#include "commands/drive_commands.h"

// NOTE: This is an example of how we can implement commands.
DriveDeadReckon::DriveDeadReckon(TankDrive &drive, int leftSpeed, 
    int rightSpeed, int durationMs)
    : drive(&drive), leftSpeed(leftSpeed), 
    rightSpeed(rightSpeed), durationMs(durationMs) {}

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

// DriveToPoint Command Implementation
DriveToPoint::DriveToPoint(TankDrive &drive, Odometry &odom, double targetX, double targetY)
    : drive_(&drive), odom_(&odom), targetX_(targetX), targetY_(targetY), reached_(false) {}

void DriveToPoint::execute() {
    drive_->driveToPoint(targetX_, targetY_);
}

bool DriveToPoint::isFinished() {
    Pose currentPose;
    odom_->getPose(&currentPose);
    return std::abs(targetX_ - currentPose.x) < 1.0 &&
           std::abs(targetY_ - currentPose.y) < 1.0;
}

void DriveToPoint::end() {
    drive_->driveMotors(0, 0);
}