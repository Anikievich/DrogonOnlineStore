#include "api_ratingController.h"

using namespace api;

// Add definition of your processing function here
void ratingController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                              Rating::CreateDTO &&pNewRating) {
    DatabaseHelper* db = DatabaseHelper::getInstance();

    auto resultRating = db->exec("INSERT INTO rating (user, device_id, rating) VALUES('"
                           + std::to_string(pNewRating.userID) + "', '"
                           + std::to_string(pNewRating.deviceID ) + "', '"+
                           std::to_string(pNewRating.rate) + "')");
    db->commit();
    auto resultAVG = db->exec ("SELECT AVG(rate) FROM rating WHERE device_id = '" + std::to_string(pNewRating.deviceID ) + "' ");
    db->commit();

    auto result = db->exec ("UPDATE device SET rating = '" +
            std::to_string(resultAVG.at(0).at("rate").get<float>().value()) + "' WHERE id = '" +
            std::to_string(pNewRating.deviceID) + "'");
    db->commit();

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Rate "  + std::to_string(pNewRating.deviceID) + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}

void ratingController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                              Rating::GetAllDTO &&pNewRating) {
    Json::Value ret;

    int limit;
    int page;
    (pNewRating.limit) ? limit = pNewRating.limit : limit = 9;
    (pNewRating.page) ? page = pNewRating.page : page = 1;
    int offset = page * limit - limit;

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("SELECT * FROM rating OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    db->commit();

    for (const auto& d : result) {
        Json::Value  r;
        r["id"] =  d.at("id").get<int>().value();
        r["device_id"] = d.at("device_id").get<int>().value();
        r["user_id"] =  d.at("user_id").get<int>().value();
        r["rate"] =  d.at("rate").get<int>().value();
        ret.append(r);
    }

    delete db;
    db = nullptr;

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void ratingController::getOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                              Rating::GetOneDTO &&pNewRating) {
    Json::Value ret;
    DatabaseHelper* db = DatabaseHelper::getInstance();

    auto result = db->exec("SELECT rate FROM rating WHERE device_id = '"+
            std::to_string (pNewRating.deviceID) +"' AND user_id = '"+ std::to_string (pNewRating.userID) +"'");
    db->commit();

    delete db;
    db = nullptr;

    ret["rate"] =  result.at(0).at("rate").get<unsigned int>().value();
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void ratingController::update(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                              Rating::UpdateDTO &&pNewRating) {

    if(pNewRating.rate == std::nullopt) {
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::badRequest("no rating")));
        return;
    }
    DatabaseHelper *db = DatabaseHelper::getInstance();
    auto result = db->exec("UPDATE rate SET rate = '" + std::to_string(pNewRating.rate.value())+ " WHERE device_id = '"+
                           std::to_string (pNewRating.deviceID) +"' AND user_id = '"+ std::to_string (pNewRating.userID) +"''");
    db->commit();

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Rate "  +  std::to_string(pNewRating.deviceID) + " update ");
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}
