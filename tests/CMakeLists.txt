# Создаем исполняемый файл для тестов
add_executable(unit_tests test_main.cpp)

# Линкуем GTest и твою математическую библиотеку
target_link_libraries(unit_tests
    PRIVATE
        GTest::gtest_main
        math_lib
)

# Чтобы тесты запускались через вкладку Testing в VS Code
include(GoogleTest)
gtest_discover_tests(unit_tests)
