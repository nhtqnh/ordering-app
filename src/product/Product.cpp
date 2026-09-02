#include "product/Product.h"

Product::Product()
    : id(0), name(""), price(0.0), quantity(0), category("")
{
}

Product::Product(int id, const std::string& name, double price,
                  int quantity, const std::string& category)
    : id(id), name(name), price(price), quantity(quantity), category(category)
{
}

Product::~Product()
{
}


int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
std::string Product::getCategory() const { return category; }

void Product::setName(const std::string& newName) { name = newName; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setQuantity(int newQuantity) { quantity = newQuantity; }
void Product::setCategory(const std::string& newCategory) { category = newCategory; }

bool Product::reduceQuantity(int amount)
{
    if (amount <= 0 || amount > quantity)
    {
        return false; 
    }
    quantity -= amount;
    return true;
}


bool Product::operator==(const Product& other) const
{
    return this->id == other.id;
}

bool Product::operator<(const Product& other) const
{
    return this->price < other.price;
}

bool Product::operator>(const Product& other) const
{
    return this->price > other.price;
}

std::ostream& operator<<(std::ostream& os, const Product& p)
{
    os << "[" << p.id << "] " << p.name
       << " | Gia: " << p.price << " VND"
       << " | Ton kho: " << p.quantity
       << " | Danh muc: " << p.category;
    return os;
}