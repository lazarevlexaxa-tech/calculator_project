#pragma once
#include "Parser.hpp" // Чтобы знать о структуре CalculationData

class Checker {
public:
    // Проверяет данные. Если что-то не так — кидает исключение.
    void check(const CalculationData& data) const;
};
