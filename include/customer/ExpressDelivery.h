#pragma once
#include "customer/DeliveryMethod.h"

class ExpressDelivery : public DeliveryMethod
{
private:
    double fee;
    int deliveryDays;

public:
    ExpressDelivery(double fee = 50000.0, int deliveryDays = 1);
    virtual ~ExpressDelivery() override = default;

    double calculateFee() const override;
    int getDeliveryDays() const override;
    std::string getMethodName() const override;
    std::string getDescription() const override;
};