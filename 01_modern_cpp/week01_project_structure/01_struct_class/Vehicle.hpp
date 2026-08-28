#pragma once

struct VehicleState {
	double speed = 0.0;
	double steeringAngle = 0.0;
	double acceleration = 0.0;
	double brake = 0.0;

	VehicleState(double speed = 0.0,
		double steeringAngle = 0.0,
		double acceleration = 0.0,
		double brake = 0.0);
};

class Vehicle {
public:
	Vehicle(double speed = 0.0,
		double steeringAngle = 0.0,
		double acceleration = 0.0,
		double brake = 0.0);
	const VehicleState& getState(void) const;
	void showState(void) const;
	void setSpeed(double newSpeed);
	void setSteeringAngle(double newSteeringAngle);
	void setBrake(double newBrake);
	void setAcceleration(double newAcceleration);
	

private: 
	VehicleState state;
	static double validateSpeed(double speed);
	static double validateSteeringAngle(double steeringAngle);
	static double validateBrake(double brake);
};