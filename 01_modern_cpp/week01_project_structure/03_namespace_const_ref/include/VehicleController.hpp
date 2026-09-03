#pragma once

#include "Vehicle.hpp"
namespace automotive {
    class VehicleController {
    public:
        explicit VehicleController(Vehicle& vehicle);

        void setTargetSpeed(double targetSpeed);

    private:
        Vehicle& vehicle;
    };
}