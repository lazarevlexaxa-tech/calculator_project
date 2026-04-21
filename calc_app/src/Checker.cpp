#include "Checker.hpp"
#include "Logger.hpp"
#include <set>
#include <stdexcept>
#include <string>

void Checker::check(const CalculationData &data) const {
    // 1. Проверка поддерживаемых операций
    static const std::set<std::string> validOps = {"add", "sub", "mul",
                                                   "div", "pow", "fact"};

    if (validOps.find(data.operation) == validOps.end()) {
        Logger::getInstance().error("Unknown operation: " + data.operation);
        throw std::runtime_error("Unknown operation: " + data.operation);
    }

    // 2. Специфические проверки (с новыми именами полей)

    // Проверка деления на ноль (вместо data.b)
    if (data.operation == "div" && data.second_number == 0) {
        Logger::getInstance().error("Validation failed: Division by zero");
        throw std::runtime_error("Division by zero");
    }

    // Проверка отрицательной степени (вместо data.b)
    if (data.operation == "pow" && data.second_number < 0) {
        Logger::getInstance().error("Validation failed: Negative exponent");
        throw std::runtime_error("Negative exponent not supported");
    }

    // Проверка факториала (вместо data.n)
    if (data.operation == "fact" && data.factorial_n < 0) {
        Logger::getInstance().error(
            "Validation failed: Factorial of negative number");
        throw std::runtime_error("Factorial of negative number");
    }

    Logger::getInstance().info("Data validation passed for operation: " +
                               data.operation);
}
