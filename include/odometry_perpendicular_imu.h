#pragma once
#include "odometry.h"

class OdometryPerpendicularIMU : public Odometry {
  public:
    OdometryPerpendicularIMU(int8_t horizontalEncoderPort, int8_t verticalEncoderPort,
                             int8_t imu1Port, int8_t imu2Port);
    void reset() override;

  protected:
    void updatePose() override;

  private:
    // Rotation sensors
    pros::Rotation horizontalEncoder;
    pros::Rotation verticalEncoder;
    pros::Imu imu1;
    pros::Imu imu2;

    // Internal tracking of past sensor values for delta calculation
    uint32_t horizontalEncoderLastPos;
    uint32_t verticalEncoderLastPos;
    double imuLastAngle;
};