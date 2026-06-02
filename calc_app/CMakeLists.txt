# Перечисляем все файлы реализации из папки src
add_executable(calculator
    src/main.cpp
    src/Logger.cpp
    src/Parser.cpp
    src/Checker.cpp
    src/Printer.cpp
    src/Runner.cpp
    src/DbWrapper.cpp 
)

find_package(PostgreSQL REQUIRED)

# Указываем путь к заголовкам приложения
target_include_directories(calculator PRIVATE include ${PostgreSQL_INCLUDE_DIRS})

# Связываем приложение с нашей ВНЕШНЕЙ библиотекой и остальными зависимостями
target_link_libraries(calculator
    PRIVATE
        math_lib::math_lib  # Изменено: теперь через пространство имен
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        ${PostgreSQL_LIBRARIES}
)
