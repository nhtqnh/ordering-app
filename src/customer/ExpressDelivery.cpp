#include "customer/ExpressDelivery.h"

using namespace std;

ExpressDelivery::ExpressDelivery(double fee, int deliveryDays)
    : fee(fee), deliveryDays(deliveryDays)
{
}

double ExpressDelivery::calculateFee() const
{
    return this->fee;
}

int ExpressDelivery::getDeliveryDays() const
{
    return this->deliveryDays;
}

string ExpressDelivery::getMethodName() const
{
    return "Giao hang hoa toc (Express Delivery)";
}

string ExpressDelivery::getDescription() const
{
    return "Nhan hang trong 24h (1 ngay) - Phi: 50,000 VND";
}