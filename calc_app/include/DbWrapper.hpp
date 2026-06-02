#pragma once

#include <memory>
#include <postgresql/libpq-fe.h> // Сишный заголовок PostgreSQL
#include <string>

class DbWrapper {
  private:
    // Кастомные деструкторы-функторы для Си-структур (RAII)
    struct ConnDeleter {
        void operator()(PGconn *conn) const {
            if (conn) {
                PQfinish(
                    conn); // Закрывает соединение и освобождает память C-API
            }
        }
    };

    struct ResultDeleter {
        void operator()(PGresult *res) const {
            if (res) {
                PQclear(res); // Освобождает память, выделенную под ответ СУБД
            }
        }
    };

    std::unique_ptr<PGconn, ConnDeleter> conn_;

  public:
    DbWrapper() = default;
    ~DbWrapper() = default; // std::unique_ptr всё очистит автоматически

    // Метод для подключения к базе
    bool connect(const std::string &conn_str);

    // Метод для отправки запросов (INSERT, SELECT и т.д.)
    // Возвращает умный unique_ptr, защищая от утечек памяти
    std::unique_ptr<PGresult, ResultDeleter>
    exec_query(const std::string &query);
};