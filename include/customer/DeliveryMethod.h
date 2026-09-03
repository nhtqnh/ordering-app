#pragma once

class DeliveryMethod
{
public:
    virtual double calculateFee() const = 0;
    virtual int getDeliveryDays() const = 0;

    virtual ~DeliveryMethod();
};