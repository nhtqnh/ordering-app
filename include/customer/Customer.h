#pragma once

#include <string>
#include <iostream>

class Customer
{
protected:
    std::string name;
    std::string phone;
    std::string address;

    // ===== DỮ LIỆU TÍCH LŨY TOÀN THỜI GIAN =====
    double totalSpent;
    int purchaseCount;

    // ===== DỮ LIỆU CHU KỲ VIP =====
    // Chỉ có ý nghĩa khi customer đang là VIP.
    double quarterSpent;
    std::string membershipStartDate; // YYYY-MM-DD

public:
    Customer(const std::string& name = "",
             const std::string& phone = "",
             const std::string& address = "");

    Customer(const Customer& other);

    virtual ~Customer();

    // ===== THÔNG TIN CƠ BẢN =====
    std::string getName() const;
    void setName(const std::string& name);

    std::string getPhone() const;
    void setPhone(const std::string& phone);

    std::string getAddress() const;
    void setAddress(const std::string& address);

    // ===== TÍCH LŨY TOÀN THỜI GIAN =====
    double getTotalSpent() const;
    void setTotalSpent(double value);

    int getPurchaseCount() const;
    void setPurchaseCount(int value);

    // ===== CHU KỲ VIP =====
    double getQuarterSpent() const;
    void setQuarterSpent(double value);
    void addQuarterSpent(double amount);

    std::string getMembershipStartDate() const;
    void setMembershipStartDate(const std::string& date);

    virtual void recordPurchase(double amount);

    virtual std::string getCustomerType() const;
    virtual double getDiscountRate() const;
    virtual void print() const;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Customer& customer);

    friend std::istream& operator>>(std::istream& is,
                                    Customer& customer);
};