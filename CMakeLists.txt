cmake_minimum_required(VERSION 3.16)

project(OrderingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(OrderingApp
    src/main.cpp

    # Customer
    src/customer/Customer.cpp
    src/customer/VIPCustomer.cpp
    src/customer/DeliveryMethod.cpp
    src/customer/StandardDelivery.cpp
    src/customer/ExpressDelivery.cpp
    src/customer/CustomerManager.cpp


    # Product
    src/product/Product.cpp
    src/product/ProductManager.cpp

    # Cart
    src/cart/CartItem.cpp
    src/cart/ShoppingCart.cpp

    # Order
    src/order/Order.cpp
    src/order/OrderManager.cpp

    # Utils
    src/utils/DateUtils.cpp
    src/utils/InputUtils.cpp
    src/utils/Menu.cpp
)