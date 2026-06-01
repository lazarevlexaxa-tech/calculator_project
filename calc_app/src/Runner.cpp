#include "Runner.hpp"
#include "Logger.hpp"
#include <iostream>
#include <math_lib/Calculator.hpp>
#include <stdexcept>

// В конструкторе добавляем math_lib:: к типу Calculator
Runner::Runner() = default;

Runner::~Runner() = default;

void Runner::run(int argc, char **argv) {
    auto &logger = Logger::getInstance();
    logger.info("Application sequence started");

    if (argc != 2) {
        logger.error("No input JSON provided in command line arguments");
        throw std::runtime_error("Usage: calculator <json_string>");
    }

    std::string jsonInput = argv[1];

    logger.info("Application sequence started with input: " + jsonInput);

    try {
        CalculationData data = m_parser.parse(jsonInput);
        m_checker.check(data);

        int result = m_calculator.calculate(data);
        m_printer.print(data, result);
        logger.info("Application sequence finished successfully");

    } catch (const std::exception &e) {
        logger.error("Critical error during execution: " +
                     std::string(e.what()));
        std::cerr << "[Error]: " << e.what() << std::endl;
    }
}
