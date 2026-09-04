#include "customer/CustomerManager.h"
#include "customer/VIPCustomer.h"
#include "customer/Membership.h"

#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
#include <ctime>
#include <iomanip>

namespace
{
    std::vector<std::string> splitCustomerLine(
        const std::string& line,
        char delimiter)
    {
        std::vector<std::string> tokens;

        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, delimiter))
        {
            tokens.push_back(token);
        }

        return tokens;
    }
}

CustomerManager::CustomerManager()
{

}
bool CustomerManager::isValidPhone(const std::string& phone)
{
    if (phone.size() < 9 || phone.size() > 11)
    {
        return false;
    }

    for (char c : phone)
    {
        if (!std::isdigit(
                static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    return true;
}

int CustomerManager::tierRank(const std::string& tier)
{
    if (tier == "Kim Cương")
        return 3;

    if (tier == "Vàng")
        return 2;

    if (tier == "Bạc")
        return 1;

    return 0;
}

std::string CustomerManager::getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    if (!localTime)
    {
        return "";
    }

    std::ostringstream oss;

    oss << std::put_time(
        localTime,
        "%Y-%m-%d"
    );

    return oss.str();
}

int CustomerManager::monthsBetween(
    const std::string& startDate,
    const std::string& currentDate)
{
    if (startDate.empty() ||
        currentDate.empty())
    {
        return 0;
    }

    try
    {
        int startYear =
            std::stoi(startDate.substr(0, 4));

        int startMonth =
            std::stoi(startDate.substr(5, 2));

        int currentYear =
            std::stoi(currentDate.substr(0, 4));

        int currentMonth =
            std::stoi(currentDate.substr(5, 2));

        return
            (currentYear - startYear) * 12
            + (currentMonth - startMonth);
    }
    catch (...)
    {
        return 0;
    }
}

std::string CustomerManager::addThreeMonths(
    const std::string& date)
{
    if (date.empty())
    {
        return "";
    }

    try
    {
        int year =
            std::stoi(date.substr(0, 4));

        int month =
            std::stoi(date.substr(5, 2));

        int day =
            std::stoi(date.substr(8, 2));

        month += 3;

        if (month > 12)
        {
            month -= 12;
            year++;
        }

        std::ostringstream oss;

        oss << std::setfill('0')
            << std::setw(4) << year
            << "-"
            << std::setw(2) << month
            << "-"
            << std::setw(2) << day;

        return oss.str();
    }
    catch (...)
    {
        return "";
    }
}

bool CustomerManager::loadFromFile(
    const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return false;
    }

    customers.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::vector<std::string> tokens =
            splitCustomerLine(line, ';');

        if (tokens.size() < 10)
        {
            continue;
        }

        const std::string& name = tokens[0];
        const std::string& phone = tokens[1];
        const std::string& address = tokens[2];
        const std::string& type = tokens[3];
        const std::string& tier = tokens[4];

        double totalSpent = 0.0;
        int purchaseCount = 0;
        double quarterSpent = 0.0;
        std::string membershipStartDate =
            tokens[9];

        try
        {
            totalSpent = std::stod(tokens[6]);
            purchaseCount = std::stoi(tokens[7]);
            quarterSpent = std::stod(tokens[8]);
        }
        catch (...)
        {
            continue;
        }

        if (phone.empty() ||
            findByPhone(phone) != nullptr)
        {
            continue;
        }

        std::shared_ptr<Customer> customer;

        if (type == "VIP")
        {
            std::string safeTier =
                tier.empty() ? "Silver" : tier;

            customer =
                std::make_shared<VIPCustomer>(
                    name,
                    phone,
                    address,
                    safeTier
                );
        }
        else
        {
            customer =
                std::make_shared<Customer>(
                    name,
                    phone,
                    address
                );
        }

        customer->setTotalSpent(totalSpent);
        customer->setPurchaseCount(purchaseCount);
        customer->setQuarterSpent(quarterSpent);
        customer->setMembershipStartDate(
            membershipStartDate
        );

        customers.push_back(customer);
    }

    for (auto& customer : customers)
    {
        refreshMembership(customer);
    }

    return true;
}

