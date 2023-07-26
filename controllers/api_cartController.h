#pragma once

#include <drogon/HttpController.h>
#include "../entity/Cart.h"
#include "../database/DataBaseHelper.h"
#include "../Middleware/ErrorHandlingMiddleware.h"

using namespace drogon;

namespace api
{
class cartController : public drogon::HttpController<cartController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
        METHOD_ADD(cartController::add, "/", Post,  "authFilter"); // path is /api/cartController/{arg2}/{arg1}
        METHOD_ADD(cartController::getAll, "/", Get,  "adminRoleFilter");
        METHOD_ADD(cartController::getUserCart, "/user", Post, "authFilter");
        METHOD_ADD(cartController::remove, "/", Post, "");
    // METHOD_ADD(cartController::get, "/{2}/{1}", Get); // path is /api/cartController/{arg2}/{arg1}
    // METHOD_ADD(cartController::your_method_name, "/{1}/{2}/list", Get); // path is /api/cartController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(cartController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    void add(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Cart::AddDTO &&pNewCart);
    void getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Cart::GetAllDTO &&pNewCart);
    void getUserCart(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Cart::GetUserCartDTO &&pNewCart);
    void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Cart::RemoveDTO &&pNewCart);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
}
