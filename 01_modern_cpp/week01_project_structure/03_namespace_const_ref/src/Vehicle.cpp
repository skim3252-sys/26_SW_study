#include <iostream>
#include "Vehicle.hpp"
using namespace std;

namespace automotive {
	VehicleState::VehicleState(double speed,
		double steeringAngle,
		double acceleration,
		double brake)
		: speed(speed),
		steeringAngle(steeringAngle),
		acceleration(acceleration),
		brake(brake) {
	}


	Vehicle::Vehicle(double speed,
		double steeringAngle,
		double acceleration,
		double brake)
		: state{ validateSpeed(speed), validateSteeringAngle(steeringAngle),
		acceleration, validateBrake(brake) } {
	}
	const VehicleState& Vehicle::getState(void) const {
		return state;
	}
	void Vehicle::setSpeed(double newSpeed) {
		state.speed = validateSpeed(newSpeed);
	}
	void Vehicle::setSteeringAngle(double newSteeringAngle) {
		state.steeringAngle = validateSteeringAngle(newSteeringAngle);
	}
	void Vehicle::setBrake(double newBrake) {
		state.brake = validateBrake(newBrake);
	}
	void Vehicle::setAcceleration(double newAcceleration) {
		state.acceleration = newAcceleration;
	}
	void Vehicle::showState(void) const {
		cout << "Speed: " << state.speed << endl;
		cout << "Steering Angle: " << state.steeringAngle << endl;
		cout << "Acceleration: " << state.acceleration << endl;
		cout << "Brake: " << state.brake << endl;
	}

	double Vehicle::validateSpeed(double speed) {
		if (speed < 0.0) {
			return 0.0;
		}
		else if (speed > 200.0) {
			return 200.0;
		}
		return speed;
	}
	double Vehicle::validateSteeringAngle(double steeringAngle) {
		if (steeringAngle < -30.0) {
			return -30.0;
		}
		else if (steeringAngle > 30.0) {
			return 30.0;
		}
		return steeringAngle;
	}
	double Vehicle::validateBrake(double brake) {
		if (brake < 0.0) {
			return 0.0;
		}
		else if (brake > 1.0) {
			return 1.0;
		}
		return brake;
	}
}