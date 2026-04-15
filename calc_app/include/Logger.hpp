#pragma once
#include <string>
#include <memory>

// Forward Declaration
namespace spdlog { class logger; }

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Удаляем возможность копирования Singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void info(const std::string& message);
    void error(const std::string& message);
    void debug(const std::string& message);

private:
    Logger(); 
    ~Logger();

    std::shared_ptr<spdlog::logger> m_logger;
};
