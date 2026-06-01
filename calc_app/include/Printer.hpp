#pragma once
#include "Parser.hpp" // Чтобы принимать структуру CalculationData

class Printer {
  public:
    // Правило 5:
    Printer() = default;
    ~Printer() = default;

    Printer(const Printer &) = default;
    Printer &operator=(const Printer &) = default;

    Printer(Printer &&) noexcept = default;
    Printer &operator=(Printer &&) noexcept = default;

    // Передаем структуру с входными данными и итоговый результат
    void print(const CalculationData &data, int result) const;
};
