#pragma once
#include <string>

namespace InputUtils {
    int readInt(const std::string& prompt);
    int readInt(const std::string& prompt, int min, int max);
    double readDouble(const std::string& prompt);
    std::string readString(const std::string& prompt);
    std::string readNonEmptyString(const std::string& prompt);
    bool confirm(const std::string& prompt);
}