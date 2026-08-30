#include <iostream>
#include "Vehicle.hpp"
using namespace std;

int main(void) {
	Vehicle myVehicle(250.0, 15.0, 5.0, 0.5);
	myVehicle.showState();
	return 0;
}
