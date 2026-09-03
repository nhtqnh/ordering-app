#pragma once

#include <string>
#include <iosfwd>

class Customer
{
private:
    std::string name;
    std::string phone;
    std::string address;

public:
    Customer(
        const std::string& name = "",
        const std::string& phone = "",
        const std::string& address = ""
    );

    std::string getName() const;
    void setName(const std::string& name);

    std::string getPhone() const;
    void setPhone(const std::string& phone);

    std::string getAddress() const;
    void setAddress(const std::string& address);

    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const Customer& customer);
    friend std::istream& operator>>(std::istream& in, Customer& customer);
};