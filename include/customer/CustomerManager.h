#pragma once

#include <vector>
#include <memory>
#include <string>

#include "customer/Customer.h"

class CustomerManager
{
private:
    std::vector<std::shared_ptr<Customer>> customers;

    static int tierRank(const std::string& tier);

    // Ngày hiện tại YYYY-MM-DD
    static std::string getCurrentDate();

    // Tính số tháng giữa 2 ngày YYYY-MM-DD
    static int monthsBetween(const std::string& startDate,
                             const std::string& currentDate);

    // Tạo ngày mới sau 3 tháng
    static std::string addThreeMonths(const std::string& date);

    // Xử lý trạng thái VIP khi hết chu kỳ
    void refreshMembership(std::shared_ptr<Customer>& customer);

    // Nâng hạng nếu đạt target trong chu kỳ
    void upgradeIfEligible(std::shared_ptr<Customer>& customer);

    // Khi Regular vừa trở thành VIP
    void startMembershipCycle(std::shared_ptr<Customer>& customer,
                              const std::string& tier);

public:
    CustomerManager();

    bool loadFromFile(const std::string& filePath);
    bool saveToFile(const std::string& filePath) const;

    std::shared_ptr<Customer> findByPhone(
        const std::string& phone) const;

    bool addCustomer(
        const std::shared_ptr<Customer>& customer);

    int getTotalCustomers() const;

    const std::vector<std::shared_ptr<Customer>>&
    getAllCustomers() const;

    static bool isValidPhone(const std::string& phone);

    std::string recordPurchase(
        std::shared_ptr<Customer>& customer,
        double amountSpent,
        const std::string& saveFilePath);
};