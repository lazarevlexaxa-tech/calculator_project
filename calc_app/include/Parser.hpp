#pragma once
#include <nlohmann/json.hpp>
#include <string>

// Структура для хранения распарсенных данных
struct CalculationData {
    std::string operation;
    int a;
    int b;
    int n; // для факториала, например
};

class Parser {
  public:
    // Правило 5:
    Parser() = default;
    ~Parser() = default;

    Parser(const Parser &) = default;
    Parser &operator=(const Parser &) = default;

    Parser(Parser &&) noexcept = default;
    Parser &operator=(Parser &&) noexcept = default;

    // Метод принимает сырую JSON-строку и возвращает структуру с данными
    CalculationData parse(const std::string &jsonInput);
};
