#ifndef EXPRESSDELIVERY_H
#define EXPRESSDELIVERY_H

#include "DeliveryMethod.h"

class ExpressDelivery : public DeliveryMethod
{
public:
    double calculateFee() const override
    {
        return 50000;
    }

    int getDeliveryDays() const override
    {
        return 1;
    }
};

#endif