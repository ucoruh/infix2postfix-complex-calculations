cmake_minimum_required(VERSION 3.10)

# Proje adı ve versiyonu
project(InfixToPostfixCalculator VERSION 1.0)

# C++ standardı
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

# Kurulum hedefi (install)
install(TARGETS InfixToPostfixCalculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
