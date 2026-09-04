#include "customer/VIPCustomer.h"
#include <iomanip>
#include <iostream>

using namespace std;

VIPCustomer::VIPCustomer(
    const string& name,
    const string& phone,
    const string& address,
    const string& membershipTier
)
    : Customer(name, phone, address),
      membershipTier(membershipTier)
{
}

VIPCustomer::~VIPCustomer()
{
}

string VIPCustomer::getMembershipTier() const
{
    return membershipTier;
}

void VIPCustomer::setMembershipTier(const string& tier)
{
    membershipTier = tier;
}

void VIPCustomer::recordPurchase(double amount)
{
    Customer::recordPurchase(amount);
}

string VIPCustomer::getCustomerType() const
{
    return "Khach hang VIP [" + membershipTier + "]";
}

double VIPCustomer::getDiscountRate() const
{
    if (membershipTier == "Kim Cương")
        return 0.15;

    if (membershipTier == "Vàng")
        return 0.10;

    return 0.05;
}

void VIPCustomer::print() const
{
    Customer::print();

    cout << "Hang thanh vien : "
         << membershipTier
         << " (Giam gia: "
         << getDiscountRate() * 100
         << "%)\n"

         << "Chi tieu chu ky : "
         << fixed << setprecision(0)
         << getQuarterSpent()
         << " VND\n"

         << "Bat dau chu ky  : "
         << getMembershipStartDate()
         << "\n"

         << "-------------------------------------------"
         << endl;
}