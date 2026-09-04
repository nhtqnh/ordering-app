#pragma once
#include "customer/DeliveryMethod.h"

// Ke thua tu DeliveryMethod (Chuong 4 & Chuong 5)
class StandardDelivery : public DeliveryMethod
{
private:
    double fee;
    int deliveryDays;

public:
    StandardDelivery(double fee = 30000.0, int deliveryDays = 3);
    virtual ~StandardDelivery() override = default;

    double calculateFee() const override;
    int getDeliveryDays() const override;
    std::string getMethodName() const override;
    std::string getDescription() const override;
};