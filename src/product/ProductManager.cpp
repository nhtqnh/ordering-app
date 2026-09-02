#include "product/ProductManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

ProductManager::ProductManager()
{
}

// ---- Ham phu: tach chuoi theo dau phan cach ----
static std::vector<std::string> splitLine(const std::string& line, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool ProductManager::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Loi: Khong the mo file " << filePath << std::endl;
        return false;
    }

    products.clear();
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::vector<std::string> tokens = splitLine(line, ';');
        if (tokens.size() < 5) continue; // dong du lieu khong hop le -> bo qua

        int id = std::stoi(tokens[0]);
        std::string name = tokens[1];
        double price = std::stod(tokens[2]);
        int quantity = std::stoi(tokens[3]);
        std::string category = tokens[4];

        products.push_back(Product(id, name, price, quantity, category));
    }

    file.close();
    return true;
}

//hien thi danh sach
void ProductManager::displayAll() const
{
    if (products.empty())
    {
        std::cout << "Danh sach san pham dang trong.\n";
        return;
    }

    for (const auto& p : products)
    {
        std::cout << p << std::endl;   // dung operator<< da nap chong trong Product
    }
}

//tim kiem theo id
Product* ProductManager::findById(int id)
{
    for (auto& p : products)
    {
        if (p.getId() == id)   
        {
            return &p;
        }
    }
    return nullptr;
}

//tim kiem theo ten
static std::string toLower(const std::string& s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::vector<Product> ProductManager::searchByName(const std::string& keyword) const
{
    std::vector<Product> result;
    std::string lowerKeyword = toLower(keyword);

    for (const auto& p : products)
    {
        if (toLower(p.getName()).find(lowerKeyword) != std::string::npos)
        {
            result.push_back(p);
        }
    }
    return result;
}

//sap xep theo gia
void ProductManager::sortByPriceAscending()
{
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) { return a < b; });
}

void ProductManager::sortByPriceDescending()
{
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) { return a > b; });
}

//sap xep theo ten
void ProductManager::sortByName()
{
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b)
              {
                  return a.getName() < b.getName();
              });
}

const std::vector<Product>& ProductManager::getAllProducts() const
{
    return products;
}

int ProductManager::getTotalProducts() const
{
    return static_cast<int>(products.size());
}