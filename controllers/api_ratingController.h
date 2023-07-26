#pragma once

#include <drogon/HttpController.h>
#include "../entity/Rating.h"
#include "../database/DataBaseHelper.h"
#include "../Middleware/ErrorHandlingMiddleware.h"
using namespace drogon;

namespace api
{
class ratingController : public drogon::HttpController<ratingController>
{
  public:
    METHOD_LIST_BEGIN
        METHOD_ADD(ratingController::create, "/", Post,  "authFilter"); // path is /api/cartController/{arg2}/{arg1}
        METHOD_ADD(ratingController::getAll, "/", Get,  "adminRoleFilter");
        METHOD_ADD(ratingController::getOne, "/user", Get, "authFilter");
        METHOD_ADD(ratingController::update, "/", Put, "authFilter");

    METHOD_LIST_END
    void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Rating::CreateDTO &&pNewRating);
    void getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Rating::GetAllDTO &&pNewRating);
    void getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Rating::GetOneDTO &&pNewRating);
    void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, Rating::UpdateDTO &&pNewRating);
};
}
