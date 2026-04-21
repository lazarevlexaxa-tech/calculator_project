#include "Runner.hpp"
#include "Logger.hpp"
#include <iostream>
#include <stdexcept>

void Runner::run(const std::string &jsonInput) {
    auto &logger = Logger::getInstance();
    logger.info("Application sequence started");

    try {
        // 1. Парсинг
        CalculationData data = m_parser.parse(jsonInput);

        // 2. Валидация
        m_checker.check(data);

        // 3. Расчёт (заменяем a, b, n на новые имена)
        int result = 0;
        if (data.operation == "add") {
            result = m_calculator.add(data.first_number, data.second_number);
        } else if (data.operation == "sub") {
            result = m_calculator.sub(data.first_number, data.second_number);
        } else if (data.operation == "mul") {
            result = m_calculator.mul(data.first_number, data.second_number);
        } else if (data.operation == "div") {
            result = m_calculator.div(data.first_number, data.second_number);
        } else if (data.operation == "pow") {
            result = m_calculator.pow(data.first_number, data.second_number);
        } else if (data.operation == "fact") {
            result = m_calculator.fact(data.factorial_n);
        }

        // 4. Вывод
        m_printer.print(data, result);

        logger.info("Application sequence finished successfully");

    } catch (const std::exception &e) {
        logger.error("Critical error during execution: " +
                     std::string(e.what()));
        std::cerr << "[Error]: " << e.what() << std::endl;
    }
}
