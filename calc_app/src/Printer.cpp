#include "Printer.hpp"
#include "Logger.hpp"
#include <iomanip>
#include <iostream>

void Printer::print(const CalculationData &data, int result) const {
    std::cout << "--- Calculation Result ---" << std::endl;

    if (data.operation == "fact") {
        // Используем factorial_n вместо n
        std::cout << "Operation: " << data.operation << "(" << data.factorial_n
                  << ") = " << result << std::endl;
    } else if (data.operation == "pow") {
        // Используем first_number и second_number
        std::cout << "Operation: " << data.first_number << " ^ "
                  << data.second_number << " = " << result << std::endl;
    } else {
        std::string op_symbol;
        if (data.operation == "add")
            op_symbol = "+";
        else if (data.operation == "sub")
            op_symbol = "-";
        else if (data.operation == "mul")
            op_symbol = "*";
        else if (data.operation == "div")
            op_symbol = "/";

        // Используем first_number и second_number
        std::cout << "Operation: " << data.first_number << " " << op_symbol
                  << " " << data.second_number << " = " << result << std::endl;
    }

    std::cout << "--------------------------" << std::endl;

    Logger::getInstance().info("Final result displayed to user.");
}
