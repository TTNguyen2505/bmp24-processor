# BMP24 Processor

## Short Description
`BMP24 Processor` is a C++17 command-line project for loading 24-bit BMP images, applying color filters, and performing geometric transformations. The code is built with CMake and Ninja on Windows.

## Course Information
- Course name: `IT1.109.3 - Data Structures and Algorithms`
- Assignment title: `Course Project`
- Instructor: `M.Sc. Tran Thi Dung`
- Institution: `University of Transport and Communications, Campus in Ho Chi Minh City`

## Features
- Load 24-bit BMP images from disk
- Save processed BMP images to a new file
- Apply color filters
  - Gray scale
  - Sepia
  - Invert
  - Brightness
  - Contrast
  - Saturation
- Apply geometric transforms
  - Rotation
  - Scaling
  - Shearing
  - Translation
- Command-line driven workflow
- Modular source layout with separate headers and implementation files

## Technologies
- Language: `C++17`
- Build system: `CMake`
- Build generator: `Ninja`
- Compiler: `g++`
- Script helper: `PowerShell`

## Requirements
To build this project on Windows, install the following tools:

- `CMake 4.0+`
- `Ninja`
- `g++` from `MinGW-w64` or another Windows GCC distribution
- `PowerShell` (included on modern Windows systems)

#### Check installed versions

```powershell
cmake --version
ninja --version
g++ --version
```

## How to Clone

Clone the repository and move into the project folder:

```powershell
git clone <repository-url>
cd <repo-folder>
```

## How to Build

### Option 1: Use the provided PowerShell script

```powershell
.\build.ps1
```

To rebuild from scratch:

```powershell
.\build.ps1 -Clean
```

This helper only configures and builds the project. The old `-Run` flow has been removed.

### Option 2: Build manually with CMake and Ninja

```powershell
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
```

## Run

After building, the executable is available at:

```powershell
.\build\bmp24-processor.exe
```

The command parser is still under development, but the intended usage looks like this:

```powershell
.\build\bmp24-processor.exe -grayscale 0.5 input.bmp
.\build\bmp24-processor.exe -invert 0.5 --rotate 90 input.bmp
```

## Project Structure

```text
project-root/
|-- build/                  # Generated build output
|-- include/                # Header files
|   |-- bmp24.hpp
|   |-- cli_parser.hpp
|   |-- color_filter.hpp
|   |-- matrix.hpp
|   |-- transform.hpp
|   `-- util.hpp
|-- samples/                # Sample assets and demo files
|   |-- bmp-source.bmp
|   |-- index.html
|   `-- style.css
|-- src/                    # Source files
|   |-- bmp24.cpp
|   |-- cli_parser.cpp
|   |-- color_filter.cpp
|   |-- main.cpp
|   |-- matrix.cpp
|   |-- transform.cpp
|   `-- util.cpp
|-- build.ps1               # Windows build helper script
|-- CMakeLists.txt          # CMake project definition
`-- README.md
```

## Limitations
- The project currently builds, but some processing functions are still marked `TODO`
- Command-line parsing is not fully implemented yet
- Help output is not fully implemented yet
- Image filters and transformations are still being completed
- The project currently targets 24-bit BMP images only
- No automated test suite is included


## Authors
| Student ID | Full Name | Major |
|---|---|---|
| `6551020083` | Huynh Thai Tu | Electronics and Telecommunications Engineering |
| `6651071004` | Nguyen Tran Duy Bao | Information Technology |
| `6651071013` | Nguyen Thanh Dat | Information Technology |
| `6651071099` | Tran Trong Nguyen | Information Technology |
| `6651071099` | Doan Xuan Tin | Information Technology |

# Công cụ xử lý ảnh BMP 24-bit

## Mô tả
`BMP24 Processor` là một dự án dòng lệnh viết bằng C++17 để đọc ảnh BMP 24-bit, áp dụng bộ lọc màu và thực hiện các phép biến đổi hình học. Mã nguồn được tổ chức theo cấu trúc đơn giản `src/` + `include/` và được build bằng CMake cùng Ninja trên Windows.

## Thông tin môn học
- Tên học phần: `IT1.109.3 - Cấu trúc dữ liệu và giải thuật`
- Tên bài tập: `Bài tập lớn`
- Giảng viên: `Ths. Trần Thị Dung`
- Trường: `Trường Đại học Giao thông Vân tại - Phân hiệu tại TP.HCM`

