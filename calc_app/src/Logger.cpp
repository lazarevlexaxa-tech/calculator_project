#include "Logger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger() {
    // Проверяем, существует ли уже логгер с таким именем
    m_logger = spdlog::get("console");
    
    if (!m_logger) {
        // Если нет — создаем новый
        m_logger = spdlog::stdout_color_mt("console");
    }

    // Устанавливаем формат: [время] [уровень] сообщение
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
}

Logger::~Logger() {
    // В Singleton деструктор вызовется при завершении программы
    spdlog::drop_all();
}

void Logger::info(const std::string& message) {
    m_logger->info(message);
}

void Logger::error(const std::string& message) {
    m_logger->error(message);
}

void Logger::debug(const std::string& message) {
    m_logger->debug(message);
}
