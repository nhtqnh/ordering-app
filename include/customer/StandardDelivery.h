#ifndef STANDARDDELIVERY_H
#define STANDARDDELIVERY_H

#include "DeliveryMethod.h"

class StandardDelivery : public DeliveryMethod
{
public:
    double calculateFee() const override
    {
        return 30000;
    }

    int getDeliveryDays() const override
    {
        return 3;
    }
};

#endif