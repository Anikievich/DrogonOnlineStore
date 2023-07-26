
#include "DataBaseHelper.h"
#include <unistd.h>

std::mutex DatabaseHelper::m_mutex;
bool DatabaseHelper::fl = false;

std::condition_variable DatabaseHelper::m_condition;
std::queue<std::shared_ptr<pqxx::connection>> DatabaseHelper::m_pool;
//void DatabaseHelper::createPool()
//{
//   std::lock_guard<std::mutex> locker_( mutex_ );
//
//    for (auto i=0; i < POOL_SIZE; i++) {
//        m_pool.emplace(std::make_shared<pqxx::connection>("postgres://localhost/db"));
//   }
//}
DatabaseHelper *DatabaseHelper::getInstance() {
    std::unique_lock<std::mutex> locker_( m_mutex );
    if (!fl) {
        fl = true;
        // createPool();
        //std::unique_lock<std::mutex> locker_( m_mutex );
LOG_DEBUG<<"DB1";

        for (auto i=0; i < POOL_SIZE; ++i) {
            auto conn_ = std::make_shared<pqxx::connection>("postgres://localhost/db");
            LOG_DEBUG<<"LOOP";
             m_pool.emplace(conn_);
        //m_pool.emplace(conn_);
        }
        LOG_DEBUG<<"DB2";
        //instance_
    }
    while (m_pool.empty()) {
        LOG_DEBUG<<"WAIT!!!";
        m_condition.wait(locker_);
        LOG_DEBUG<<"GO";
    }
    auto c_ = m_pool.front();
    LOG_DEBUG<<c_.get();
    // immediately pop as we will use it now
    if ((c_->is_open())) {
        LOG_DEBUG<<"DB is open";
        }
        else {
        LOG_DEBUG<<"DB is not open";
        }
    m_pool.pop();
    LOG_DEBUG<<"POP";
    auto* instance_ = new DatabaseHelper(c_);

    return instance_;
}

DatabaseHelper::DatabaseHelper(std::shared_ptr<pqxx::connection> &conn_) :
        conn_(conn_), txn_(reinterpret_cast<pqxx::connection&>(*conn_)) {
    if ((conn_->is_open())) {
        LOG_DEBUG<<"DB is open";
    }
    else {
        LOG_DEBUG<<"DB is not open";
    }
    //  return conn_;

   // if (c_.is_open()) {
     //   LOG_ERROR<<"DB is open";
    //}
    //else {
       // LOG_ERROR<<"DB is not open";
    //}
}

void DatabaseHelper::freeConnection(std::shared_ptr<pqxx::connection> const &conn_)
{
    std::unique_lock<std::mutex> lock_(m_mutex);
    LOG_DEBUG<<"FREE1";
    // push a new connection into a pool
    m_pool.push(conn_);
    LOG_DEBUG<<"FREE2";
    // unlock mutex
    lock_.unlock();
    LOG_DEBUG<<"FREE3";
    // notify one of thread that is waiting
    m_condition.notify_one();
}

DatabaseHelper::~DatabaseHelper() {

    txn_.commit();
    freeConnection(conn_);
}

pqxx::result DatabaseHelper::exec(std::string_view query, std::string const& desc ) {
    LOG_DEBUG<<"DB3.1";
    //LOG_DEBUG<<;
   // m_mutex.lock();
   std::cout<< std::this_thread::get_id();
    //usleep(2000000);
    pqxx::result e;
   //std::thread t([&]() {
         e = txn_.exec(query, desc);
    //});
   // t.join();
    LOG_DEBUG<<"DB3.2";
   // m_mutex.unlock();
    return e;
}

pqxx::result DatabaseHelper::exec2(std::string_view query, std::string const& desc ) {
    LOG_DEBUG<<"EXEC1.1";
    //LOG_DEBUG<<;
    // m_mutex.lock();
    std::cout<< std::this_thread::get_id();


    pqxx::result e;
    std::thread t([&]() {
        usleep(6000000);
        e = txn_.exec(query, desc);
    });
    t.join();
    LOG_DEBUG<<"EXEC1.2";
    // m_mutex.unlock();
    return e;
}