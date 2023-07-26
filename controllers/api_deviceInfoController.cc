#include "api_deviceInfoController.h"

using namespace api;

void api::deviceInfoController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                       DeviceInfo::CreateDTO &&pNewDevice) {

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto resultInfo = db->exec("INSERT INTO device_info (device_id, title, description) VALUES('"
                               +  std::to_string (pNewDevice.deviceID)  + "', '"
                               + pNewDevice.title + "','"
                               + pNewDevice.description + "')");
    db->commit();

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Person "  + std::to_string (pNewDevice.deviceID) + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);

}

void api::deviceInfoController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, DeviceInfo::GetAllDTO &&pNewDevice) {
    Json::Value ret;

    int limit;
    int page;

    (pNewDevice.limit) ? limit = pNewDevice.limit : limit = 9;
    (pNewDevice.page) ? page = pNewDevice.page : page = 1;
    int offset = page * limit - limit;

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("SELECT * FROM device_info OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    delete db;
    db = nullptr;

    for (const auto& d : result) {

        Json::Value  r;
        r["device_id"] =  d.at("device_id").get<unsigned int>().value();
        r["title"]= d.at("title").get<const char*>().value();
        r["description"] =  d.at("description").get<const char*>().value();

        ret.append(r);
    }

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::deviceInfoController::getOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                   int id) {

    Json::Value ret;
    DatabaseHelper* db = DatabaseHelper::getInstance();

    auto result = db->exec("SELECT * FROM device_info WHERE id = '"+ std::to_string (id) +"'");
    db->commit();
    delete db;
    db = nullptr;

    ret["device_id"] =  result.at(0).at("device_id").get<unsigned int>().value();
    ret["title"]= result.at(0).at("title").get<const char*>().value();
    ret["description"] =  result.at(0).at("description").get<const char*>().value();

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::deviceInfoController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                   int id)  {
    Json::Value ret;
    try {
        DatabaseHelper *db = DatabaseHelper::getInstance();
        auto result = db->exec("DELETE FROM device_info WHERE id = '" + std::to_string(id) + "' ");
        db->commit();
        delete db;
        db = nullptr;

        ret["message"] = "Device_info has been deleted";
        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k200OK);
        callback(res);
    }
    catch (const std::runtime_error &e){
        callback( ErrorHandlingMiddleware::errorReturn(ApiError::badRequest(e.what())));
    }

}

void api::deviceInfoController::update(const drogon::HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback,
                                       DeviceInfo::UpdateDTO &&pNewDevice) {

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec(DeviceInfoUpdateDecorator::UpdateDevice(pNewDevice));
    db->commit();
    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Device Info "  +  std::to_string(pNewDevice.id) + " update ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);

}
