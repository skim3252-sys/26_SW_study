#pragma once

#include "Vehicle.hpp"

class VehicleController {
public:
    explicit VehicleController(Vehicle& vehicle);

    void setTargetSpeed(double targetSpeed);

private:
    Vehicle& vehicle;
};