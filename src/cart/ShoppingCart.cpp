#include "cart/ShoppingCart.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool ShoppingCart::isEmpty() const
{
    return items.empty();
}

int ShoppingCart::getSize() const
{
    return static_cast<int>(items.size());
}

int ShoppingCart::getQuantityInCart(int productId) const
{
    for (const auto& item : items)
    {
        if (item.getProduct().getId() == productId)
        {
            return item.getQuantity();
        }
    }
    return 0;
}

bool ShoppingCart::addProduct(const Product& product, int quantity)
{
    if (quantity <= 0)
    {
        return false;
    }

    int currentInCart = getQuantityInCart(product.getId());
    if (currentInCart + quantity > product.getQuantity())
    {
        return false; // vuot qua ton kho
    }

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getProduct().getId() == product.getId())
        {
            items[i].setQuantity(items[i].getQuantity() + quantity);
            return true;
        }
    }

    items.push_back(CartItem(product, quantity));
    return true;
}

bool ShoppingCart::removeProduct(int productId)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getProduct().getId() == productId)
        {
            items.erase(items.begin() + i);
            return true;
        }
    }

    return false;
}

bool ShoppingCart::updateQuantity(int productId, int quantity, int stockAvailable)
{
    if (quantity <= 0)
    {
        return false;
    }
    if (quantity > stockAvailable)
    {
        return false; // vuot qua ton kho
    }

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getProduct().getId() == productId)
        {
            items[i].setQuantity(quantity);
            return true;
        }
    }

    return false;
}

double ShoppingCart::getSubtotal() const
{
    double subtotal = 0;

    for (int i = 0; i < items.size(); i++)
    {
        subtotal += items[i].getTotal();
    }

    return subtotal;
}

void ShoppingCart::display() const
{
    if (items.empty())
    {
        cout << "Gio hang dang trong." << endl;
        return;
    }

    cout << "===== GIO HANG =====" << endl;

    for (int i = 0; i < items.size(); i++)
    {
        Product product = items[i].getProduct();

        cout << i + 1 << ". "
            << product.getName()
            << " | Gia: "
            << fixed << setprecision(0)
            << product.getPrice()
            << " VND | So luong: "
            << items[i].getQuantity()
            << " | Thanh tien: "
            << items[i].getTotal()
            << " VND"
            << endl;
    }

    cout << "Tam tinh: "
        << fixed << setprecision(0)
        << getSubtotal()
        << " VND"
        << endl;
}

void ShoppingCart::clear()
{
    items.clear();
}

const vector<CartItem>& ShoppingCart::getItems() const
{
    return items;
}