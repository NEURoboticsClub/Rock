#include "odometry_perpendicular_imu.h"

OdometryPerpendicularIMU::OdometryPerpendicularIMU(
    int8_t leftEncoderPort, int8_t rightEncoderPort,
    int8_t imu1Port, int8_t imu2Port)
    : imu1(imu1Port),
      imu2(imu2Port),
      leftEncoder(leftEncoderPort),
      rightEncoder(rightEncoderPort),
      leftEncoderLastPos(0),
      rightEncoderLastPos(0),
      imuLastAngle(0.0) {}
    
void OdometryPerpendicularIMU::reset() {
    Odometry::reset();
    imu1.reset();
    imu2.reset();
    while (imu1.is_calibrating() || imu2.is_calibrating()) pros::delay(10);
    leftEncoder.reset_position();
    rightEncoder.reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
    imuLastAngle = 0.0;
}

void OdometryPerpendicularIMU::updatePose() {
    int32_t leftEncoderNewPos = leftEncoder.get_position();
    int32_t rightEncoderNewPos = rightEncoder.get_position();

    // 36000 = ticks per rev; 6.28318 = 2 * pi
    double dL =
        ((static_cast<double>(leftEncoderNewPos) - static_cast<double>(leftEncoderLastPos)) / 36000.0) *
        6.28318;
    double dR =
        ((static_cast<double>(rightEncoderNewPos) - static_cast<double>(rightEncoderLastPos)) / 36000.0) *
        6.28318;

    double imu1Angle = imu1.get_rotation();
    double imu2Angle = imu2.get_rotation();
    double imuAvgAngle = (imu1Angle + imu2Angle) / 2.0;
    double dThetaDeg = imuAvgAngle - imuLastAngle;
    double dThetaRad = dThetaDeg * (M_PI / 180.0);

    // Convert wheel readings into robot motion
    double d_robot = (dL + dR) / 2.0;

    // Rotate into field based on IMU heading
    double thetaRad = imuAvgAngle * (M_PI / 180.0);
    double dx_field = d_robot * cos(thetaRad + dThetaRad / 2.0);
    double dy_field = d_robot * sin(thetaRad + dThetaRad / 2.0);

    currentPose->x += dx_field;
    currentPose->y += dy_field;
    currentPose->theta += dThetaRad;

    leftEncoderLastPos = leftEncoderNewPos;
    rightEncoderLastPos = rightEncoderNewPos;
    imuLastAngle = imuAvgAngle;
}