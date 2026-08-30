#ifndef DELIVERYMETHOD_H
#define DELIVERYMETHOD_H

class DeliveryMethod
{
public:
    virtual double calculateFee() const = 0;
    virtual int getDeliveryDays() const = 0;

    virtual ~DeliveryMethod() {}
};

#endif