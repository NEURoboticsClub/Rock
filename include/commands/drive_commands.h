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

class DriveDistance : public TimeoutCommand {
  public:
    /**
     * Constructs a DriveDistance command with specified parameters.
     * 
     * @param drive Reference to the TankDrive object to control the robot's movement.
     * @param odom Reference to the Odometry object to track the robot's position.
     * @param targetDistance The distance to drive in inches.
     * @param timeoutMs The duration in milliseconds after which the command should time out.
     */
    DriveDistance(TankDrive &drive, Odometry &odom, double targetDistance, uint32_t timeoutMs = 2000);

    void initialize() override;
    void execute() override;
    bool isFinished() override;
    void end() override;

  private:
    TankDrive *drive_;
    Odometry *odom_;
    double targetDistance_;
    double targetX_;
    double targetY_;
};

class TurnToHeading : public TimeoutCommand {
  public:
    /**
     * Constructs a TurnToHeading command with specified parameters.
     * 
     * @param drive Reference to the TankDrive object to control the robot's movement.
     * @param odom Reference to the Odometry object to track the robot's position.
     * @param targetHeading The target heading in degrees.
     * @param timeoutMs The duration in milliseconds after which the command should time out.
     */
    TurnToHeading(TankDrive &drive, Odometry &odom, double targetHeading, uint32_t timeoutMs = 2000);

    void execute() override;
    bool isFinished() override;
    void end() override;

  private:
    TankDrive *drive_;
    Odometry *odom_;
    double targetHeading_;
};