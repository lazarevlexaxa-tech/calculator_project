#pragma once

#include "Checker.hpp"
#include "Parser.hpp"
#include "Printer.hpp"
#include <memory> // Нужно для unique_ptr
#include <string>

// ВМЕСТО инклюда пишем Forward Declaration:
class Calculator;

class Runner {
  public:
    // Правило 5:
    Runner();
    ~Runner();

    Runner(const Runner &) = default;
    Runner &operator=(const Runner &) = default;

    Runner(Runner &&) noexcept = default;
    Runner &operator=(Runner &&) noexcept = default;

    // Главный метод, который запускает весь цикл
    void run(int argc, char **argv);

  private:
    // Поля класса — компоненты системы
    Parser m_parser;
    Checker m_checker;
    std::unique_ptr<Calculator> m_calculator; // Теперь компилятор не ругается!
    Printer m_printer;
};
