#include "customer/StandardDelivery.h"

using namespace std;

StandardDelivery::StandardDelivery(double fee, int deliveryDays)
    : fee(fee), deliveryDays(deliveryDays)
{
}

double StandardDelivery::calculateFee() const
{
    return this->fee;
}

int StandardDelivery::getDeliveryDays() const
{
    return this->deliveryDays;
}

string StandardDelivery::getMethodName() const
{
    return "Giao hang tieu chuan (Standard Delivery)";
}

string StandardDelivery::getDescription() const
{
    return "Nhan hang sau 3 ngay - Phi: 30,000 VND";
}