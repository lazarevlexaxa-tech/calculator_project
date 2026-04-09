# Версия CMake, имя проекта, язык программирования и его стандарт.

cmake_minimum_required(VERSION 3.14)
project(Calculator CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 1. Подключаю модуль CMake для работы со внешними модулями, означаю что буду использовать репозиторий math_lib и затем ищу его, начиная от текущей папки. Последняя строка приводит слова в действия, заставляя идти по указанному пути, проверять наличие файла и подключать его к основному проекту.

include(FetchContent)

FetchContent_Declare(
  math_lib
  GIT_REPOSITORY https://gitflic.ru/project/lazarevlexa/mymathlib.git
  GIT_TAG master
)

FetchContent_MakeAvailable(math_lib)


# 2. включаю автопроверку на каждой строке через clang-tidy

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")


# 3. Объявление исполняемого файла и придание названия программы с указанием файлов для неё, затем соединяю мою программу (название должно совпасть с названием выше) к math_lib. (в сложных проектах сборка может быть из большого количества файлов и не для всех из них я бы хотел подключать определенные репозитории, поэтому прописываю вручную)

add_executable(calculator main.cpp)

target_link_libraries(calculator PRIVATE math_lib)


# 4. Правила установки для команды install. Помогает запускать файл как отдельную программу, а не как файл внутри папки build

install(TARGETS calculator DESTINATION bin)

# 5. Clang-Format (ТЗ требует автоматическое форматирование)
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
add_custom_target(format
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    COMMENT "Formatting code with clang-format"
)
