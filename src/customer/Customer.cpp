#include "customer/Customer.h"
#include "customer/Membership.h"

#include <iomanip>

using namespace std;

Customer::Customer(const string& name,
                   const string& phone,
                   const string& address)
    : name(name),
      phone(phone),
      address(address),
      totalSpent(0.0),
      purchaseCount(0),
      quarterSpent(0.0),
      membershipStartDate("")
{
}

Customer::Customer(const Customer& other)
    : name(other.name),
      phone(other.phone),
      address(other.address),
      totalSpent(other.totalSpent),
      purchaseCount(other.purchaseCount),
      quarterSpent(other.quarterSpent),
      membershipStartDate(other.membershipStartDate)
{
}

Customer::~Customer()
{
}

string Customer::getName() const
{
    return name;
}

void Customer::setName(const string& name)
{
    this->name = name;
}

string Customer::getPhone() const
{
    return phone;
}

void Customer::setPhone(const string& phone)
{
    this->phone = phone;
}

string Customer::getAddress() const
{
    return address;
}

void Customer::setAddress(const string& address)
{
    this->address = address;
}

double Customer::getTotalSpent() const
{
    return totalSpent;
}

void Customer::setTotalSpent(double value)
{
    if (value >= 0.0)
    {
        totalSpent = value;
    }
}

int Customer::getPurchaseCount() const
{
    return purchaseCount;
}

void Customer::setPurchaseCount(int value)
{
    if (value >= 0)
    {
        purchaseCount = value;
    }
}

double Customer::getQuarterSpent() const
{
    return quarterSpent;
}

void Customer::setQuarterSpent(double value)
{
    if (value >= 0.0)
    {
        quarterSpent = value;
    }
}

void Customer::addQuarterSpent(double amount)
{
    if (amount > 0.0)
    {
        quarterSpent += amount;
    }
}

string Customer::getMembershipStartDate() const
{
    return membershipStartDate;
}

void Customer::setMembershipStartDate(const string& date)
{
    membershipStartDate = date;
}

void Customer::recordPurchase(double amount)
{
    if (amount <= 0.0)
    {
        return;
    }

    totalSpent += amount;
    purchaseCount += 1;
}

string Customer::getCustomerType() const
{
    return "Khach hang tieu chuan";
}

double Customer::getDiscountRate() const
{
    return 0.0;
}

void Customer::print() const
{
    cout << "-------------------------------------------\n"
         << "Hang thanh vien : " << getCustomerType() << "\n"
         << "Ten khach hang  : " << name << "\n"
         << "So dien thoai   : " << phone << "\n"
         << "Dia chi         : " << address << "\n"
         << "Tong tien da mua: "
         << fixed << setprecision(0)
         << totalSpent << " VND\n"
         << "So lan mua hang : "
         << purchaseCount << "\n"
         << "-------------------------------------------"
         << endl;
}

ostream& operator<<(ostream& os, const Customer& customer)
{
    os << customer.name
       << " (" << customer.phone << ") - "
       << customer.address;

    return os;
}

istream& operator>>(istream& is, Customer& customer)
{
    cout << "  > Nhap ho va ten: ";
    getline(is, customer.name);

    cout << "  > Nhap so dien thoai: ";
    getline(is, customer.phone);

    cout << "  > Nhap dia chi giao hang: ";
    getline(is, customer.address);

    return is;
}