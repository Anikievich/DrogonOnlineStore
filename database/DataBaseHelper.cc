
#include "DataBaseHelper.h"

  DatabaseHelper *DatabaseHelper::getInstance() {
     std::lock_guard<std::mutex> lock(mutex_);
     if (instance_ == nullptr) {
         instance_ = new DatabaseHelper("postgres://localhost/db");
     }
     return instance_;
}