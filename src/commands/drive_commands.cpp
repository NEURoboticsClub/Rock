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
DriveDistance::DriveDistance(TankDrive &drive, Odometry &odom, double targetDistance)
    : drive_(&drive), odom_(&odom), targetDistance_(targetDistance), targetX_(0), targetY_(0) {}

void DriveDistance::initialize() {
    Pose currentPose;
    odom_->getPose(&currentPose);
    targetX_ = currentPose.x + targetDistance_ * cos(currentPose.theta);
    targetY_ = currentPose.y + targetDistance_ * sin(currentPose.theta);
}

void DriveDistance::execute() {
    drive_->driveDistance(targetDistance_);
}

bool DriveDistance::isFinished() {
    Pose currentPose;
    odom_->getPose(&currentPose);
    return std::abs(targetX_ - currentPose.x) < 1.0 &&
           std::abs(targetY_ - currentPose.y) < 1.0;
}

void DriveDistance::end() {
    drive_->driveMotors(0, 0);
}