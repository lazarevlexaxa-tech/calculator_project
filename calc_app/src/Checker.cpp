#include "Checker.hpp"
#include "Logger.hpp"
#include <stdexcept>
#include <set>
#include <string>

void Checker::check(const CalculationData& data) const {
    // 1. Проверка поддерживаемых операций
    const std::set<std::string> validOps = {"add", "sub", "mul", "div", "pow", "fact"};
    if (validOps.find(data.operation) == validOps.end()) {
        Logger::getInstance().error("Unknown operation: " + data.operation);
        throw std::runtime_error("Unknown operation: " + data.operation);
    }

    // 2. Специфические проверки из ДЗ-1
    if (data.operation == "div" && data.b == 0) {
        Logger::getInstance().error("Validation failed: Division by zero");
        throw std::runtime_error("Division by zero");
    }

    if (data.operation == "pow" && data.b < 0) {
        Logger::getInstance().error("Validation failed: Negative exponent");
        throw std::runtime_error("Negative exponent not supported");
    }

    if (data.operation == "fact" && data.n < 0) {
        Logger::getInstance().error("Validation failed: Factorial of negative number");
        throw std::runtime_error("Factorial of negative number");
    }

    Logger::getInstance().info("Data validation passed for operation: " + data.operation);
}
