#pragma once
#include "Parser.hpp"
#include "Checker.hpp"
#include "Printer.hpp"
#include "../../math_lib/include/Calculator.hpp"
#include <string>

class Runner {
public:
    // Главный метод, который запускает весь цикл
    void run(const std::string& jsonInput);

private:
    // Поля класса — компоненты системы
    Parser m_parser;
    Checker m_checker;
    Calculator m_calculator;
    Printer m_printer;
};
