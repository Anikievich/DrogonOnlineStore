//#pragma once

#ifndef ONLINESTORE_TYOECONTROLLER_H
#define ONLINESTORE_TYOECONTROLLER_H

#include <drogon/HttpController.h>
#include "../entity/Type.h"
#include "../database/DataBaseHelper.h"
#include "../Middleware/ErrorHandlingMiddleware.h"
using namespace drogon;

namespace api {
    class typeController : public drogon::HttpController<typeController> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            // METHOD_ADD(type::get, "/{2}/{1}", Get); // path is /type/{arg2}/{arg1}
            // METHOD_ADD(type::your_method_name, "/{1}/{2}/list", Get); // path is /type/{arg1}/{arg2}/list
            // ADD_METHOD_TO(type::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
            METHOD_ADD(typeController::create, "/", Post, "adminRoleFilter"); // path is /brand/{arg1}/{arg2}/list
            METHOD_ADD(typeController::getAll, "/", Get);
            METHOD_ADD(typeController::remove, "/id={1}", Delete, "adminRoleFilter");
            METHOD_ADD(typeController::update, "/", Put, "adminRoleFilter");
        METHOD_LIST_END
        // your declaration of processing function maybe like this:
        //
        // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
        void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Type::CreateDTO &&pNewType);
        void getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Type::GetAllDTO &&pNewType);
        void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int id);
        void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Type::UpdateDTO &&pNewType);
    };
}
#endif //ONLINESTORE_TYOECONTROLLER_H