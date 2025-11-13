#pragma once
#include "base_commands.h"
#include "tank_drive.h"

class DriveDeadReckon : public Command {
  public:
    /**
     * Constructs a DriveDeadReckon command with specified parameters.
     * 
     * @param drive Reference to the TankDrive object to control the robot's movement.
     * @param leftSpeed The speed for the left motors.
     * @param rightSpeed The speed for the right motors.
     * @param durationMs The duration in milliseconds to drive at the specified speeds.
     */
    DriveDeadReckon(TankDrive &drive, int leftSpeed, int rightSpeed, int durationMs);

    void initialize() override;
    bool isFinished() override;
    void end() override;

  private:
    TankDrive *drive;
    Odometry *odom;
    int leftSpeed;
    int rightSpeed;
    int durationMs;
    std::uint32_t startTime;
};

// TODO: Add more drive commands