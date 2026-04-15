#include "Runner.hpp"
#include "Logger.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    auto& logger = Logger::getInstance();
    logger.info("Calculator project started");

    // Проверяем, передал ли пользователь JSON-строку
    if (argc < 2) {
        logger.error("No input arguments provided");
        std::cerr << "Usage: " << argv[0] << " '<json_string>'" << std::endl;
        std::cerr << "Example: " << argv[0] << " '{\"operation\": \"add\", \"a\": 10, \"b\": 20}'" << std::endl;
        return 1;
    }

    // Аргумент argv[1] — это и есть наша JSON-строка
    std::string inputJson = argv[1];

    // Создаем Runner и запускаем приложение
    Runner app;
    app.run(inputJson);

    logger.info("Calculator project shutting down");
    return 0;
}
