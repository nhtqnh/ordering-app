#include "customer/Customer.h"

#include <iostream>
#include <string>

Customer::Customer(
    const std::string& name,
    const std::string& phone,
    const std::string& address
)
    : name(name), phone(phone), address(address)
{
}

std::string Customer::getName() const
{
    return name;
}

void Customer::setName(const std::string& name)
{
    this->name = name;
}

std::string Customer::getPhone() const
{
    return phone;
}

void Customer::setPhone(const std::string& phone)
{
    this->phone = phone;
}

std::string Customer::getAddress() const
{
    return address;
}

void Customer::setAddress(const std::string& address)
{
    this->address = address;
}

void Customer::print() const
{
    std::cout << "Customer Name: " << name << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Address: " << address << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Customer& customer)
{
    out << "Customer Name: " << customer.name << std::endl;
    out << "Phone: " << customer.phone << std::endl;
    out << "Address: " << customer.address;

    return out;
}

std::istream& operator>>(std::istream& in, Customer& customer)
{
    std::getline(in >> std::ws, customer.name);
    std::getline(in, customer.phone);
    std::getline(in, customer.address);

    return in;
}