#include "VehicleController.hpp"
#include <iostream>
namespace automotive {
	VehicleController::VehicleController(Vehicle& vehicle)
		: vehicle(vehicle)
	{
	}

	void VehicleController::setTargetSpeed(double targetSpeed)
	{
		vehicle.setSpeed(targetSpeed);
	}

	Speed::Speed(double value) : value(value)
	{ std::cout << "Normal constructor\n"; }

	Speed::Speed(const Speed& other) : value(other.value) {
		std::cout << "Copy constructor\n";
	}

	Speed& Speed::operator=(const Speed& other) noexcept {
		value = other.value;
		std::cout << "Copy assignment\n";
		return *this;
	}

	Speed::Speed( Speed&& other) : value(other.value) {
		std::cout << "Move constructor\n";
		other.value = 0.0;
	}
	Speed& Speed::operator=( Speed&& other) noexcept {
		value = other.value;
		std::cout << "Move assignment\n";
		other.value = 0.0;
		return *this;
	}

	void Speed::showSpeed() { printf("%f", value); }

	void PrintSpeed(Speed speed) { speed.showSpeed(); }
}