#include <gtest/gtest.h>
#include "../math_lib/include/Calculator.hpp"
#include <stdexcept>

// Группа тестов для базовой арифметики
TEST(CalculatorTest, BasicOperations) {
    Calculator calc;
    EXPECT_EQ(calc.add(2, 3), 5);
    EXPECT_EQ(calc.sub(10, 4), 6);
    EXPECT_EQ(calc.mul(3, 3), 9);
    EXPECT_EQ(calc.div(10, 2), 5);
}

// Тест на возведение в степень и факториал
TEST(CalculatorTest, AdvancedOperations) {
    Calculator calc;
    EXPECT_EQ(calc.pow(2, 3), 8);
    EXPECT_EQ(calc.fact(5), 120);
    EXPECT_EQ(calc.fact(0), 1); // Граничный случай
}

// Тест на исключения (деление на ноль)
TEST(CalculatorTest, ThrowsExceptionOnDivisionByZero) {
    Calculator calc;
    // Проверяем, что вылетает именно runtime_error
    EXPECT_THROW(calc.div(10, 0), std::runtime_error);
}

// Тест на переполнение (Overflow)
TEST(CalculatorTest, ThrowsExceptionOnOverflow) {
    Calculator calc;
    // Попробуем сложить очень большие числа
    EXPECT_THROW(calc.add(2147483647, 1), std::overflow_error);
    // Факториал большого числа точно вызовет переполнение int
    EXPECT_THROW(calc.fact(20), std::overflow_error);
}

// Тест на некорректные данные для факториала
TEST(CalculatorTest, ThrowsExceptionOnNegativeFactorial) {
    Calculator calc;
    EXPECT_THROW(calc.fact(-5), std::runtime_error);
}
