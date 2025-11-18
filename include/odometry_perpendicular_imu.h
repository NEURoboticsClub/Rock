#pragma once
#include "odometry.h"

class OdometryPerpendicularIMU : public Odometry {
  public:
    OdometryPerpendicularIMU(pros::Rotation *xEncoder = NULL, pros::Rotation *yEncoder = NULL,
                             pros::IMU *imu1Port = NULL, pros::IMU *imu2 = NULL);
    void reset() override;

  protected:
    void updatePose() override;

  private:
    // Rotation sensors
    pros::Rotation *xEncoder_;
    pros::Rotation *yEncoder_;
    pros::Imu *imu1_;
    pros::Imu *imu2_;

    // Internal tracking of past sensor values for delta calculation
    uint32_t horizontalEncoderLastPos_;
    uint32_t verticalEncoderLastPos_;
    double imuLastAngle_;
};