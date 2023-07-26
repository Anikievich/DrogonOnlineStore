#include "brandController.h"
#include <thread>

void api::brandController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                        Brand::CreateDTO &&pNewBrand) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("INSERT INTO brand (name) VALUES('" + (pNewBrand.name) + "')");
    db->commit();

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Person "  + pNewBrand.name + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}

void api::brandController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                        Brand::GetAllDTO &&pNewBrand)  {
    Json::Value ret;

    int limit;
    int page;
    (pNewBrand.limit) ? limit = pNewBrand.limit : limit = 9;
    (pNewBrand.page) ? page = pNewBrand.page : page = 1;
    int offset = page * limit - limit;

    DatabaseHelper* db =  DatabaseHelper::getInstance();
    auto result = db->exec ("SELECT id, name FROM brand OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    db->commit();

    for (const auto& d : result) {
        Json::Value  r;
        r["id"] =  d.at("id").get<int>().value();
        r["name"]= d.at("name").get<const char*>().value();
        ret.append(r);
    }
    //result = db->exec("select count(*) from type");

    delete db;
    db = nullptr;

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}


void api::brandController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                  int id)  {
      Json::Value ret;
    try {
         DatabaseHelper *db = DatabaseHelper::getInstance();
         auto result = db->exec("DELETE FROM brand WHERE id = '" + std::to_string(id) + "' ");
         db->commit();
        delete db;
        db = nullptr;

        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k200OK);
        callback(res);
    }
    catch (const std::runtime_error &e){
        callback( ErrorHandlingMiddleware::errorReturn(ApiError::badRequest(e.what())));
    }
}

void api::brandController::update(const drogon::HttpRequestPtr &req,
                                  std::function<void(const HttpResponsePtr &)> &&callback,
                                  Brand::UpdateDTO &&pNewBrand) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("UPDATE brand SET name = '" + (pNewBrand.name) + "' WHERE id = '" + std::to_string (pNewBrand.id) + "'");
    db->commit();
    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Person "  + pNewBrand.name + " updated ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}

