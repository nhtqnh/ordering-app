#pragma once
#include <iostream>
#include <string>

class Product
{
private:
    int id;
    std::string name;
    double price;
    int quantity;     
    std::string category;

public:
    Product();  
    Product(int id, const std::string& name, double price,
            int quantity, const std::string& category);


    ~Product();

    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getCategory() const;

    void setName(const std::string& name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setCategory(const std::string& category);

    //giam so luong ton kho khi co don hang
    bool reduceQuantity(int amount);

    //Ss 2 san pham theo id 
    bool operator==(const Product& other) const;

    //ss theo gia 
    bool operator<(const Product& other) const;
    bool operator>(const Product& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Product& p);
};