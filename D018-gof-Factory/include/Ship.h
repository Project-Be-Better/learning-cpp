#pragma once
#include "Transport.h"

class Ship : public Transport
{
private:
    int tripsDone_;
    bool maintenanceNeeded_;
    int cargoCapacityKg_;

public:
    Ship();

    std::string deliver() const override;
    int maxLoadCapacity() const override;
    std::string type() const override;
    bool needsMaintenance() const override;

    void performDelivery(int loadweight) override;
    void performMaintenance() override;
};