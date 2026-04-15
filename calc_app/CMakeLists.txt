# Перечисляем все файлы реализации из папки src
add_executable(calculator
    src/main.cpp
    src/Logger.cpp
    src/Parser.cpp
    src/Checker.cpp
    src/Printer.cpp
    src/Runner.cpp
)

# Указываем путь к заголовкам приложения
target_include_directories(calculator PRIVATE include)

# Связываем приложение с нашей библиотекой и внешними зависимостями
target_link_libraries(calculator
    PRIVATE
        math_lib
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)

