# BMP24 Processor

Repository: [TTNguyen2505/bmp24-processor](https://github.com/TTNguyen2505/bmp24-processor)

`BMP24 Processor` is a C++17 command-line tool for loading 24-bit BMP images, applying color filters, and performing geometric transformations. The project is built with CMake and Ninja on Windows.

## Course Information
- Course name: `IT1.109.3 - Data Structures and Algorithms`
- Assignment title: `Course Project`
- Instructor: `M.Sc. Tran Thi Dung`
- Institution: `University of Transport and Communications, Campus in Ho Chi Minh City`

## Features
- Load 24-bit BMP images from disk
- Save processed BMP images to a new file
- Apply color filters
  - Grayscale
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

### Check installed versions

```powershell
cmake --version
ninja --version
g++ --version
```

## Clone

```powershell
git clone https://github.com/TTNguyen2505/bmp24-processor.git
cd bmp24-processor
```

## Build

### Option 1: Use the provided PowerShell script

```powershell
.\build.ps1
```

To rebuild from scratch:

```powershell
.\build.ps1 -Clean
```

The script configures the project in `build/`, builds it, and copies `bmp24-processor.exe` to the repository root so you can run it without entering the build folder.

### Option 2: Build manually with CMake and Ninja

```powershell
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
```

After a manual build, the executable is available at `.\build\bmp24-processor.exe`.

## Run

After using `.\build.ps1`, run the program from the repository root:

```powershell
.\bmp24-processor.exe
```

Example commands:

```powershell
.\bmp24-processor.exe -grayscale 0.5 input.bmp
.\bmp24-processor.exe -invert 0.5 --rotate 90 input.bmp
.\bmp24-processor.exe --translate 100 50 --scale 1.5 1.5 input.bmp -o output.bmp
```

## Project Structure

```text
project-root/
|-- include/                # Public headers
|   |-- app/
|   |   |-- cli_parser.hpp
|   |   `-- pipeline.hpp
|   |-- core/
|   |   |-- color.hpp
|   |   |-- color_filter.hpp
|   |   |-- image.hpp
|   |   `-- transform.hpp
|   |-- io/
|   |   |-- bmp24.hpp
|   |   |-- bmp_io.hpp
|   |   `-- file_system.hpp
|   `-- math/
|       |-- coordinate.hpp
|       |-- geometry.hpp
|       |-- interpolation.hpp
|       `-- matrix.hpp
|-- samples/
|   |-- bmp-source.bmp
|   |-- index.html
|   `-- style.css
|-- src/
|   |-- app/
|   |   |-- cli_parser.cpp
|   |   `-- pipeline.cpp
|   |-- core/
|   |   |-- color.cpp
|   |   |-- color_filter.cpp
|   |   |-- image.cpp
|   |   `-- transform.cpp
|   |-- io/
|   |   |-- bmp24.cpp
|   |   |-- bmp_io.cpp
|   |   `-- file_system.cpp
|   |-- math/
|   |   |-- coordinate.cpp
|   |   |-- geometry.cpp
|   |   |-- interpolation.cpp
|   |   `-- matrix.cpp
|   `-- main.cpp
|-- build.ps1
|-- format.ps1
|-- CMakeLists.txt
`-- README.md
```

## Notes
- `build.ps1` copies the executable to the repository root after a successful build.
- The project currently targets 24-bit BMP images.

## Authors
| Student ID | Full Name | Major |
|---|---|---|
| `6551020083` | Huynh Thai Tu | Electronics and Telecommunications Engineering |
| `6651071004` | Nguyen Tran Duy Bao | Information Technology |
| `6651071013` | Nguyen Thanh Dat | Information Technology |
| `6651071099` | Tran Trong Nguyen | Information Technology |
| `6651071099` | Doan Xuan Tin | Information Technology |
