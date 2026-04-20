#pragma once
#include "../../math_lib/include/Calculator.hpp"
#include "Checker.hpp"
#include "Parser.hpp"
#include "Printer.hpp"
#include <string>

class Runner {
  public:
    // Правило 5:
    Runner() = default;
    ~Runner() = default;

    Runner(const Runner &) = default;
    Runner &operator=(const Runner &) = default;

    Runner(Runner &&) noexcept = default;
    Runner &operator=(Runner &&) noexcept = default;

    // Главный метод, который запускает весь цикл
    void run(const std::string &jsonInput);

  private:
    // Поля класса — компоненты системы
    Parser m_parser;
    Checker m_checker;
    Calculator m_calculator;
    Printer m_printer;
};
