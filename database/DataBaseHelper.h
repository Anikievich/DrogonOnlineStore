
#ifndef ONLINESTORE_DATABASEHELPER_H
#define ONLINESTORE_DATABASEHELPER_H

#include <pqxx/pqxx>
//#include <spdlog/spdlog.h>
#include <mutex>
#include "pqxx/types.hxx"
#include "Mutex.h"
#include <trantor/utils/Logger.h>
#include <memory>
#include <pqxx/connection>
#include <pqxx/connection.hxx>
#include <condition_variable>
#include <queue>
#include <thread>
//class DatabaseHelper;
//static DatabaseHelper* instance_;
//static std::mutex mutex_;


class DatabaseHelper{
private:
   // pqxx::connection c_;
    pqxx::work txn_;
    std::shared_ptr<pqxx::connection> conn_;
    //pqxx::connection;
   // std::shared_ptr<pqxx::connection> connection();
    void freeConnection(std::shared_ptr<pqxx::connection> const &conn_);
   // static void createPool();

    static std::mutex m_mutex;
    static std::condition_variable m_condition;
    static std::queue<std::shared_ptr<pqxx::connection>> m_pool;

    static const int POOL_SIZE = 10;
    //DatabaseHelper* instance_;
private:
    static bool fl;
    //static std::mutex m_mutex;

protected:
    //static void createPool();
    explicit DatabaseHelper(std::shared_ptr<pqxx::connection> &conn_) ;



public:
    ~DatabaseHelper();
    DatabaseHelper(DatabaseHelper& other) = delete;

    void operator=(const DatabaseHelper&) = delete;

     static DatabaseHelper* getInstance();

    void commit() {
        txn_.exec("commit;");
        txn_.exec("begin;");
    }

    pqxx::result exec(std::string_view query, std::string const& desc = std::string{}) ;
    pqxx::result exec2(std::string_view query, std::string const& desc = std::string{}) ;

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
