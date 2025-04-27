#pragma once
#include <string>

class Transport
{
public:
    virtual ~Transport() = default;

    // READ ONLY OPERATIONS

    // Deliver the goods
    virtual std::string deliver() const = 0;

    // Return maximum capacity of Transport
    virtual int maxLoadCapacity() const = 0;

    // Return transport type
    virtual std::string type() const = 0;

    // Check if transport needs maintenance
    virtual bool needsMaintenance() const = 0;

    // NON CONST OPERATOINS

    // Simulates delivery
    virtual void performDelivery(int loadweight) = 0;

    // Perform maintenance
    virtual void performMaintenance() = 0;
};
