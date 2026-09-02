#pragma once

#include <iostream>
#include <string>

// Lop Product - dai dien cho mot san pham trong cua hang
// Chuong 2: Dong goi (Encapsulation) - thuoc tinh private, truy cap qua getter/setter
// Chuong 3: Nap chong toan tu (Operator Overloading)
class Product
{
private:
    int id;
    std::string name;
    double price;
    int quantity;      // so luong ton kho
    std::string category;

public:
    // ---- Constructors ----
    Product();  // constructor mac dinh
    Product(int id, const std::string& name, double price,
            int quantity, const std::string& category);

    // ---- Destructor ----
    ~Product();

    // ---- Getters ----
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getCategory() const;

    // ---- Setters ----
    void setName(const std::string& name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setCategory(const std::string& category);

    // Giam so luong ton kho khi co don hang (tra ve true neu du hang)
    bool reduceQuantity(int amount);

    // ---- Operator Overloading (Chuong 3) ----
    // So sanh 2 san pham theo id -> dung cho tim kiem (search)
    bool operator==(const Product& other) const;

    // So sanh theo gia -> dung cho sap xep (sort) mac dinh theo gia tang dan
    bool operator<(const Product& other) const;
    bool operator>(const Product& other) const;

    // In thong tin san pham ra man hinh: std::cout << product;
    friend std::ostream& operator<<(std::ostream& os, const Product& p);
};