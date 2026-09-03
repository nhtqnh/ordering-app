#include "customer/StandardDelivery.h"

double StandardDelivery::calculateFee() const
{
    return 30000;
}

int StandardDelivery::getDeliveryDays() const
{
    return 3;
}