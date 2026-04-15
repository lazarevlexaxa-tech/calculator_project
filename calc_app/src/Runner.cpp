#include "Runner.hpp"
#include "Logger.hpp"
#include <iostream>
#include <stdexcept>

void Runner::run(const std::string& jsonInput) {
    auto& logger = Logger::getInstance();
    logger.info("Application sequence started");

    try {
        // 1. Парсинг
        CalculationData data = m_parser.parse(jsonInput);

        // 2. Валидация
        m_checker.check(data);

        // 3. Расчёт
        int result = 0;
        if (data.operation == "add") result = m_calculator.add(data.a, data.b);
        else if (data.operation == "sub") result = m_calculator.sub(data.a, data.b);
        else if (data.operation == "mul") result = m_calculator.mul(data.a, data.b);
        else if (data.operation == "div") result = m_calculator.div(data.a, data.b);
        else if (data.operation == "pow") result = m_calculator.pow(data.a, data.b);
        else if (data.operation == "fact") result = m_calculator.fact(data.n);

        // 4. Вывод
        m_printer.print(data, result);

        logger.info("Application sequence finished successfully");

    } catch (const std::exception& e) {
        // Ловим любую ошибку (парсинг, валидация, переполнение)
        logger.error("Critical error during execution: " + std::string(e.what()));
        
        // Выводим понятное сообщение пользователю в stderr
        std::cerr << "[Error]: " << e.what() << std::endl;
    }
}
