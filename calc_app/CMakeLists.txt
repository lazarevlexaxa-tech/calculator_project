# Версия CMake, имя проекта, язык программирования и его стандарт.

cmake_minimum_required(VERSION 3.14)
project(Calculator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 1. Ищу установленные библиотеки в системе автоматически. К библиотеке math_lib прописываю путь вручную

find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../math_lib math_lib_build)

# 2. включаю автопроверку на каждой строке через clang-tidy

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")


# 3. Объявление исполняемого файла и придание названия программы с указанием файлов для неё, затем соединяю мою программу (название должно совпасть с названием выше) к math_lib и остальным файлам. (в сложных проектах сборка может быть из большого количества файлов и не для всех из них я бы хотел подключать определенные репозитории, поэтому прописываю вручную)

add_executable(calculator main.cpp)

target_link_libraries(calculator
    PRIVATE
        math_lib
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        GTest::gtest_main
)


# 4. Правила установки для команды install. Помогает запускать файл как отдельную программу, а не как файл внутри папки build

install(TARGETS calculator DESTINATION bin)

# 5. Clang-Format (ТЗ требует автоматическое форматирование)
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
add_custom_target(format
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    COMMENT "Formatting code with clang-format"
)
