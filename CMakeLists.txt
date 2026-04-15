cmake_minimum_required(VERSION 3.14)
project(CalculatorProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Поиск внешних библиотек (JSON, Logger, GTest)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

# 2. Подключаем наши модули
# Сначала библиотеку, так как приложение от неё зависит
add_subdirectory(math_lib)
add_subdirectory(calc_app)
add_subdirectory(tests)

# 3. Глобальные настройки (Clang-Tidy)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

