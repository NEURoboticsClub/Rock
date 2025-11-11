#pragma once
#include "odometry.h"

class OdometryPerpendicularIMU : public Odometry {
  public:
    OdometryPerpendicularIMU(int8_t leftEncoderPort, int8_t rightEncoderPort,
                             int8_t imu1Port, int8_t imu2Port);
    void reset() override;

  protected:
    void updatePose() override;

  private:
    // Rotation sensors
    pros::Rotation leftEncoder;
    pros::Rotation rightEncoder;
    pros::Imu imu1;
    pros::Imu imu2;

    // Internal tracking of past sensor values for delta calculation
    uint32_t leftEncoderLastPos;
    uint32_t rightEncoderLastPos;
    double imuLastAngle;
};