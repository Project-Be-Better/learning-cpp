#include "Ship.h"

Ship::Ship() : tripsDone_(0), maintenanceNeeded_(false), cargoCapacityKg_(20000000) {}

std::string Ship::deliver() const
{
    return "Ship: Delivering goods by Ship";
};

int Ship::maxLoadCapacity() const
{
    return cargoCapacityKg_;
};

std::string Ship::type() const
{
    return "SHIP";
};

bool Ship::needsMaintenance() const
{
    return maintenanceNeeded_;
};

void Ship::performDelivery(int loadweight)
{
    ++tripsDone_;

    if (loadweight > cargoCapacityKg_)
    {
        maintenanceNeeded_ = true;
    };

    if (tripsDone_ > 5)
    {
        maintenanceNeeded_ = true;
    }
};

void Ship::performMaintenance()
{
    maintenanceNeeded_ = false;
    tripsDone_ = 0;
};