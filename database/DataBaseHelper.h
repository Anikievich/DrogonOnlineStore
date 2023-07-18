
#ifndef ONLINESTORE_DATABASEHELPER_H
#define ONLINESTORE_DATABASEHELPER_H

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>
#include "pqxx/types.hxx"
#include "Mutex.h"
#include <trantor/utils/Logger.h>

//class DatabaseHelper;
//static DatabaseHelper* instance_;
//static std::mutex mutex_;


class DatabaseHelper{
private:
    pqxx::connection c_;
    pqxx::work txn_;

private:


protected:

    explicit DatabaseHelper(const char* url) :
            c_(url ? url : ""), txn_(c_) {
        if (c_.is_open()) {
            LOG_ERROR<<"DB is open";
        }
        else {
            LOG_ERROR<<"DB is not open";
        }
    }

    ~DatabaseHelper() {
        txn_.commit();
    }

public:
    DatabaseHelper(DatabaseHelper& other) = delete;

    void operator=(const DatabaseHelper&) = delete;

     static DatabaseHelper* getInstance();

    void commit() {
        txn_.exec("commit;");
        txn_.exec("begin;");
    }

    pqxx::result exec(std::string_view query, std::string const& desc = std::string{}) {
        return txn_.exec(query, desc);
    }

    pqxx::result exec(std::stringstream const& query, std::string const& desc = std::string{}) {
        return txn_.exec(query.str(), desc);
    }

    pqxx::result exec0(std::string_view query, std::string const& desc = std::string{}) {
        return txn_.exec0(query.data(), desc);
    }

    pqxx::row exec1(std::string_view query, std::string const& desc = std::string{}) {
        return txn_.exec1(query.data(), desc);
    }

    pqxx::result exec_n(size_t rows, std::string_view query, std::string const& desc = std::string{}) {
        return txn_.exec_n(rows, query.data(), desc);
    }

    template <typename...Args>
    pqxx::result exec_params(std::string const &query, Args &&... args) {
        return txn_.exec_params(query, std::forward<Args>(args)...);
    }

    template<typename...Args>
    pqxx::result exec_params0(std::string const& query, Args &&... args) {
        return txn_.exec_params0(query, std::forward<Args>(args)...);
    }

    template<typename...Args>
    pqxx::row exec_params1(std::string const& query, Args &&... args) {
        return txn_.exec_params1(query, std::forward<Args>(args)...);
    }

    template<typename...Args>
    pqxx::row exec_params_n(std::size_t rows, std::string const& query, Args &&... args) {
        return txn_.exec_params_n(rows, query, std::forward<Args>(args)...);
    }

    template<typename T>
    std::string quote(const T& str) {
        return txn_.quote(str);
    }

    template<typename...TYPE>
    auto stream(std::string_view query) {
        return txn_.stream<TYPE...>(query);
    }
};




#endif //ONLINESTORE_DATABASEHELPER_H
