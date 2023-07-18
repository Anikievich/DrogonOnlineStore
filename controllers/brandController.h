#pragma once

#include <drogon/HttpController.h>
#include "../entity/Brand.h"
#include "../database/DataBaseHelper.h"
#include "../Middleware/ErrorHandlingMiddleware.h"
using namespace drogon;

namespace api {
    class brandController : public drogon::HttpController<brandController> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            // METHOD_ADD(brand::get, "/{2}/{1}", Get); // path is /brand/{arg2}/{arg1}
            // METHOD_ADD(brand::your_method_name, "/{1}/{2}/list", Get); // path is /brand/{arg1}/{arg2}/list
            // ADD_METHOD_TO(brand::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
              METHOD_ADD(brandController::create, "/", Post, "adminRoleFilter"); // path is /brand/{arg1}/{arg2}/list
              METHOD_ADD(brandController::getAll, "/", Get);
              METHOD_ADD(brandController::remove, "/id={1}", Delete, "adminRoleFilter");// path is /brand/{arg1}/{arg2}/list
              METHOD_ADD(brandController::update, "/", Put, "adminRoleFilter");
        METHOD_LIST_END
        // your declaration of processing function maybe like this:
        // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
        // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
         void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Brand::CreateDTO &&pNewBrand);
         void getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Brand::GetAllDTO &&pNewBrand);
         void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int id);
         void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Brand::UpdateDTO &&pNewBrand);
    };
}