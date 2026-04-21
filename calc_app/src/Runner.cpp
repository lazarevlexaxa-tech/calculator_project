#include "Runner.hpp"
#include "../../math_lib/include/Calculator.hpp" // Добавляем инклюд здесь
#include "Logger.hpp"
#include <iostream>
#include <stdexcept>

// Реализуем конструктор, создавая объект Calculator в куче
Runner::Runner() : m_calculator(std::make_unique<Calculator>()) {
}

// Деструктор определяем здесь, где компилятор уже видит полный Calculator
Runner::~Runner() = default;

void Runner::run(const std::string &jsonInput) {
    auto &logger = Logger::getInstance();
    logger.info("Application sequence started");

    try {
        CalculationData data = m_parser.parse(jsonInput);
        m_checker.check(data);

        int result = 0;
        // Теперь используем -> для m_calculator, так как это unique_ptr
        if (data.operation == "add") {
            result = m_calculator->add(data.first_number, data.second_number);
        } else if (data.operation == "sub") {
            result = m_calculator->sub(data.first_number, data.second_number);
        } else if (data.operation == "mul") {
            result = m_calculator->mul(data.first_number, data.second_number);
        } else if (data.operation == "div") {
            result = m_calculator->div(data.first_number, data.second_number);
        } else if (data.operation == "pow") {
            result = m_calculator->pow(data.first_number, data.second_number);
        } else if (data.operation == "fact") {
            result = m_calculator->fact(data.factorial_n);
        }

        m_printer.print(data, result);
        logger.info("Application sequence finished successfully");

    } catch (const std::exception &e) {
        logger.error("Critical error during execution: " +
                     std::string(e.what()));
        std::cerr << "[Error]: " << e.what() << std::endl;
    }
}
