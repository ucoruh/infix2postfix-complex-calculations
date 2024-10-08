cmake_minimum_required(VERSION 3.10)

# Proje adı ve versiyonu
project(InfixToPostfixCalculator VERSION 1.0)

# C++ standardı
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Statik derleme ayarları - Windows ve Linux için
if(MSVC)
    # Windows (MSVC) için statik bağlantı
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    # GCC/Clang (Linux/WSL) için statik bağlantı
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

# Include ve kaynak dosyalarının yollarını belirtin
include_directories(include)
add_executable(InfixToPostfixCalculator src/main.cpp src/infix_calculator.cpp)

# Hedef tanımları ve platform ayarları
if(WIN32)
    target_compile_definitions(InfixToPostfixCalculator PRIVATE _USE_MATH_DEFINES)
endif()

# Derleme seçenekleri
if(MSVC)
    target_compile_options(InfixToPostfixCalculator PRIVATE /W4)
else()
    target_compile_options(InfixToPostfixCalculator PRIVATE -Wall -Wextra -pedantic)
endif()

# Kurulum hedefi
install(TARGETS InfixToPostfixCalculator
    RUNTIME DESTINATION bin  # Kurulum dizini prefix'e göre otomatik olacak
)
