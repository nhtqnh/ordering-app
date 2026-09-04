#include "utils/Menu.h"
#include "utils/InputUtils.h"
#include "product/ProductManager.h"
#include "cart/ShoppingCart.h"
#include "order/OrderManager.h"
#include "customer/Customer.h"
#include "customer/VIPCustomer.h"
#include "customer/CustomerManager.h"
#include "customer/StandardDelivery.h"
#include "customer/ExpressDelivery.h"
#include <iostream>
#include <iomanip>
#include <memory>

namespace {

const std::string PRODUCTS_FILE = "../data/products.txt";
const std::string CUSTOMERS_FILE = "../data/customers.txt";

// ===================== SAN PHAM =====================

void handleSearchProduct(ProductManager& productManager)
{
    std::string keyword = InputUtils::readNonEmptyString("Nhap ten san pham can tim: ");
    std::vector<Product> results = productManager.searchByName(keyword);

    if (results.empty())
    {
        std::cout << "Khong tim thay san pham phu hop.\n";
        return;
    }

    std::cout << "\n===== KET QUA TIM KIEM (" << results.size() << ") =====\n";
    for (const auto& p : results)
    {
        std::cout << p << std::endl;
    }
}

void handleSortProduct(ProductManager& productManager)
{
    std::cout << "\n===== SAP XEP SAN PHAM =====\n";
    std::cout << "1. Gia tang dan\n";
    std::cout << "2. Gia giam dan\n";
    std::cout << "3. Ten A-Z\n";
    std::cout << "0. Quay lai\n";
    int choice = InputUtils::readInt("Chon: ", 0, 3);

    switch (choice)
    {
        case 1:
            productManager.sortByPriceAscending();
            productManager.displayAll();
            break;
        case 2:
            productManager.sortByPriceDescending();
            productManager.displayAll();
            break;
        case 3:
            productManager.sortByName();
            productManager.displayAll();
            break;
        default:
            break;
    }
}

// ===================== GIO HANG =====================

void handleCartMenu(ShoppingCart& cart, ProductManager& productManager)
{
    int choice;
    do
    {
        std::cout << "\n===== GIO HANG =====\n";
        std::cout << "1. Them san pham\n";
        std::cout << "2. Xem gio hang\n";
        std::cout << "3. Cap nhat so luong\n";
        std::cout << "4. Xoa san pham\n";
        std::cout << "5. Xoa toan bo gio hang\n";
        std::cout << "0. Quay lai\n";
        choice = InputUtils::readInt("Chon: ", 0, 5);

        switch (choice)
        {
            case 1:
            {
                int productId = InputUtils::readInt("Nhap ID san pham: ");
                Product* p = productManager.findById(productId);
                if (p == nullptr)
                {
                    std::cout << "Khong tim thay san pham!\n";
                    break;
                }
                if (p->getQuantity() <= 0)
                {
                    std::cout << "San pham da het hang!\n";
                    break;
                }

                int quantity = InputUtils::readInt("Nhap so luong: ", 1, 1000);
                if (cart.addProduct(*p, quantity))
                {
                    std::cout << "Da them vao gio hang!\n";
                }
                else
                {
                    std::cout << "Ton kho khong du (con lai " << p->getQuantity()
                               << ", trong gio da co " << cart.getQuantityInCart(productId)
                               << ")!\n";
                }
                break;
            }
            case 2:
                cart.display();
                break;
            case 3:
            {
                if (cart.isEmpty())
                {
                    std::cout << "Gio hang dang trong!\n";
                    break;
                }
                int productId = InputUtils::readInt("Nhap ID san pham can cap nhat: ");
                Product* p = productManager.findById(productId);
                if (p == nullptr)
                {
                    std::cout << "Khong tim thay san pham!\n";
                    break;
                }
                int quantity = InputUtils::readInt("Nhap so luong moi: ", 1, 1000);
                if (cart.updateQuantity(productId, quantity, p->getQuantity()))
                {
                    std::cout << "Da cap nhat so luong!\n";
                }
                else
                {
                    std::cout << "Cap nhat that bai: san pham khong co trong gio hoac vuot ton kho (con lai "
                               << p->getQuantity() << ")!\n";
                }
                break;
            }
            case 4:
            {
                if (cart.isEmpty())
                {
                    std::cout << "Gio hang dang trong!\n";
                    break;
                }
                int productId = InputUtils::readInt("Nhap ID san pham can xoa: ");
                if (cart.removeProduct(productId))
                {
                    std::cout << "Da xoa san pham khoi gio hang!\n";
                }
                else
                {
                    std::cout << "Khong tim thay san pham trong gio hang!\n";
                }
                break;
            }
            case 5:
                if (cart.isEmpty())
                {
                    std::cout << "Gio hang da trong san!\n";
                }
                else if (InputUtils::confirm("Ban co chac muon xoa toan bo gio hang?"))
                {
                    cart.clear();
                    std::cout << "Da xoa toan bo gio hang!\n";
                }
                break;
            default:
                break;
        }
    } while (choice != 0);
}

// ===================== KHACH HANG =====================

std::shared_ptr<Customer> identifyOrCreateCustomer(CustomerManager& customerManager)
{
    std::string phone;
    while (true)
    {
        phone = InputUtils::readNonEmptyString("Nhap so dien thoai: ");
        if (CustomerManager::isValidPhone(phone))
        {
            break;
        }
        std::cout << "So dien thoai khong hop le (chi gom 9-11 chu so). Vui long nhap lai.\n";
    }

    std::shared_ptr<Customer> customer = customerManager.findByPhone(phone);
    if (customer != nullptr)
    {
        std::cout << "\nDa nhan dien khach hang cu:\n";
        customer->print();
        return customer;
    }

    std::cout << "\nSo dien thoai chua ton tai trong he thong. Tao khach hang moi.\n";
    std::string name = InputUtils::readNonEmptyString("Nhap ho va ten: ");
    std::string address = InputUtils::readNonEmptyString("Nhap dia chi giao hang: ");

    customer = std::make_shared<Customer>(name, phone, address);
    customerManager.addCustomer(customer);
    customerManager.saveToFile(CUSTOMERS_FILE);
    std::cout << "Da tao khach hang moi (Khach hang thuong).\n";
    return customer;
}

void handleCustomerInfoMenu(CustomerManager& customerManager)
{
    std::string phone = InputUtils::readNonEmptyString("Nhap so dien thoai can tra cuu: ");
    std::shared_ptr<Customer> customer = customerManager.findByPhone(phone);
    if (customer == nullptr)
    {
        std::cout << "Khong tim thay khach hang.\n";
        return;
    }

    auto vip = std::dynamic_pointer_cast<VIPCustomer>(customer);

    int choice;
    do
    {
        std::cout << "\n========== THONG TIN KHACH HANG ==========\n";
        std::cout << "1. Tra cuu thong tin khach hang\n";
        std::cout << "2. Xem hang thanh vien\n";
        std::cout << "3. Xem so lan mua hang\n";
        std::cout << "0. Quay lai\n";
        choice = InputUtils::readInt("Chon: ", 0, 3);

        switch (choice)
        {
            case 1:
            {
                customer->print();
                
                if (InputUtils::confirm("\nBan co muon cap nhat thong tin ca nhan khong?"))
                {
                    std::cout << "\n--- Cap nhat thong tin ---\n";
                    std::cout << "1. Doi ten\n";
                    std::cout << "2. Doi dia chi giao hang\n";
                    std::cout << "0. Huy\n";
                    int updateChoice = InputUtils::readInt("Chon muc can doi: ", 0, 2);
                    
                    if (updateChoice == 1) 
                    {
                        std::string newName = InputUtils::readNonEmptyString("Nhap ten moi: ");
                        customer->setName(newName);
                        std::cout << "Cap nhat ten thanh cong!\n";
                        customerManager.saveToFile(CUSTOMERS_FILE);
                    } 
                    else if (updateChoice == 2) 
                    {
                        std::string newAddress = InputUtils::readNonEmptyString("Nhap dia chi moi: ");
                        customer->setAddress(newAddress);
                        std::cout << "Cap nhat dia chi thanh cong!\n";
                        customerManager.saveToFile(CUSTOMERS_FILE);
                    }
                }
                break;
            }
            case 2:
            {
                double spent = customer->getTotalSpent();
                if (vip && spent >= 3000000)
                {
                    std::string tier = vip->getMembershipTier();
                    double target = 3000000; 

                    if (tier == "Vàng") target = 5000000;
                    else if (tier == "Kim Cương") target = 10000000;

                    std::cout << "Hang thanh vien: " << tier << "\n";
                    std::cout << "Han muc: " << std::fixed << std::setprecision(0) 
                              << spent << " / " << target << " VND\n";
                }
                else
                {
                    std::cout << "Khach hang chua dat dieu kien VIP.\n";
                    std::cout << "Han muc: " << std::fixed << std::setprecision(0) 
                              << spent << " / 3000000 VND\n";
                }
                break;
            }
            case 3:
                std::cout << "So lan mua hang: " << customer->getPurchaseCount() << "\n";
                break;
            default:
                break;
        }
    } while (choice != 0);
}

// ===================== DAT HANG =====================

void handlePlaceOrder(ShoppingCart& cart, ProductManager& productManager,
                       OrderManager& orderManager, CustomerManager& customerManager)
{
    if (cart.isEmpty())
    {
        std::cout << "Gio hang dang trong! Vui long them san pham truoc khi dat hang.\n";
        return;
    }

    std::shared_ptr<Customer> customer = identifyOrCreateCustomer(customerManager);

    std::cout << "\n===== PHUONG THUC GIAO HANG =====\n";
    std::cout << "1. Giao hang tieu chuan\n";
    std::cout << "2. Giao hang hoa toc\n";
    int deliveryChoice = InputUtils::readInt("Chon phuong thuc giao: ", 1, 2);

    std::shared_ptr<DeliveryMethod> delivery;
    if (deliveryChoice == 2)
    {
        delivery = std::make_shared<ExpressDelivery>();
    }
    else
    {
        delivery = std::make_shared<StandardDelivery>();
    }

    Order previewOrder(0, customer, delivery, cart.getItems());
    previewOrder.display(true);

    if (!InputUtils::confirm("\nXac nhan dat hang?"))
    {
        std::cout << "Da huy dat hang.\n";
        return;
    }

    for (const auto& item : cart.getItems())
    {
        Product* p = productManager.findById(item.getProduct().getId());
        if (p == nullptr || p->getQuantity() < item.getQuantity())
        {
            std::cout << "Dat hang that bai: san pham \"" << item.getProduct().getName()
                       << "\" khong con du ton kho.\n";
            return;
        }
    }

    Order finalOrder = orderManager.createOrder(customer, delivery, cart);
    if (!finalOrder.isValid())
    {
        std::cout << "Dat hang that bai!\n";
        return;
    }

    for (const auto& item : cart.getItems())
    {
        Product* p = productManager.findById(item.getProduct().getId());
        if (p != nullptr)
        {
            p->reduceQuantity(item.getQuantity());
        }
    }

    std::string upgradedTier = customerManager.recordPurchase(
        customer, finalOrder.getSubtotal(), CUSTOMERS_FILE);

    cart.clear();

    std::cout << "\nDAT HANG THANH CONG!\n";

    if (!upgradedTier.empty())
    {
        std::cout << "\n CHUC MUNG! Ban vua duoc nang hang thanh khach hang VIP hang "
                   << upgradedTier << "! \n";
    }
}

} // namespace

