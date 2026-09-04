#pragma once
#include <string>

// Lop truu tuong (Abstract Base Class - Chuong 5)
class DeliveryMethod
{
public:
    virtual ~DeliveryMethod() = default;

    // Cac phuong thuc thuan ao (Pure Virtual Functions)
    virtual double calculateFee() const = 0;
    virtual int getDeliveryDays() const = 0;
    virtual std::string getMethodName() const = 0;
    virtual std::string getDescription() const = 0;
};