#pragma once

#include <vector>
#include "CartItem.h"

using namespace std;

class ShoppingCart
{
private:
    vector<CartItem> items;

public:
    bool isEmpty() const;
    int getSize() const;

    void addProduct(const Product& product);

    bool removeProduct(int productId);
    bool updateQuantity(int productId, int quantity);

    double getSubtotal() const;

    void display() const;
    void clear();

    const vector<CartItem>& getItems() const;
};