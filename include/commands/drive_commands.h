#pragma once
#include "base_commands.h"
#include "tank_drive.h"

class DriveDistance : public Command {
  public:
    /**
     * Constructs a DriveDistance command with specified parameters.
     * 
     * @param drive Reference to the TankDrive object to control the robot's movement.
     * @param odom Reference to the Odometry object to track the robot's position.
     * @param distanceInches The distance in inches the robot should drive forward.
     */
    DriveDistance(TankDrive &drive, Odometry &odom, double distanceInches);

    void initialize() override;
    void execute() override;
    bool isFinished() override;
    void end() override;

  private:
    TankDrive *drive;
    Odometry *odom;
    double distanceInches;
};

// TODO: Add more drive commands