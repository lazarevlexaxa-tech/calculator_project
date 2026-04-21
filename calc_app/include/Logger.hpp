#pragma once
#include <memory>
#include <string>

class Logger {
  public:
    static Logger &getInstance() {
        static Logger instance;
        return instance;
    }

    // Правило пяти
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger &&) = delete;

    void info(const std::string &message);
    void error(const std::string &message);
    void debug(const std::string &message);

  private:
    Logger();

    // Используем Pimpl: создаем скрытую структуру,
    // которая будет объявлена только в .cpp файле
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;
};
