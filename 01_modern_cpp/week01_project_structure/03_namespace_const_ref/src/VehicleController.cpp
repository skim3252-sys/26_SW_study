#include "VehicleController.hpp"
namespace automotive {
    VehicleController::VehicleController(Vehicle& vehicle)
        : vehicle(vehicle)
    {
    }

    void VehicleController::setTargetSpeed(double targetSpeed)
    {
        vehicle.setSpeed(targetSpeed);
    }
}