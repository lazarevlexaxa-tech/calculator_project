#include "DbWrapper.hpp"
#include "Logger.hpp"
#include <iostream>

bool DbWrapper::connect(const std::string &conn_str) {
    auto &logger = Logger::getInstance();

    // 1. Устанавливаем соединение через сишную функцию PQconnectdb
    PGconn *raw_conn = PQconnectdb(conn_str.c_str());

    // 2. Сразу оборачиваем сырой указатель в unique_ptr! С этого момента память
    // под контролем.
    conn_.reset(raw_conn);

    // 3. Проверяем, успешно ли подключились
    if (PQstatus(conn_.get()) != CONNECTION_OK) {
        logger.error("Database connection failed: " +
                     std::string(PQerrorMessage(conn_.get())));
        return false;
    }

    logger.info("Successfully connected to PostgreSQL database.");
    return true;
}
std::unique_ptr<PGresult, DbWrapper::ResultDeleter>
DbWrapper::exec_query(const std::string &query) {
    auto &logger = Logger::getInstance();

    if (!conn_) {
        logger.error("Attempted to execute query without active connection.");
        return nullptr;
    }

    // 1. Отправляем запрос через сишную PQexec
    PGresult *raw_res = PQexec(conn_.get(), query.c_str());

    // 2. Сразу оборачиваем в умный указатель
    std::unique_ptr<PGresult, ResultDeleter> res(raw_res);

    // 3. Проверяем статус выполнения запроса
    ExecStatusType status = PQresultStatus(res.get());
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
        logger.error("SQL Error: " + std::string(PQerrorMessage(conn_.get())));
        return nullptr;
    }

    return res; // Возвращаем умный указатель наружу
}