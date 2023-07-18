#include "typeController.h"
#include <trantor/utils/Logger.h>

void api::typeController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                       Type::CreateDTO &&pNewType) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("INSERT INTO type (name) VALUES('" + (pNewType.name) + "')");
    db->commit();

    Json::Value ret;
    ret["massage"] = (" Person "  + pNewType.name + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}


void api::typeController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                       Type::GetAllDTO &&pNewType)  {
    Json::Value ret;

    int limit;
    int page;
    (pNewType.limit) ? limit = pNewType.limit : limit = 9;
    (pNewType.page) ? page = pNewType.page : page = 1;
    int offset = page * limit - limit;


    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db-> exec("SELECT id, name FROM type OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    db->commit();

    for (const auto& d : result) {
        Json::Value  r;
        r["id"] =  d.at("id").get<int>().value();
        r["name"]= d.at("name").get<const char*>().value();
        ret.append(r);
    }


    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::typeController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                 int id)  {
    Json::Value ret;
    try {
        DatabaseHelper *db = DatabaseHelper::getInstance();
        auto result = db->exec("DELETE FROM type WHERE id = '" + std::to_string(id) + "' ");
        db->commit();
        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k200OK);
        callback(res);
    }
    catch (const std::runtime_error &e){
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::badRequest(e.what())));
    }

}

void api::typeController::update(const drogon::HttpRequestPtr &req,
                                  std::function<void(const HttpResponsePtr &)> &&callback,
                                  Type::UpdateDTO &&pNewType) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("UPDATE type SET name = '" + (pNewType.name) + "' WHERE id = '" + std::to_string (pNewType.id) + "'");
    db->commit();

    Json::Value ret;
    ret["massage"] = (" Person "  + pNewType.name + " updated ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}