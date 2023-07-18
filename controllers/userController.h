#pragma once

#include <drogon/HttpController.h>
#include <trantor/utils/Logger.h>
#include <bcrypt/BCrypt.hpp>
#include <jwt-cpp/jwt.h>
#include "../Middleware/ErrorHandlingMiddleware.h"
#include "../entity/User.h"
#include "../database/DataBaseHelper.h"
#include "../utils/jwtService.h"
#include "../decorators/UpdateDecorators.h"

using namespace drogon;

namespace api{
    class userController : public drogon::HttpController<userController> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            // METHOD_ADD(user::get, "/{2}/{1}", Get); // path is /user/{arg2}/{arg1}
            // METHOD_ADD(user::your_method_name, "/{1}/{2}/list", Get); // path is /user/{arg1}/{arg2}/list
            // ADD_METHOD_TO(user::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
            METHOD_ADD(userController::registration, "/registration", Post);
            METHOD_ADD(userController::login, "/login", Post);
            METHOD_ADD(userController::check, "/auth", Get, "authFilter"); // path is /user/{arg2}/{arg1};
            METHOD_ADD(userController::remove, "/id={1}", Delete, "authFilter");
            METHOD_ADD(userController::update, "/", Put, "authFilter");
        METHOD_LIST_END


        void registration(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, User::RegistrationDTO &&pNewUser);
        void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,  User::LoginDTO &&pNewUser);
        void check(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, User::CheckDTO &&pNewUser);
        void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int id);
        void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, User::UpdateDTO &&pNaewUser);
    };
}