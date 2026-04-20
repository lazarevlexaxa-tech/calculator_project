#pragma once
#include "Parser.hpp" // Чтобы знать о структуре CalculationData

class Checker {
  public:
    // Правило пяти (Rule of Five)
    Checker() = default;
    virtual ~Checker() = default;

    Checker(const Checker &other) = default;
    Checker &operator=(const Checker &other) = default;

    Checker(Checker &&other) noexcept = default;
    Checker &operator=(Checker &&other) noexcept = default;

    // Проверяет данные. Если что-то не так — кидает исключение.
    void check(const CalculationData &data) const;
};
