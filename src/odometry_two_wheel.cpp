#include "odometry_two_wheel.h"

TwoWheelOdometry::TwoWheelOdometry(int8_t leftEncoderPort,
								   int8_t rightEncoderPort, double dW)
	: Odometry(),
	  dW(dW),
	  leftEncoder(leftEncoderPort),
	  rightEncoder(rightEncoderPort) {
	leftEncoder.reset_position();
	rightEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
}

void TwoWheelOdometry::reset() {
	Odometry::reset();

	leftEncoder.reset_position();
	rightEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
}

void TwoWheelOdometry::updatePose() {
	// math based off of:
	// https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
	int32_t leftEncoderNewPos = leftEncoder.get_position();
	int32_t rightEncoderNewPos = rightEncoder.get_position();
	double dL =
		((static_cast<double>(leftEncoderNewPos) - static_cast<double>(leftEncoderLastPos)) / 36000.0) *
		6.28318;
	double dR =
		((static_cast<double>(rightEncoderNewPos) - static_cast<double>(rightEncoderLastPos)) / 36000.0) *
		6.28318;
	double d = (dL + dR) / 2.0;
	double deltaThetaRad = (dR - dL) / (2.0 * dW);

	double x = currentPose_.x +
			   (d * static_cast<double>(cos(currentPose_.theta + (deltaThetaRad / 2.0))));
	double y = currentPose_.y +
			   (d * static_cast<double>(sin(currentPose_.theta + (deltaThetaRad / 2.0))));
	double theta = currentPose_.theta + deltaThetaRad;

	currentPose_.x = x;
	currentPose_.y = y;
	currentPose_.theta = theta;

	leftEncoderLastPos = leftEncoderNewPos;
	rightEncoderLastPos = rightEncoderNewPos;
}