#pragma once
#include <string>

// Структура с понятными именами полей
struct CalculationData {
    std::string operation;
    int first_number;  // Вместо a
    int second_number; // Вместо b
    int factorial_n;   // Вместо n (указываем конкретный смысл)
};

class Parser {
  public:
    // Правило пяти
    Parser() = default;
    ~Parser() = default;
    Parser(const Parser &) = default;
    Parser &operator=(const Parser &) = default;
    Parser(Parser &&) noexcept = default;
    Parser &operator=(Parser &&) noexcept = default;

    // Метод принимает строку. nlohmann/json будет только внутри .cpp
    CalculationData parse(const std::string &jsonInput);
};
