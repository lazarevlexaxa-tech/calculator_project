#include "Printer.hpp"
#include "Logger.hpp"
#include <iostream>
#include <iomanip> // Для красоты, если захочешь выравнивание

void Printer::print(const CalculationData& data, int result) const {
    std::cout << "--- Calculation Result ---" << std::endl;
    
    if (data.operation == "fact") {
        // Красивый вывод для факториала: fact(5) = 120
        std::cout << "Operation: " << data.operation << "(" << data.n << ") = " << result << std::endl;
    } else if (data.operation == "pow") {
        // Вывод для степени: 2 ^ 3 = 8
        std::cout << "Operation: " << data.a << " ^ " << data.b << " = " << result << std::endl;
    } else {
        // Для остальных: 10 + 20 = 30
        std::string op_symbol;
        if (data.operation == "add") op_symbol = "+";
        else if (data.operation == "sub") op_symbol = "-";
        else if (data.operation == "mul") op_symbol = "*";
        else if (data.operation == "div") op_symbol = "/";
        
        std::cout << "Operation: " << data.a << " " << op_symbol << " " << data.b << " = " << result << std::endl;
    }
    
    std::cout << "--------------------------" << std::endl;

    Logger::getInstance().info("Final result displayed to user.");
}
