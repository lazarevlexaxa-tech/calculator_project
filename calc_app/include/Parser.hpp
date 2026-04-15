#pragma once
#include <string>
#include <nlohmann/json.hpp>

// Структура для хранения распарсенных данных
struct CalculationData {
    std::string operation;
    int a;
    int b;
    int n; // для факториала, например
};

class Parser {
public:
    // Метод принимает сырую JSON-строку и возвращает структуру с данными
    CalculationData parse(const std::string& jsonInput);
};
