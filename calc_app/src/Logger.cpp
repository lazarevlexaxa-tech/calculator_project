#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h> // Инклюд только здесь!

// Определяем скрытую структуру
struct Logger::Impl {
    std::shared_ptr<spdlog::logger> spd_logger;
};

Logger::Logger() : m_pimpl(std::make_unique<Impl>()) {
    m_pimpl->spd_logger = spdlog::stdout_color_mt("console");
}

Logger::~Logger() = default;

void Logger::info(const std::string &message) {
    m_pimpl->spd_logger->info(message);
}

void Logger::error(const std::string &message) {
    m_pimpl->spd_logger->error(message);
}

void Logger::debug(const std::string &message) {
    m_pimpl->spd_logger->debug(message);
}
