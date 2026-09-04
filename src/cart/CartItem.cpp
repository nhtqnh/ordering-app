#include "cart/CartItem.h"

CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity)
{
}

Product CartItem::getProduct() const
{
    return product;
}

int CartItem::getQuantity() const
{
    return quantity;
}

void CartItem::setQuantity(int quantity)
{
    if (quantity > 0)
        this->quantity = quantity;
}

void CartItem::increaseQuantity()
{
    quantity++;
}

double CartItem::getTotal() const
{
    return product.getPrice() * quantity;
}