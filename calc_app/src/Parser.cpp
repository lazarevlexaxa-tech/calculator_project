#include "Parser.hpp"
#include "Logger.hpp"
#include <nlohmann/json.hpp> // Подключаем здесь, чтобы скрыть от пользователя
#include <stdexcept>

CalculationData Parser::parse(const std::string &jsonInput) {
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

        // Извлекаем данные, используя новые имена полей
        if (data.operation == "fact") {
            if (j.contains("n")) {
                data.factorial_n = j.at("n").get<int>();
            } else {
                throw std::runtime_error(
                    "JSON missing 'n' field for factorial");
            }
        } else {
            if (j.contains("a") && j.contains("b")) {
                data.first_number = j.at("a").get<int>();
                data.second_number = j.at("b").get<int>();
            } else {
                throw std::runtime_error("JSON missing 'a' or 'b' fields");
            }
        }

        Logger::getInstance().info("JSON parsed successfully");
        return data;

    } catch (const nlohmann::json::exception &e) {
        Logger::getInstance().error("JSON parsing error: " +
                                    std::string(e.what()));
        throw std::runtime_error("Invalid JSON format: " +
                                 std::string(e.what()));
    }
}
