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
    std::cout << "Resetting OdometryPerpendicularIMU..." << std::endl;
    Odometry::reset();
    xEncoderLastPos_ = 0;
    yEncoderLastPos_ = 0;
    imuLastAngle_ = 0.0;
}

void OdometryPerpendicularIMU::updatePose() {
    int32_t xEncoderNewPos = xEncoder_->get_position();
    int32_t yEncoderNewPos = yEncoder_->get_position();

    std::cout << "Horizontal Encoder Pos: " << xEncoderNewPos
              << " Vertical Encoder Pos: " << yEncoderNewPos << std::endl;

    // 36000 = ticks per rev; 6.28318 = 2 * pi
    double dH =
        ((static_cast<double>(xEncoderNewPos) - static_cast<double>(xEncoderLastPos_)) / 36000.0) *
        6.28318;
    double dV =
        ((static_cast<double>(yEncoderNewPos) - static_cast<double>(yEncoderLastPos_)) / 36000.0) *
        6.28318;

    double imu1Angle = imu1_->get_rotation();
    double imu2Angle = imu2_->get_rotation();
    double imuAvgAngle = (imu1Angle + imu2Angle) / 2.0;
    double dThetaDeg = imuAvgAngle - imuLastAngle_;
    double dThetaRad = dThetaDeg * (M_PI / 180.0);

    // Convert wheel readings into robot motion
    double d_robot = dV;

    // Rotate into field based on IMU heading
    double thetaRad = imuAvgAngle * (M_PI / 180.0);
    double dx_field = d_robot * cos(thetaRad + dThetaRad / 2.0);
    double dy_field = d_robot * sin(thetaRad + dThetaRad / 2.0);

    currentPose_.x += dx_field;
    currentPose_.y += dy_field;
    currentPose_.theta += dThetaRad;

    xEncoderLastPos_ = xEncoderNewPos;
    yEncoderLastPos_ = yEncoderNewPos;
    imuLastAngle_ = imuAvgAngle;
}