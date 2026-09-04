#pragma once

#include <vector>
#include "cart/CartItem.h"

using namespace std;

class ShoppingCart
{
private:
    vector<CartItem> items;

public:
    bool isEmpty() const;
    int getSize() const;

    // Them san pham vao gio hang voi so luong chi dinh (mac dinh 1).
    // Kiem tra ton kho: tra ve false neu (so luong da co trong gio + quantity)
    // vuot qua ton kho hien tai cua san pham (product.getQuantity()).
    bool addProduct(const Product& product, int quantity = 1);

    // Tong so luong cua 1 san pham dang co trong gio hang (0 neu chua co)
    int getQuantityInCart(int productId) const;

    bool removeProduct(int productId);

    // Cap nhat so luong, co kiem tra khong vuot qua ton kho (stockAvailable)
    bool updateQuantity(int productId, int quantity, int stockAvailable);

    double getSubtotal() const;

    void display() const;
    void clear();

    const vector<CartItem>& getItems() const;
};