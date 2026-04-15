#pragma once
#include "Parser.hpp" // Чтобы принимать структуру CalculationData

class Printer {
public:
    // Передаем структуру с входными данными и итоговый результат
    void print(const CalculationData& data, int result) const;
};
