#pragma once
#include <string>

// Подключаем внешнюю библиотеку
#include <math_lib/Calculator.hpp>

class Parser {
  public:
    Parser() = default;
    ~Parser() = default;
    Parser(const Parser &) = default;
    Parser &operator=(const Parser &) = default;
    Parser(Parser &&) noexcept = default;
    Parser &operator=(Parser &&) noexcept = default;

    // Добавляем префикс math_lib:: к возвращаемому типу
    CalculationData parse(const std::string &jsonInput);
};
