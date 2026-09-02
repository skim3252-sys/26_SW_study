#include "VehicleController.hpp"

VehicleController::VehicleController(Vehicle& vehicle)
    : vehicle(vehicle)
{
}

void VehicleController::setTargetSpeed(double targetSpeed)
{
    vehicle.setSpeed(targetSpeed);
}