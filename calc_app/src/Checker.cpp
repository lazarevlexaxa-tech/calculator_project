#include "Checker.hpp"
#include "Logger.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>

int Checker::check(CalculationData &data) {
    // 1. Проверка поддерживаемых операций
    static const std::set<std::string> validOps = {"add", "sub", "mul",
                                                   "div", "pow", "fact"};

    if (validOps.find(data.operation) == validOps.end()) {
        Logger::getInstance().error("Unknown operation: " + data.operation);
        return 4;
    }

    // 2. Специфические проверки (с новыми именами полей)

    // Проверка деления на ноль (вместо data.b)
    if (data.operation == "div" && data.second_number == 0) {
        Logger::getInstance().error("Validation failed: Division by zero");
        return 1;
    }

    // Проверка отрицательной степени (вместо data.b)
    if (data.operation == "pow" && data.second_number < 0) {
        Logger::getInstance().error("Validation failed: Negative exponent");
        return 2;
    }

    // Проверка факториала (вместо data.n)
    if (data.operation == "fact" && data.factorial_n < 0) {
        Logger::getInstance().error(
            "Validation failed: Factorial of negative number");
        return 3;
    }

    Logger::getInstance().info("Data validation passed for operation: " +
                               data.operation);

    if (data.operation == "add" || data.operation == "mul") {
        if (data.second_number > data.first_number) {
            std::swap(data.second_number, data.first_number);
            Logger::getInstance().info("Arguments swapped for canonical form");
        }
    }

    return 0; // ошибок нет
}
