#include "odometry_perpendicular_imu.h"

OdometryPerpendicularIMU::OdometryPerpendicularIMU(
    int8_t horizontalEncoderPort, int8_t verticalEncoderPort,
    int8_t imu1Port, int8_t imu2Port)
    : imu1(imu1Port),
      imu2(imu2Port),
      horizontalEncoder(horizontalEncoderPort),
      verticalEncoder(verticalEncoderPort),
      horizontalEncoderLastPos(0),
      verticalEncoderLastPos(0),
      imuLastAngle(0.0) {}
    
void OdometryPerpendicularIMU::reset() {
    std::cout << "Resetting OdometryPerpendicularIMU..." << std::endl;
    Odometry::reset();
    std::cout << "IMU1 Reset" << imu1.reset(true) << std::endl;
    // imu2.reset();
    while (!std::isfinite(imu1.get_rotation())) {
        std::cout << "Waiting for IMU1 to calibrate..." << std::endl;
        std::cout << "IMU1 Rotation: " << imu1.get_rotation() << std::endl;
        pros::delay(10);
    }

    std::cout << "IMU1 calibrated." << std::endl;
    std::cout << "IMU1 Rotation: " << imu1.get_rotation() << std::endl;
    std::cout << "Is finite: " << std::isfinite(imu1.get_rotation()) << std::endl;
    // pros::delay(100000);
    horizontalEncoder.reset_position();
    verticalEncoder.reset_position();
    horizontalEncoderLastPos = 0;
    verticalEncoderLastPos = 0;
    imuLastAngle = 0.0;
}

void OdometryPerpendicularIMU::updatePose() {
    int32_t horizontalEncoderNewPos = horizontalEncoder.get_position();
    int32_t verticalEncoderNewPos = verticalEncoder.get_position();

    // std::cout << "Horizontal Encoder Pos: " << horizontalEncoderNewPos
    //           << " Vertical Encoder Pos: " << verticalEncoderNewPos << std::endl;

    // 36000 = ticks per rev; 6.28318 = 2 * pi
    double dH =
        ((static_cast<double>(horizontalEncoderNewPos) - static_cast<double>(horizontalEncoderLastPos)) / 36000.0) *
        6.28318;
    double dV =
        ((static_cast<double>(verticalEncoderNewPos) - static_cast<double>(verticalEncoderLastPos)) / 36000.0) *
        6.28318;

    // std::cout << "dH: " << dH << " dV: " << dV << std::endl;

    double imu1Angle = imu1.get_rotation();
    double imu2Angle = imu2.get_rotation();
    double imuAvgAngle = imu1Angle; //(imu1Angle + imu2Angle) / 2.0;
    double dThetaDeg = imuAvgAngle - imuLastAngle;
    double dThetaRad = dThetaDeg * (M_PI / 180.0);

    std::cout << "imu1Angle: " << imu1Angle << " imu2Angle: " << imu2Angle
              << " imuAvgAngle: " << imuAvgAngle << std::endl;

    // Convert wheel readings into robot motion
    double d_robot = dV;

    // Rotate into field based on IMU heading
    double thetaRad = imuAvgAngle * (M_PI / 180.0);
    double dx_field = d_robot * cos(thetaRad + dThetaRad / 2.0);
    double dy_field = d_robot * sin(thetaRad + dThetaRad / 2.0);

    std::cout << "thetaRad: " << thetaRad << " d_robot: " << d_robot << std::endl;

    poseMutex.take();
    currentPose->x += dx_field;
    currentPose->y += dy_field;
    currentPose->theta += dThetaRad;
    poseMutex.give();

    std::cout << "dx_field: " << dx_field << " dy_field: " << dy_field
              << " dThetaRad: " << dThetaRad << std::endl;

    std::cout << "currentPose->x: " << currentPose->x << " currentPose->y: " << currentPose->y
              << " currentPose->theta: " << currentPose->theta << std::endl;

    horizontalEncoderLastPos = horizontalEncoderNewPos;
    verticalEncoderLastPos = verticalEncoderNewPos;
    imuLastAngle = imuAvgAngle;
}