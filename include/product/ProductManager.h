#pragma once

#include <vector>
#include <string>
#include "product/Product.h"

class ProductManager
{
private:
    std::vector<Product> products;   

public:
    ProductManager();
    bool loadFromFile(const std::string& filePath);

    //hien thi danh sach san pham
    void displayAll() const;

    //tim kiem san pham theo id 
    Product* findById(int id);

    //tim kiem san pham theo ten
    std::vector<Product> searchByName(const std::string& keyword) const;

    //sxep danh sach theo gia 
    void sortByPriceAscending();
    void sortByPriceDescending();

    //sx theo ten 
    void sortByName();

    //lay toan bo danh sach
    const std::vector<Product>& getAllProducts() const;

    int getTotalProducts() const;
};