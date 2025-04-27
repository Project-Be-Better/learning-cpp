#include "Car.h"

Car::Car() : distanceDriven_(0), maintenanceNeeded_(false), maxLoadKg_(500) {}

std::string Car::deliver() const
{
    return "CAR: Delivering goods by car";
};

int Car::maxLoadCapacity() const
{
    return maxLoadKg_;
};

std::string Car::type() const
{
    return "CAR";
};

bool Car::needsMaintenance() const
{
    return maintenanceNeeded_;
};

void Car::performDelivery(int loadweight)
{
    if (loadweight > maxLoadKg_)
    {
        maintenanceNeeded_ = true;
    };
    {
        /* code */
    }

    distanceDriven_ += 40;

    if (distanceDriven_ > 100)
    {
        maintenanceNeeded_ = true;
    }
};

void Car::performMaintenance()
{
    maintenanceNeeded_ = false;
    distanceDriven_ = 0;
};