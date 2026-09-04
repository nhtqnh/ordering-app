#include "order/Order.h"
#include "utils/DateUtils.h"
#include <iomanip>
#include <iostream>

Order::Order()
    : orderId(0), subtotal(0.0), discount(0.0), shippingFee(0.0), total(0.0) {}

Order::Order(
    int orderId,
    std::shared_ptr<Customer> customer,
    std::shared_ptr<DeliveryMethod> deliveryMethod,
    const std::vector<CartItem>& items
)
    : orderId(orderId),
      orderDate(DateUtils::getCurrentDate()),
      customer(customer),
      deliveryMethod(deliveryMethod),
      items(items),
      subtotal(0.0), discount(0.0), shippingFee(0.0), total(0.0)
{
    for (const auto& item : this->items) {
        subtotal += item.getTotal();
    }

    // Ap dung giam gia VIP tu chinh doi tuong Customer (da hinh: customer thuong
    // tra ve 0.0, VIPCustomer tra ve ty le giam theo hang thanh vien).
    double discountRate = (this->customer) ? this->customer->getDiscountRate() : 0.0;
    discount = subtotal * discountRate;

    shippingFee = this->deliveryMethod->calculateFee();
    expectedDeliveryDate = DateUtils::getExpectedDeliveryDate(this->deliveryMethod->getDeliveryDays());
    total = subtotal - discount + shippingFee;
}

int Order::getOrderId() const { return orderId; }

bool Order::isValid() const {
    return orderId > 0 && customer != nullptr && deliveryMethod != nullptr && !items.empty();
}

double Order::getSubtotal() const { return subtotal; }
double Order::getDiscount() const { return discount; }
double Order::getShippingFee() const { return shippingFee; }
double Order::getTotal() const { return total; }
std::shared_ptr<Customer> Order::getCustomer() const { return customer; }

void Order::display(bool isPreview) const {
    std::cout << "\n===========================================\n";

    if (isPreview) {
        std::cout << "           XEM TRUOC DON HANG\n";
    }

    std::cout << "===========================================\n";

    // Khi đặt hàng thật mới hiện mã đơn
    if (!isPreview) {
        std::cout << "Ma don hang       : " << orderId << "\n";
    }

    std::cout << "Ngay dat hang     : " << orderDate << "\n";
    std::cout << "Ngay giao du kien : " << expectedDeliveryDate << "\n";
    std::cout << "\n";

    for (size_t i = 0; i < items.size(); ++i) {
        const auto& item = items[i];

        std::cout << i + 1 << ". "
                  << item.getProduct().getName()
                  << "\n";

        std::cout << "   So luong   : "
                  << item.getQuantity()
                  << "\n";

        std::cout << "   Thanh tien : "
                  << std::fixed << std::setprecision(0)
                  << item.getTotal()
                  << " VND\n";
    }

    std::cout << "\n";

    if (deliveryMethod) {
        std::cout << "Phuong thuc : "
                  << deliveryMethod->getMethodName()
                  << "\n";
    }

    std::cout << "\n";

    std::cout << std::fixed << std::setprecision(0);

    std::cout << "Tam tinh        : "
              << subtotal << " VND\n";

    std::cout << "Giam gia        : "
              << discount << " VND\n";

    std::cout << "Phi van chuyen  : "
              << shippingFee << " VND\n";

    std::cout << "-------------------------------------------\n";

    std::cout << "TONG THANH TOAN : "
              << total << " VND\n";
}

void Order::displayHistory() const {
    std::cout << "\n===========================================\n";
    std::cout << "              MA DON HANG #" << orderId << "\n";
    std::cout << "===========================================\n";

    for (size_t i = 0; i < items.size(); ++i) {
        const auto& item = items[i];

        std::cout << i + 1 << ". "
                  << item.getProduct().getName()
                  << "\n";

        std::cout << "   So luong      : "
                  << item.getQuantity()
                  << "\n";

        std::cout << "   Thanh tien    : "
                  << std::fixed << std::setprecision(0)
                  << item.getTotal()
                  << " VND\n";
    }

    if (deliveryMethod) {
        std::cout << "Phuong thuc : "
                  << deliveryMethod->getMethodName()
                  << "\n";
    }

    std::cout << std::fixed << std::setprecision(0);

    std::cout << "Tong thanh toan : "
              << total
              << " VND\n";
}