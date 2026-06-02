#pragma once

#include "Checker.hpp"
#include "DbWrapper.hpp"
#include "Parser.hpp"
#include "Printer.hpp"
#include <math_lib/Calculator.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// ВМЕСТО инклюда пишем Forward Declaration:
namespace math_lib {
class Calculator;
}

class Runner {
  public:
    // Правило 5:
    Runner();
    ~Runner();

    Runner(const Runner &) = default;
    Runner &operator=(const Runner &) = default;

    Runner(Runner &&) noexcept = default;
    Runner &operator=(Runner &&) noexcept = default;

    // Главный метод, который запускает весь цикл
    void run(int argc, char **argv);

  private:
    struct CacheEntry {
        CalculationData input_data; // Исходные параметры
        int result;                 // Результат вычислений
        int status;                 // Статус (0 - успех, номер ошибки)
    };
    std::unordered_map<std::string, std::weak_ptr<CacheEntry>>
        cache_; // быстрый кеш

    std::vector<std::shared_ptr<CacheEntry>>
        storage_; // хранилище - медленный кеш

    void warm_up_cache();

    std::string make_cache_key(const CalculationData &data)
        const; // функция для генерации простого ключа

    bool execute(const CalculationData &data, const std::string &key,
                 int &out_result, int status,
                 bool is_write = false); // метод поиска и сохранения в кеш

    Parser m_parser;
    Checker m_checker;
    math_lib::Calculator m_calculator;
    Printer m_printer;
    DbWrapper m_db;
};
