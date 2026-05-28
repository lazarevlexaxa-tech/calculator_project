#include "Runner.hpp"
#include "Logger.hpp"
#include <iostream>
#include <math_lib/Calculator.hpp>
#include <stdexcept>

// В конструкторе добавляем math_lib:: к типу Calculator
Runner::Runner() = default;

Runner::~Runner() = default;

std::string Runner::make_cache_key(const CalculationData &data) const {
    return data.operation + ":" + std::to_string(data.first_number) + ":" +
           std::to_string(data.second_number);
}

void Runner::run(int argc, char **argv) {
    auto &logger = Logger::getInstance();
    logger.info("Application sequence started");

    if (!m_db.connect("host=localhost port=5432 dbname=test_db "
                      "user=cpp_developer password=14071979")) {
        logger.error("Failed to initialize database connection. Exiting.");
        throw std::runtime_error("Database connection error");
    }

    warm_up_cache();

    if (argc != 2) {
        logger.error("No input JSON provided in command line arguments");
        throw std::runtime_error("Usage: calculator <json_string>");
    }

    std::string jsonInput = argv[1];

    logger.info("Application sequence started with input: " + jsonInput);

    try {
        CalculationData data = m_parser.parse(jsonInput);
        // 1. Получаем статус от чекера вместо падения по throw
        int status = m_checker.check(data);

        std::string key = make_cache_key(data);
        int result = 0;

        // 2. Ищем в кэше. Если этот плохой пример уже вводили, execute вернет
        // true
        if (execute(data, key, result, status)) {
            logger.info("Shortcut executed: operation is already known as "
                        "invalid or cached.");
            // Если сохраненный статус был ошибочным, можно вывести сообщение об
            // ошибке
            return;
        }

        // 3. Если в кэше не нашли, смотрим на статус чекера
        if (status > 0) {
            logger.error("Validation failed with code " +
                         std::to_string(status) + ". Saving error to cache...");
            // Сохраняем ошибку в кэш и базу, чтобы больше не валидировать её в
            // будущем
            execute(data, key, result, status, true);
            std::cerr << "[Error]: Operation cannot be executed due to "
                         "validation code "
                      << status << std::endl;
            return;
        }

        // 4. Если статус 0 (все отлично) — считаем как обычно
        result = m_calculator.calculate(data);
        execute(data, key, result, 0, true); // Сохраняем успешный результат

        m_printer.print(data, result);
        logger.info("Application sequence finished successfully");

    } catch (const std::exception &e) {
        logger.error("Critical error during execution: " +
                     std::string(e.what()));
        std::cerr << "[Error]: " << e.what() << std::endl;
    }
}

void Runner::warm_up_cache() {
    auto &logger = Logger::getInstance();
    logger.info("Starting cache warm-up from PostgreSQL...");

    // 1. Делаем запрос на выборку всей истории
    auto res = m_db.exec_query(
        "SELECT num1, num2, op, result, status FROM operations_history;");

    if (!res) {
        logger.error("Cache warm-up failed: query error.");
        return;
    }

    // 2. Узнаем, сколько строк вернула база данных
    int rows = PQntuples(res.get());
    logger.info("Found " + std::to_string(rows) +
                " records in database history.");

    // 3. Читаем строки в цикле и забиваем наш быстрый кэш в RAM
    for (int i = 0; i < rows; ++i) {
        // Достаем данные из столбцов (индексация с 0: 0-num1, 1-num2, 2-op,
        // 3-result, 4-status)
        int n1 = std::stoi(PQgetvalue(res.get(), i, 0));
        int n2 = std::stoi(PQgetvalue(res.get(), i, 1));
        std::string op = PQgetvalue(res.get(), i, 2);
        int result = std::stoi(PQgetvalue(res.get(), i, 3));
        int status = std::stoi(PQgetvalue(res.get(), i, 4));

        // Собираем объект для хранения в оперативной памяти (RAM)
        auto entry = std::make_shared<CacheEntry>();
        entry->input_data.first_number = n1;
        entry->input_data.second_number = n2;
        entry->input_data.operation = op;
        entry->result = result;
        entry->status = status;

        // Генерируем для него правильный ключ кэша
        // Так как данные в базе уже сохранены в отсвапленном виде, ключ
        // сгенерируется идеально
        std::string key =
            op + ":" + std::to_string(n1) + ":" + std::to_string(n2);

        // Кладем в наши RAM-контейнеры
        storage_.push_back(entry); // Якорь в памяти
        cache_[key] = entry;       // Быстрый поиск (weak_ptr)
    }

    logger.info("Cache successfully warmed up with " + std::to_string(rows) +
                " entries.");
}

bool Runner::execute(const CalculationData &data, const std::string &key,
                     int &out_result, int our_status, bool is_write) {
    // 1. ПОИСК В КЭШЕ

    if (!is_write) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            if (auto cached_entry = it->second.lock()) {

                if (cached_entry->status > 0) {
                    Logger::getInstance().info(
                        "Cache Hit! This operation previously failed with "
                        "code: " +
                        std::to_string(cached_entry->status));
                    out_result = 0;
                    return true; // Говорим run(): "Всё найдено, прерываемся"
                }

                Logger::getInstance().info(
                    "Cache L1 Hit! Answer loaded from map.");

                out_result = cached_entry->result;
                // Отдаем сохраненный результат наружу в run()

                return true;
            }
        }
        return false;
    }

    auto new_entry = std::make_shared<CacheEntry>();
    new_entry->input_data = data;
    new_entry->result = out_result;
    new_entry->status = our_status;

    storage_.push_back(new_entry); // Сохраняем в вектор, чтобы жил в RAM
    cache_[key] = new_entry; // Сохраняем weak_ptr в мапу для быстрого поиска

    Logger::getInstance().info("Result saved to fast L1 cache (RAM).");

    // 2. ОТПРАВЛЯЮ РЕЗУЛЬТАТ В БАЗУ ДАННЫХ (ЖЕСТКИЙ ДИСК)
    // Формирую чистый SQL-запрос. Привожу int к строкам через
    // std::to_string
    std::string sql_query =
        "INSERT INTO operations_history (num1, num2, op, result, "
        "status) "
        "VALUES (" +
        std::to_string(data.first_number) + ", " +
        std::to_string(data.second_number) + ", " + "'" + data.operation +
        "', " // строку операции берем в одинарные кавычки для SQL
        + std::to_string(out_result) + ", " + std::to_string(our_status) +
        ");"; // Сюда улетит код ошибки
    Logger::getInstance().info("Sending new result to PostgreSQL...");

    // Вызываем нашу RAII-обертку. Возвращаемый уникальный указатель
    // автоматически удалит за собой память PGresult при выходе из этой
    // функции!
    auto res = m_db.exec_query(sql_query);

    if (res) {
        Logger::getInstance().info(
            "Successfully persisted data to PostgreSQL.");
    } else {
        Logger::getInstance().error("Failed to write data to database!");
    }

    return false;
}