bool CustomerManager::saveToFile(
    const std::string& filePath) const
{
    std::ofstream file(
        filePath,
        std::ios::trunc
    );

    if (!file.is_open())
    {
        std::cerr
            << "Loi: Khong the ghi file "
            << filePath
            << std::endl;

        return false;
    }

    for (const auto& c : customers)
    {
        auto vip =
            std::dynamic_pointer_cast<VIPCustomer>(c);

        std::string type =
            vip ? "VIP" : "REGULAR";

        std::string tier =
            vip
            ? vip->getMembershipTier()
            : "-";

        file << c->getName() << ";"
             << c->getPhone() << ";"
             << c->getAddress() << ";"
             << type << ";"
             << tier << ";"
             << c->getTotalSpent() << ";"
             << c->getPurchaseCount() << ";"
             << c->getQuarterSpent() << ";"
             << c->getMembershipStartDate()
             << "\n";
    }

    return true;
}

std::shared_ptr<Customer>
CustomerManager::findByPhone(
    const std::string& phone) const
{
    for (const auto& c : customers)
    {
        if (c->getPhone() == phone)
        {
            return c;
        }
    }

    return nullptr;
}

bool CustomerManager::addCustomer(
    const std::shared_ptr<Customer>& customer)
{
    if (!customer)
    {
        return false;
    }

    if (findByPhone(
            customer->getPhone()) != nullptr)
    {
        return false;
    }

    customers.push_back(customer);

    return true;
}

int CustomerManager::getTotalCustomers() const
{
    return static_cast<int>(
        customers.size()
    );
}

const std::vector<std::shared_ptr<Customer>>&
CustomerManager::getAllCustomers() const
{
    return customers;
}

void CustomerManager::startMembershipCycle(
    std::shared_ptr<Customer>& customer,
    const std::string& tier)
{
    if (!customer)
    {
        return;
    }

    auto vip =
        std::dynamic_pointer_cast<VIPCustomer>(
            customer
        );

    if (!vip)
    {
        auto newVip =
            std::make_shared<VIPCustomer>(
                customer->getName(),
                customer->getPhone(),
                customer->getAddress(),
                tier
            );

        newVip->setTotalSpent(
            customer->getTotalSpent()
        );

        newVip->setPurchaseCount(
            customer->getPurchaseCount()
        );

        newVip->setQuarterSpent(0.0);

        newVip->setMembershipStartDate(
            getCurrentDate()
        );

        for (auto& c : customers)
        {
            if (c->getPhone() ==
                customer->getPhone())
            {
                c = newVip;
                break;
            }
        }

        customer = newVip;

        return;
    }

    vip->setMembershipTier(tier);
    vip->setQuarterSpent(0.0);
    vip->setMembershipStartDate(
        getCurrentDate()
    );
}

