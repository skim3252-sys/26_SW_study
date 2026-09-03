#include <iostream>
#include "Vehicle.hpp"
#include "VehicleController.hpp"
using namespace std;

int main(void) {
	automotive::Vehicle myVehicle(150.0 , 15.0, 5.0, 0.5);
	automotive::VehicleController myController(myVehicle);
	myController.setTargetSpeed(200.0);
	myVehicle.showState();
	return 0;
}
