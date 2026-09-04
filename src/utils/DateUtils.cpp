#include "utils/DateUtils.h"
#include <chrono>
#include <iomanip>
#include <sstream>

namespace DateUtils {
    std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d");
        return ss.str();
    }

    std::string getExpectedDeliveryDate(int daysToAdd) {
        auto now = std::chrono::system_clock::now();
        auto delivery_time = now + std::chrono::hours(24 * daysToAdd);
        std::time_t delivery_c = std::chrono::system_clock::to_time_t(delivery_time);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&delivery_c), "%Y-%m-%d");
        return ss.str();
    }
}