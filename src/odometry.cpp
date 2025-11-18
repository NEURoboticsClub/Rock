#include "odometry.h"

Odometry::Odometry() { currentPose = new Pose(0.0, 0.0, 0.0); }

void Odometry::init() {
	pros::Task task([this] { runOdometry(); });
}

void Odometry::reset() {
	poseMutex.take();
	currentPose->x = 0.0;
	currentPose->y = 0.0;
	currentPose->theta = 0.0;
	poseMutex.give();
}

void Odometry::getPose(Pose *pose) {
	poseMutex.take();
	pose->x = currentPose->x;
	pose->y = currentPose->y;
	pose->theta = currentPose->theta;
	poseMutex.give();
}

void Odometry::setPose(Pose *newPose) {
	poseMutex.take();
	currentPose->x = newPose->x;
	currentPose->y = newPose->y;
	currentPose->theta = newPose->theta;
	poseMutex.give();
}

void Odometry::updatePose() {}

void Odometry::runOdometry() {
	while (true) {
		this->updatePose();
		pros::delay(20);
	}
}