### Tính năng
- Đọc ảnh BMP 24-bit từ đĩa
- Lưu ảnh đã xử lý ra một tệp mới
- Áp dụng các bộ lọc màu
  - Thang xám
  - Sepia
  - Đảo màu
  - Độ sáng
  - Độ tương phản
  - Độ bão hòa
- Áp dụng các phép biến đổi hình học
  - Xoay
  - Phóng to/thu nhỏ
  - Xé nghiêng
  - Tịnh tiến
- Làm việc qua dòng lệnh
- Tách mã nguồn thành các file header và implementation riêng

## Công cụ sử dụng
- Ngôn ngữ: `C++17`
- Hệ thống build: `CMake`
- Bộ sinh build: `Ninja`
- Trình biên dịch: `g++`
- Script hỗ trợ: `PowerShell`

## Các yêu cầu
Để build dự án này trên Windows, hãy cài đặt các công cụ sau:

- `CMake 4.0+`
- `Ninja`
- `g++` từ `MinGW-w64` hoặc một bản CPP compiler khác cho Windows khác
- `PowerShell` (đã có sẵn trên Windows hiện đại)

### Kiểm tra phiên bản đã cài đặt

```powershell
cmake --version
ninja --version
g++ --version
```

## Làm thế nào để tải dự án

Tảu về và di chuyển vào thư mục dự án:

```powershell
git clone <repository-url>
cd <repo-folder>
```

## Làm thế nào để chạy dự án

### Cách 1: Dùng PowerShell script có sẵn

```powershell
.\build.ps1
```

Để build lại từ đầu:

```powershell
.\build.ps1 -Clean
```

Script này chỉ dùng để cấu hình và build dự án. Luồng `-Run` cũ đã được gỡ bỏ.

### Cách 2: Build thủ công bằng CMake và Ninja

```powershell
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
```

### Khởi chạy dự án

Sau khi build xong, file thực thi nằm tại:

```powershell
.\build\bmp24-processor.exe
```

Bộ phân tích dòng lệnh vẫn đang được hoàn thiện, nhưng cách dùng dự kiến sẽ giống như sau:

```powershell
.\build\bmp24-processor.exe -grayscale 0.5 input.bmp
.\build\bmp24-processor.exe -invert 0.5 --rotate 90 input.bmp
```

## Cấu trúc dự án

```text
project-root/
|-- build/                  # Các tệp được sinh ra từ hệ thống build
|-- include/                # Các tệp header
|   |-- bmp24.hpp
|   |-- cli_parser.hpp
|   |-- color_filter.hpp
|   |-- matrix.hpp
|   |-- transform.hpp
|   `-- util.hpp
|-- samples/                # Demo kết quả thu được
|   |-- bmp-source.bmp
|   |-- index.html
|   `-- style.css
|-- src/                    # Mã nguồn
|   |-- bmp24.cpp
|   |-- cli_parser.cpp
|   |-- color_filter.cpp
|   |-- main.cpp
|   |-- matrix.cpp
|   |-- transform.cpp
|   `-- util.cpp
|-- build.ps1               # Script build trên Windows
|-- CMakeLists.txt          # File cầu hình CMake
`-- README.md
```

## Một vài hạn chế
- Dự án hiện đã build được, nhưng một số hàm xử lý vẫn còn `TODO`
- Phần phân tích dòng lệnh chưa hoàn thiện
- Phần hiển thị hướng dẫn sử dụng chưa hoàn thiện
- Các bộ lọc màu và phép biến đổi vẫn đang được tiếp tục hoàn thiện
- Dự án hiện chỉ hỗ trợ ảnh BMP 24-bit
- Chưa có bộ kiểm thử tự động

## Tác giả
| Mã số sinh viên | Họ và tên | Ngành học |
|---|---|---|
| `6551020083` | Huỳnh Thái Tú | Kỹ thuật điện tử viễn thông |
| `6651071004` | Nguyễn Trần Duy Bảo | Công nghệ thông tin |
| `6651071013` | Nguyễn Thành Đạt | Công nghệ thông tin |
| `6651071099` | Trần Trọng Nguyên | Công nghệ thông tin |
| `6651071099` | Đoàn Xuân Tín | Công nghệ thông tin |