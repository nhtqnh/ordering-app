#include "ShoppingCart.h"
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

void ShoppingCart::addProduct(const Product& product)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getProduct().getId() == product.getId())
        {
            items[i].increaseQuantity();
            return;
        }
    }

    items.push_back(CartItem(product, 1));
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

bool ShoppingCart::updateQuantity(int productId, int quantity)
{
    if (quantity <= 0)
    {
        return false;
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
        cout << "Shopping cart is empty." << endl;
        return;
    }

    cout << "===== SHOPPING CART =====" << endl;

    for (int i = 0; i < items.size(); i++)
    {
        Product product = items[i].getProduct();

        cout << i + 1 << ". "
            << product.getName()
            << " | Price: "
            << fixed << setprecision(2)
            << product.getPrice()
            << " | Quantity: "
            << items[i].getQuantity()
            << " | Total: "
            << items[i].getTotal()
            << endl;
    }

    cout << "Subtotal: "
        << fixed << setprecision(2)
        << getSubtotal()
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