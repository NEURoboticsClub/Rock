#include "commands/drive_commands.h"

// NOTE: This is an example of how we can implement commands.
DriveDistance::DriveDistance(TankDrive &drive, Odometry &odom, double distanceInches)
    : drive(&drive), odom(&odom), distanceInches(distanceInches) {}

void DriveDistance::initialize() {
    finished = false;
    drive->driveDistance(distanceInches);
}

void DriveDistance::execute() {
    // TODO: We may want to implement the follower logic inside the commands 
    // instead of the TankDrive class in order to ensure the method ends 
    // properly. For now, this will be blank.
}

bool DriveDistance::isFinished() {
    // The real logic here would be checking the odom to see if we are close enough 
    // to the target position. 
    return true;
}

void DriveDistance::end() {
    drive->driveDistance(0); // Stop the drive
}