#include <iostream>
#include "Vehicle.hpp"
#include "VehicleController.hpp"
using namespace std;

int main(void) {
	automotive::Vehicle myVehicle(150.0 , 15.0, 5.0, 0.5);
	automotive::VehicleController myController(myVehicle);
	myController.setTargetSpeed(200.0);
	myVehicle.showState();
	
	automotive::Speed test(100);
	// automotive::speed test2 = 100.0; <- explicit 임으로 
	//자동 static_cast<speed>(100.0); 실행 X error 발생
	// 암시적 변환 허용 X 
	test.showSpeed(); cout << endl;


	//automotive::PrintSpeed(100.0); <- explicit Speed(double value);
	// error
	automotive::PrintSpeed(test);
	return 0;
}
