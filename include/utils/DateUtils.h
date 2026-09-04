#pragma once
#include <string>

namespace DateUtils {
    std::string getCurrentDate();

    std::string getExpectedDeliveryDate(int daysToAdd);
}