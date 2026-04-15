#include "Parser.hpp"
#include "Logger.hpp"
#include <stdexcept>

CalculationData Parser::parse(const std::string& jsonInput) {
    try {
        // Парсим строку в объект json
        auto j = nlohmann::json::parse(jsonInput);
        
        CalculationData data;
        
        // Извлекаем обязательное поле операции
        if (j.contains("operation")) {
            data.operation = j.at("operation").get<std::string>();
        } else {
            throw std::runtime_error("JSON missing 'operation' field");
        }

        // Логика извлечения аргументов зависит от твоего формата JSON.
        // Допустим, формат: {"operation": "add", "args": [10, 20]} или {"operation": "fact", "n": 5}
        
        if (data.operation == "fact") {
            data.n = j.at("n").get<int>();
        } else {
            data.a = j.at("a").get<int>();
            data.b = j.at("b").get<int>();
        }

        Logger::getInstance().info("JSON parsed successfully");
        return data;
        
    } catch (const nlohmann::json::exception& e) {
        Logger::getInstance().error("JSON parsing error: " + std::string(e.what()));
        throw std::runtime_error("Invalid JSON format");
    }
}
