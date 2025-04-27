#pragma once
#include "Transport.h"

class Car : public Transport
{
private:
    int distanceDriven_;
    int maintenanceNeeded_;
    int maxLoadKg_;

public:
    Car();

    std::string deliver() const override;
    int maxLoadCapacity() const override;
    std::string type() const override;
    bool needsMaintenance() const override;

    void performDelivery(int loadweight) override;
    void performMaintenance() override;
};