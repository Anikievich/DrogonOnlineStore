//
// Created by aniki on 5/9/23.
//

#include "ErrorHandlingMiddleware.h"

using namespace drogon;

auto ErrorHandlingMiddleware::errorReturn(const ApiError &err)->HttpResponsePtr {
    Json::Value ret;
    ret["massage"] = err.massage;
    ret["status"] = err.status;
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode((HttpStatusCode)err.status);
   // res->setBody(err.massage);
    return res;
}
