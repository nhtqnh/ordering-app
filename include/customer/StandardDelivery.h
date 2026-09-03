#pragma once

#include "customer/DeliveryMethod.h"

class StandardDelivery : public DeliveryMethod
{
public:
    double calculateFee() const override;
    int getDeliveryDays() const override;
};