void CustomerManager::refreshMembership(
    std::shared_ptr<Customer>& customer)
{
    if (!customer)
    {
        return;
    }

    auto vip =
        std::dynamic_pointer_cast<VIPCustomer>(
            customer
        );

    if (!vip)
    {
        if (customer->getTotalSpent() >=
            Membership::SILVER_THRESHOLD)
        {
            startMembershipCycle(
                customer,
                "Silver"
            );
        }

        return;
    }

    if (vip->getMembershipStartDate().empty())
    {
        vip->setMembershipStartDate(
            getCurrentDate()
        );

        vip->setQuarterSpent(0.0);

        return;
    }

    std::string today =
        getCurrentDate();

    int months =
        monthsBetween(
            vip->getMembershipStartDate(),
            today
        );

    if (months < 3)
    {
        return;
    }

    double spent =
        vip->getQuarterSpent();

    std::string newTier;

    if (spent >=
        Membership::DIAMOND_THRESHOLD)
    {
        newTier = "Kim Cương";
    }
    else if (spent >=
             Membership::GOLD_THRESHOLD)
    {
        newTier = "Vàng";
    }
    else if (spent >=
             Membership::SILVER_THRESHOLD)
    {
        newTier = "Bạc";
    }
    else
    {
        for (auto& c : customers)
        {
            if (c->getPhone() ==
                vip->getPhone())
            {
                auto regular =
                    std::make_shared<Customer>(
                        vip->getName(),
                        vip->getPhone(),
                        vip->getAddress()
                    );

                regular->setTotalSpent(
                    vip->getTotalSpent()
                );

                regular->setPurchaseCount(
                    vip->getPurchaseCount()
                );

                regular->setQuarterSpent(0.0);
                regular->setMembershipStartDate("");

                c = regular;
                customer = regular;

                return;
            }
        }

        return;
    }

    vip->setMembershipTier(newTier);

    vip->setQuarterSpent(0.0);

    vip->setMembershipStartDate(
        today
    );
}

void CustomerManager::upgradeIfEligible(
    std::shared_ptr<Customer>& customer)
{
    if (!customer)
    {
        return;
    }

    auto vip =
        std::dynamic_pointer_cast<VIPCustomer>(
            customer
        );

    if (!vip)
    {
        if (customer->getTotalSpent() >=
            Membership::DIAMOND_THRESHOLD)
        {
            startMembershipCycle(
                customer,
                "Kim Cương"
            );
        }
        else if (customer->getTotalSpent() >=
                 Membership::GOLD_THRESHOLD)
        {
            startMembershipCycle(
                customer,
                "Vàng"
            );
        }
        else if (customer->getTotalSpent() >=
                 Membership::SILVER_THRESHOLD)
        {
            startMembershipCycle(
                customer,
                "Bạc"
            );
        }

        return;
    }

    double quarterSpent =
        vip->getQuarterSpent();

    std::string currentTier =
        vip->getMembershipTier();

    std::string targetTier =
        currentTier;

    if (quarterSpent >=
        Membership::DIAMOND_THRESHOLD)
    {
        targetTier = "Kim Cương";
    }
    else if (quarterSpent >=
             Membership::GOLD_THRESHOLD)
    {
        targetTier = "Vàng";
    }
    else if (quarterSpent >=
             Membership::SILVER_THRESHOLD)
    {
        targetTier = "Bạc";
    }

    if (tierRank(targetTier) >
        tierRank(currentTier))
    {
        vip->setMembershipTier(
            targetTier
        );

        vip->setQuarterSpent(0.0);

        vip->setMembershipStartDate(
            getCurrentDate()
        );
    }
}

std::string CustomerManager::recordPurchase(
    std::shared_ptr<Customer>& customer,
    double amountSpent,
    const std::string& saveFilePath)
{
    if (!customer ||
        amountSpent <= 0.0)
    {
        return "";
    }

    refreshMembership(customer);

    std::string tierBefore;

    auto vipBefore =
        std::dynamic_pointer_cast<VIPCustomer>(
            customer
        );

    if (vipBefore)
    {
        tierBefore =
            vipBefore->getMembershipTier();

        vipBefore->addQuarterSpent(
            amountSpent
        );
    } 

    customer->recordPurchase(
        amountSpent
    );

    upgradeIfEligible(customer);

    std::string tierAfter;

    auto vipAfter =
        std::dynamic_pointer_cast<VIPCustomer>(
            customer
        );

    if (vipAfter)
    {
        tierAfter =
            vipAfter->getMembershipTier();
    }

    saveToFile(saveFilePath);

    if (!tierAfter.empty() &&
        tierAfter != tierBefore)
    {
        return tierAfter;
    }

    return "";
}