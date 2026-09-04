#pragma once
#include <memory>
#include <string>
#include <vector>
#include "customer/Customer.h"
#include "customer/DeliveryMethod.h"
#include "cart/CartItem.h"

class Order {
private:
    int orderId;
    std::string orderDate;
    std::string expectedDeliveryDate;
    std::shared_ptr<Customer> customer;
    std::shared_ptr<DeliveryMethod> deliveryMethod;
    std::vector<CartItem> items;
    double subtotal;
    double discount;
    double shippingFee;
    double total;

public:
    Order();

    Order(
        int orderId,
        std::shared_ptr<Customer> customer,
        std::shared_ptr<DeliveryMethod> deliveryMethod,
        const std::vector<CartItem>& items
    );

    int getOrderId() const;
    bool isValid() const;

    // Hiển thị đầy đủ khi đặt hàng thành công
    void display(bool isPreview = false) const;

    // Hiển thị riêng cho lịch sử đơn hàng
    void displayHistory() const;

    double getSubtotal() const;
    double getDiscount() const;
    double getShippingFee() const;
    double getTotal() const;

    std::shared_ptr<Customer> getCustomer() const;
};