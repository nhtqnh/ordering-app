#pragma once
#include "product/Product.h"

class CartItem
{
private:
    Product product;
    int quantity;

public:
    CartItem(const Product& product, int quantity = 1);

    Product getProduct() const;
    int getQuantity() const;

    void setQuantity(int quantity);
    void increaseQuantity();

    double getTotal() const;
};