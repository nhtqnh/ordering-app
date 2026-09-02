#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
using namespace std;

class Customer
{
private:
    string name;
    string phone;
    string address;

public:
    Customer(string name = "", string phone = "", string address = "")
    {
        this->name = name;
        this->phone = phone;
        this->address = address;
    }

    string getName() const
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getPhone() const
    {
        return phone;
    }

    void setPhone(string phone)
    {
        this->phone = phone;
    }

    string getAddress() const
    {
        return address;
    }

    void setAddress(string address)
    {
        this->address = address;
    }

    void print() const
    {
        cout << "Customer Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
    }
};

#endif