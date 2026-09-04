#include "utils/InputUtils.h"
#include <iostream>
#include <limits>

namespace InputUtils {
    int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Du lieu khong hop le. Vui long nhap so nguyen.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    int readInt(const std::string& prompt, int min, int max) {
        while (true) {
            int value = readInt(prompt);
            if (value >= min && value <= max) return value;
            std::cout << "Gia tri phai nam trong khoang " << min << " - " << max << ".\n";
        }
    }

    double readDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (value >= 0) return value;
            }
            std::cout << "Vui long nhap so hop le.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string readString(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    std::string readNonEmptyString(const std::string& prompt) {
        while (true) {
            std::string value = readString(prompt);
            if (!value.empty()) return value;
            std::cout << "Khong duoc de trong. Vui long nhap lai.\n";
        }
    }

    bool confirm(const std::string& prompt) {
        while (true) {
            std::string answer = readString(prompt + " (Y/N): ");
            if (answer == "Y" || answer == "y") return true;
            if (answer == "N" || answer == "n") return false;
            std::cout << "Vui long chon Y hoac N.\n";
        }
    }
}