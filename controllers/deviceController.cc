#include "deviceController.h"
#include <trantor/utils/Logger.h>
#include <jwt-cpp/jwt.h>

void api::deviceController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                   Device::CreateDTO &&pNewDevice) {
   // usleep(6000000);
        DatabaseHelper* db = DatabaseHelper::getInstance();
        LOG_DEBUG<<"LIambda";
    pqxx::result result;

    /*std::thread t([&]()  { LOG_DEBUG<<"LIambda1";
         usleep(2000000);
         result = db->exec("INSERT INTO device (name, price, img, type, brand) VALUES('"
                + (pNewDevice.name) + "', '"
                + std::to_string(pNewDevice.price) + "', '"
                + (pNewDevice.image) + "', '"
                + std::to_string(pNewDevice.typeID) + "', '"
                + std::to_string(pNewDevice.brandID) + "')");
    });*/

    result = db->exec2("INSERT INTO device (name, price, img, type, brand) VALUES('"
                       + (pNewDevice.name) + "', '"
                       + std::to_string(pNewDevice.price) + "', '"
                       + (pNewDevice.image) + "', '"
                       + std::to_string(pNewDevice.typeID) + "', '"
                       + std::to_string(pNewDevice.brandID) + "')");
    //db->commit();
    LOG_DEBUG<<"LIambda END";
   // auto single = result.inserted_oid();
    //LOG_ERROR<< single;
    //LOG_DEBUG<< single;
  //  int &&a1 = 5;
  //  int &a2 = a1;
    LOG_DEBUG<<"ResultDevice";
   // usleep(6000000);
        auto resultDeviceId = db->exec2("SELECT id FROM device WHERE name = '" + (pNewDevice.name) + "'");
        pNewDevice.infoDeviceID = resultDeviceId.at(0).at("id").get<int>().value();

        auto resultInfo = db->exec("INSERT INTO device_info (device_id, title, description) VALUES('"
                +  std::to_string (pNewDevice.infoDeviceID)  + "', '"
                + pNewDevice.infoTitle + "','"
                + pNewDevice.infoDescription + "')");
        db->commit();
    LOG_DEBUG<<"Callback";
   // t.join();
        delete db;
        db = nullptr;
    LOG_DEBUG<<"Callback";

        Json::Value ret;
        ret["massage"] = (" Person "  + pNewDevice.name + " add ");

        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k201Created);
        callback(res);
        return;
 //   }
  //  catch (ForbiddenException &ex) {
  //      callback(ex.getRespons());
  //  }


}

void api::deviceController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Device::GetAllDTO &&pNewDevice) {
    Json::Value ret;

    int limit;
    int page;

    (pNewDevice.limit) ? limit = pNewDevice.limit : limit = 9;
    (pNewDevice.page) ? page = pNewDevice.page : page = 1;
    int offset = page * limit - limit;
    LOG_DEBUG<<limit;
    LOG_DEBUG<<page;
    LOG_DEBUG<<pNewDevice.typeID;
    LOG_DEBUG<<pNewDevice.brandID;
    DatabaseHelper* db = DatabaseHelper::getInstance();
    pqxx::result result;


    if(!pNewDevice.typeID && !pNewDevice.brandID){

          result = db->exec("SELECT * FROM device OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    }else if(pNewDevice.typeID && !pNewDevice.brandID){


        result = db->exec("SELECT * FROM device WHERE type = '"+ std::to_string (pNewDevice.typeID) + "'OFFSET '"
                + (std::to_string(offset)) + "' LIMIT '"
                + (std::to_string(limit)) + "'");

    }else if(!pNewDevice.typeID && pNewDevice.brandID){

        result = db->exec("SELECT * FROM device WHERE brand = '"
                + std::to_string (pNewDevice.brandID) + "'OFFSET '"
                + (std::to_string(offset)) + "' LIMIT '"
                + (std::to_string(limit)) + "'");

    }else if(pNewDevice.typeID && pNewDevice.brandID){

        result = db->exec("SELECT * FROM device WHERE type = '"
                + std::to_string (pNewDevice.typeID) + "' AND brand = '"
                + std::to_string (pNewDevice.brandID) + "' OFFSET '"
                + (std::to_string(offset)) + "' LIMIT '"
                + (std::to_string(limit)) + "'");

    }
    db->commit();

    LOG_DEBUG<<result.at(0).at("name").get<const char*>().value();
    for (const auto& d : result) {

        Json::Value  r;
        r["id"] =  d.at("id").get<unsigned int>().value();
        r["name"]= d.at("name").get<const char*>().value();
        r["price"] =  d.at("price").get<float>().value();
        r["rating"]= d.at("rating").get<float>().value();
        r["img"] =  d.at("img").get<const char*>().value();
        r["typeId"]= d.at("type").get<int>().value();
        r["brandId"] =  d.at("brand").get<int>().value();
        ret.append(r);

    }
    delete db;
    db = nullptr;
 // auto df =  picojson::string_type;
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::deviceController::getOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                   int id) {

    Json::Value ret;
    DatabaseHelper* db = DatabaseHelper::getInstance();
    LOG_DEBUG<<"DB3";
    auto result = db->exec("SELECT * FROM device WHERE id = '"+ std::to_string (id) +"'");
    LOG_DEBUG<<"DB4";
    db->commit();
    LOG_DEBUG<<"DB5";
    auto resultId = db->exec("SELECT * FROM device_info WHERE device_id = '"+ std::to_string (id) +"'");
    db->commit();
    for(const auto& d : result ){
        Json::Value  r;
        r["id"] =  d.at("id").get<unsigned int>().value();
        r["name"]= d.at("name").get<const char*>().value();
        r["price"] =  d.at("price").get<float>().value();
        r["rating"]= d.at("rating").get<float>().value();
        r["img"] =  d.at("img").get<const char*>().value();
        r["typeId"]= d.at("type").get<int>().value();
        r["brandId"] =  d.at("brand").get<int>().value();
        for(const auto& v : resultId ){
            Json::Value  l;
            l["id"] = v.at("id").get<unsigned int>().value();
            l["title"] = v.at("title").get<const char*>().value();
            l["description"] = v.at("description").get<const char*>().value();
            l["deviceId"] = v.at("device_id").get<unsigned int>().value();
            r["info"].append(l);
        }
        ret.append(r);
    }
    delete db;
    db = nullptr;

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::deviceController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                  int id)  {
    Json::Value ret;
    try {
        DatabaseHelper *db = DatabaseHelper::getInstance();
        auto result = db->exec("DELETE FROM device WHERE id = '" + std::to_string(id) + "' ");
        db->commit();
        ret["message"] = "Device has been deleted";
        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k200OK);
        delete db;
        db = nullptr;
        callback(res);
    }
    catch (const std::runtime_error &e){
        callback( ErrorHandlingMiddleware::errorReturn(ApiError::badRequest(e.what())));
    }

}

void api::deviceController::update(const drogon::HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback,
                                   Device::UpdateDTO &&pNewDevice) {

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec(DeviceUpdateDecorator::UpdateDevice(pNewDevice));
    db->commit();
    delete db;
    db = nullptr;

    Json::Value ret;
    ret["massage"] = (" Person "  +  std::to_string(pNewDevice.id) + " update ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);

}