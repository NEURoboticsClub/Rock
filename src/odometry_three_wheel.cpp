#include "odometry_three_wheel.h"

#include "utils.h"

OdometryThreeWheel::OdometryThreeWheel(int8_t leftEncoderPort,
									   int8_t rightEncoderPort,
									   int8_t centerEncoderPort, double sL,
									   double sR, double sS)
	: Odometry(),
	  sL(sL),
	  sR(sR),
	  sS(sS),
	  leftEncoder(leftEncoderPort),
	  rightEncoder(rightEncoderPort),
	  centerEncoder(centerEncoderPort) {
	leftEncoder.reset_position();
	rightEncoder.reset_position();
	centerEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
	centerEncoderLastPos = 0;
}

void OdometryThreeWheel::reset() {
	Odometry::reset();

	leftEncoder.reset_position();
	rightEncoder.reset_position();
	centerEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
	centerEncoderLastPos = 0;
}

void OdometryThreeWheel::updatePose() {
	uint32_t leftEncoderNewPos = leftEncoder.get_position();
	uint32_t rightEncoderNewPos = rightEncoder.get_position();
	uint32_t centerEncoderNewPos = centerEncoder.get_position();
	double dL =
		((static_cast<double>(leftEncoderNewPos) - static_cast<double>(leftEncoderLastPos)) / 36000.0) *
		6.28318;
	double dR =
		((static_cast<double>(rightEncoderNewPos) - static_cast<double>(rightEncoderLastPos)) / 36000.0) *
		6.28318;
	double dC = ((static_cast<double>(centerEncoderNewPos) - static_cast<double>(centerEncoderLastPos)) /
				 36000.0) *
				6.28318;
	double deltaThetaRad = (dL - dR) / (sL + sR);

	double localOffsetX;
	double localOffsetY;

	if (doubleEquals(deltaThetaRad, 0.0, 0.01)) {
		localOffsetX = dC;
		localOffsetY = dR;
	} else {
		localOffsetX =
			(2.0 * sin(deltaThetaRad / 2.0) * (dC / deltaThetaRad) + sS);
		localOffsetY = (dR / deltaThetaRad) + sR;
	}

	double thetaM = currentPose_.theta + (deltaThetaRad / 2.0);

	double dX = (localOffsetX * cos(thetaM)) - (localOffsetY * sin(thetaM));
	double dY = (localOffsetX * sin(thetaM)) + (localOffsetY * cos(thetaM));

	double x = currentPose_.x + dX;
	double y = currentPose_.y + dY;
	double theta = currentPose_.theta + deltaThetaRad;

	currentPose_.x = x;
	currentPose_.y = y;
	currentPose_.theta = theta;

	leftEncoderLastPos = leftEncoderNewPos;
	rightEncoderLastPos = rightEncoderNewPos;
	centerEncoderLastPos = centerEncoderNewPos;
}