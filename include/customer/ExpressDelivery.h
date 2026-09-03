#pragma once

#include "customer/DeliveryMethod.h"

class ExpressDelivery : public DeliveryMethod
{
public:
    double calculateFee() const override;
    int getDeliveryDays() const override;
};