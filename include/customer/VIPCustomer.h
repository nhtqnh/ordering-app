#pragma once

#include <string>
#include "customer/Customer.h"

class VIPCustomer : public Customer
{
private:
    std::string membershipTier;

public:
    VIPCustomer(const std::string& name = "",
                const std::string& phone = "",
                const std::string& address = "",
                const std::string& membershipTier = "Silver");

    virtual ~VIPCustomer() override;

    std::string getMembershipTier() const;
    void setMembershipTier(const std::string& tier);

    virtual void recordPurchase(double amount) override;
    virtual std::string getCustomerType() const override;
    virtual double getDiscountRate() const override;
    virtual void print() const override;
};