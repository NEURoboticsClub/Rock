#include "odometry_perpendicular_imu.h"

OdometryPerpendicularIMU::OdometryPerpendicularIMU(
    pros::Rotation *xEncoder, pros::Rotation *yEncoder,
    pros::IMU *imu1, pros::IMU *imu2)
    : imu1_(imu1),
      imu2_(imu2),
      xEncoder_(xEncoder),
      yEncoder_(yEncoder),
      xEncoderLastPos_(0),
      yEncoderLastPos_(0),
      imuLastAngle_(0.0) {}
    
void OdometryPerpendicularIMU::reset() {
    Odometry::reset();
    xEncoderLastPos_ = 0;
    yEncoderLastPos_ = 0;
    imuLastAngle_ = 0.0;
}

void OdometryPerpendicularIMU::updatePose() {
    int32_t xEncoderNewPos = xEncoder_->get_position();
    int32_t yEncoderNewPos = yEncoder_->get_position();

    // 36000 = ticks per rev
    double circumference = M_PI * 2; // Wheel diameter is 2~ inches
    double dH =
        ((static_cast<double>(xEncoderNewPos) - static_cast<double>(xEncoderLastPos_)) / 36000.0) * circumference;
    double dV =
        ((static_cast<double>(yEncoderNewPos) - static_cast<double>(yEncoderLastPos_)) / 36000.0) * circumference;

    double imu1Angle = 360 - imu1_->get_rotation();
    double imu2Angle = imu1Angle; //360 - imu2_->get_rotation();
    double imuAvgAngle = std::fmod((imu1Angle + imu2Angle) / 2.0, 360.0);

    if (std::isfinite(imuAvgAngle) == false) {
        printf("IMU reading invalid, skipping pose update\n");
        // imuAvgAngle = 0;
        return;
    }

    double dThetaDeg = imuAvgAngle - imuLastAngle_;
    double dThetaRad = dThetaDeg * (M_PI / 180.0);

    // Rotate into field based on IMU heading
    double thetaRad = imuAvgAngle * (M_PI / 180.0);
    double dx_field = dV * cos(thetaRad + dThetaRad / 2.0) + dH * sin(thetaRad + dThetaRad / 2.0);
    double dy_field = dV * sin(thetaRad + dThetaRad / 2.0) - dH * cos(thetaRad + dThetaRad / 2.0);

    currentPose_.x += dx_field;
    currentPose_.y += dy_field;
    currentPose_.theta += dThetaRad;

    printf("x: %f, y: %f, theta: %f, imu1: %f, imu2: %f\n", currentPose_.x, currentPose_.y,
            currentPose_.theta * (180.0 / M_PI), imu1Angle, imu2Angle);

    xEncoderLastPos_ = xEncoderNewPos;
    yEncoderLastPos_ = yEncoderNewPos;
    imuLastAngle_ = imuAvgAngle;
}