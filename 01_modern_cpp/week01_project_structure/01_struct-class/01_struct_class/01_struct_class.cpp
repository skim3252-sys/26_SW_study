#include <iostream>

using namespace std;
struct VehicleState {
	double speed;
	double steeringAngle;
	double acceleration;
	double brake;
};
class Vehicle {
public:
	void showState(void) {
		cout << "Speed: " << state.speed << endl;
		cout << "Steering Angle: " << state.steeringAngle << endl;
		cout << "Acceleration: " << state.acceleration << endl;
		cout << "Brake: " << state.brake << endl;
	}
	const VehicleState& getState(void) const {
		return state;
	}

	void setSpeed(double newSpeed) {
		state.speed = newSpeed;
	}
	void setSteeringAngle(double newSteeringAngle) {
		state.steeringAngle = newSteeringAngle;
	}
	void setAcceleration(double newAcceleration) {
		state.acceleration = newAcceleration;
	}
	void setBrake(double newBrake) {
		state.brake = newBrake;
	}

private:
	VehicleState state;
};

int main(void) {
	Vehicle myCar;
	myCar.setSpeed(60.0);
	myCar.setSteeringAngle(15.0);
	myCar.setAcceleration(3.5);
	myCar.setBrake(0.0);
	VehicleState state = myCar.getState();
	cout << "Vehicle State:" << endl;
	cout << "Speed: " << state.speed << endl;
	cout << "Steering Angle: " << state.steeringAngle << endl;
	cout << "Acceleration: " << state.acceleration << endl;
	cout << "Brake: " << state.brake << endl;
	return 0;

}