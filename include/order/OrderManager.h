#pragma once
#include <vector>
#include <memory>
#include "order/Order.h"
#include "cart/ShoppingCart.h"
#include "customer/Customer.h"
#include "customer/DeliveryMethod.h"

class OrderManager {
private:
    std::vector<Order> orders;
    int nextOrderId;

public:
    OrderManager();
    Order createOrder(
        std::shared_ptr<Customer> customer,
        std::shared_ptr<DeliveryMethod> deliveryMethod,
        const ShoppingCart& cart
    );
    void displayAll() const;
};