void Menu::run()
{
    ProductManager productManager;
    ShoppingCart cart;
    OrderManager orderManager;
    CustomerManager customerManager;

    if (!productManager.loadFromFile(PRODUCTS_FILE))
    {
        std::cerr << "Khong the tai danh sach san pham!\n";
        return;
    }

    customerManager.loadFromFile(CUSTOMERS_FILE);

    int choice;
    do
    {
        std::cout << "\n================================================\n";
        std::cout << "             UNG DUNG DAT HANG\n";
        std::cout << "================================================\n";
        std::cout << "1. Xem danh sach san pham\n";
        std::cout << "2. Tim kiem san pham\n";
        std::cout << "3. Sap xep san pham\n";
        std::cout << "4. Gio hang\n";
        std::cout << "5. Dat hang\n";
        std::cout << "6. Thong tin khach hang\n";
        std::cout << "7. Xem lich su don hang\n";
        std::cout << "0. Thoat\n";
        choice = InputUtils::readInt("Lua chon cua ban: ", 0, 7);

        switch (choice)
        {
            case 1:
                productManager.displayAll();
                break;
            case 2:
                handleSearchProduct(productManager);
                break;
            case 3:
                handleSortProduct(productManager);
                break;
            case 4:
                handleCartMenu(cart, productManager);
                break;
            case 5:
                handlePlaceOrder(cart, productManager, orderManager, customerManager);
                break;
            case 6:
                handleCustomerInfoMenu(customerManager);
                break;
            case 7:
                orderManager.displayAll();
                break;
            case 0:
                std::cout << "Cam on ban da su dung ung dung!\n";
                break;
            default:
                break;
        }
    } while (choice != 0);
}