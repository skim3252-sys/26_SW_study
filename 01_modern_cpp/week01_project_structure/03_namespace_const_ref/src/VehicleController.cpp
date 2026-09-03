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

    Speed::Speed(double value) : value(value) {}
    void Speed::showSpeed() { printf("%f", value); }

    void PrintSpeed(Speed speed) { speed.showSpeed(); }
}