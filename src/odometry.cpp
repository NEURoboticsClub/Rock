#include "odometry.h"
#include "pose.h"

Odometry::Odometry() {}

void Odometry::init() {
	pros::Task task([this] { runOdometry(); });
}

void Odometry::reset() {
	poseMutex_.take();
	currentPose_.x = 0.0;
	currentPose_.y = 0.0;
	currentPose_.theta = 0.0;
	poseMutex_.give();
}

void Odometry::getPose(Pose *pose) {
	poseMutex_.take();
	pose->x = currentPose_.x;
	pose->y = currentPose_.y;
	pose->theta = currentPose_.theta;
	poseMutex_.give();
}

void Odometry::setPose(Pose *newPose) {
	poseMutex_.take();
	currentPose_.x = newPose->x;
	currentPose_.y = newPose->y;
	currentPose_.theta = newPose->theta;
	poseMutex_.give();
}

void Odometry::updatePose() {}

void Odometry::runOdometry() {
	while (true) {
		poseMutex_.take();
		this->updatePose();
		poseMutex_.give();
		pros::delay(20);
	}
}