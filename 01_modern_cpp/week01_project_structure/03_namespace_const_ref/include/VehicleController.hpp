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

    class Speed {
    public:
        explicit Speed(double value);
        
        Speed(const Speed& other);
        Speed& operator=(const Speed& other) noexcept;

        Speed( Speed&& other);
        Speed& operator=( Speed&& other) noexcept;


        void showSpeed();
    private:
        double value;
    };
    void PrintSpeed(Speed speed);
}