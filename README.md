ORDERING APPLICATION (OOP C++)

Đồ án môn Lập trình hướng đối tượng (OOP) - Trường Đại học Giao thông vận tải TP.HCM.

**1. GIỚI THIỆU DỰ ÁN**
Ứng dụng đặt hàng chạy trên môi trường Console, viết bằng ngôn ngữ C++17. Chương trình hỗ trợ người dùng duyệt sản phẩm từ tệp dữ liệu, quản lý giỏ hàng, chọn phương thức vận chuyển và tính toán tự động thông tin đơn hàng cùng thời gian giao hàng dự kiến.

**2. TÍNH NĂNG CHÍNH**
* Quản lý sản phẩm: Tải dữ liệu từ file `products.txt`, hỗ trợ tìm kiếm và sắp xếp danh sách sản phẩm.
* Giỏ hàng: Thêm sản phẩm nhiều lần, tự động cập nhật số lượng, xóa item và xem chi tiết giỏ hàng.
* Đặt hàng & Vận chuyển: Cho phép người dùng nhập thông tin cá nhân, chọn phương thức giao hàng Tiêu chuẩn (Standard) hoặc Hỏa tốc (Express).
* Xử lý thời gian tự động: Tự động lấy ngày đặt hàng hiện tại từ hệ thống và tính toán ngày giao dự kiến dựa trên phương thức vận chuyển.

**3. ÁP DỤNG KIẾN THỨC OOP & STL**
* Đóng gói (Encapsulation): Bảo vệ thuộc tính của các lớp `Product`, `Customer`, `ShoppingCart`, `Order` thông qua getter/setter.
* Kế thừa & Đa hình (Inheritance & Polymorphism): Lớp cơ sở `DeliveryMethod` cùng hai lớp dẫn xuất `StandardDelivery` và `ExpressDelivery` ghi đè hàm tính phí và thời gian giao.
* Thư viện STL: 
  * `std::vector` quản lý danh sách sản phẩm và giỏ hàng.
  * `std::string` xử lý dữ liệu chuỗi.
  * `std::algorithm` thực hiện các thao tác tìm kiếm và sắp xếp.

**4. CẤU TRÚC THƯ MỤC**
OrderingApp/
├── data/               # Chứa tệp products.txt
├── docs/               # Tài liệu thiết kế & task_group01.xlsx
├── include/            # Tệp khai báo Header (.h)
├── src/                # Tệp cài đặt Source (.cpp)
└── CMakeLists.txt      # Cấu hình biên dịch CMake

**5. HƯỚNG DẪN BUILD & RUN**

Yêu cầu: C++17 trở lên và CMake (hoặc compiler g++).

Chạy bằng CMake:
  mkdir build
  cd build
  cmake ..
  cmake --build .
  ./OrderingApp

Chạy trực tiếp bằng g++:
  g++ -std=c++17 src/**/*.cpp src/main.cpp -Iinclude -o OrderingApp
  ./OrderingApp

**6. PHÂN CÔNG THÀNH VIÊN**
* Thành viên 1: Xây dựng Module Customer & Delivery
* Thành viên 2: Xây dựng Module Product & ProductManager
* Thành viên 3: Xây dựng Module CartItem & ShoppingCart
* Thành viên 4 (Leader): Xây dựng Module Order, DateUtils, Menu chính & Cấu hình CMake.