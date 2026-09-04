#include "order/OrderManager.h"
#include <iostream>

OrderManager::OrderManager() : nextOrderId(1) {}

Order OrderManager::createOrder(
    std::shared_ptr<Customer> customer,
    std::shared_ptr<DeliveryMethod> deliveryMethod,
    const ShoppingCart& cart
) {
    if (cart.isEmpty()) {
        return Order();
    }
    Order order(nextOrderId++, customer, deliveryMethod, cart.getItems());
    orders.push_back(order);
    return order;
}

void OrderManager::displayAll() const {
    if (orders.empty()) {
        std::cout << "\nChua co don hang nao.\n";
        return;
    }

    for (const auto& order : orders) {
        order.displayHistory();
    }
}