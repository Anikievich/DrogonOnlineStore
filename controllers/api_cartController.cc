#include "api_cartController.h"

using namespace api;

// Add definition of your processing function here
void
cartController::add(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Cart::AddDTO &&pNewCart) {

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto resultCartID = db->exec("SELECT id FROM basket WHERE user_id = '" + std::to_string(pNewCart.userID) + "'");
    pNewCart.cartID = resultCartID.at(0).at("id").get<int>().value();

    auto result = db->exec("INSERT INTO basket_device (device_id, basket_id) VALUES('"
                           + std::to_string(pNewCart.deviceID) + "', '"
                           + std::to_string(pNewCart.cartID ) + "')");
    db->commit();

    delete db;
    db = nullptr;
    Json::Value ret;
    ret["massage"] = (" Cart "  + std::to_string(pNewCart.cartID) + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}

void cartController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                            Cart::GetAllDTO &&pNewCart) {
    Json::Value ret;

    int limit;
    int page;
    (pNewCart.limit) ? limit = pNewCart.limit : limit = 9;
    (pNewCart.page) ? page = pNewCart.page : page = 1;
    int offset = page * limit - limit;

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto result = db->exec("SELECT * FROM basket_device OFFSET '" + (std::to_string(offset)) + "' LIMIT '" + (std::to_string(limit)) + "'");
    db->commit();
    delete db;
    db = nullptr;
    for (const auto& d : result) {
        Json::Value  r;
        r["id"] =  d.at("id").get<int>().value();
        r["device_id"] = d.at("device_id").get<int>().value();
        r["basket_id"] =  d.at("basket_id").get<int>().value();
        ret.append(r);
    }

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void cartController::getUserCart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                 Cart::GetUserCartDTO &&pNewCart) {
    Json::Value ret;

    int limit;
    int page;
    (pNewCart.limit) ? limit = pNewCart.limit : limit = 9;
    (pNewCart.page) ? page = pNewCart.page : page = 1;
    const int offset = page * limit - limit;

    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto resultCartID = db->exec("SELECT id FROM basket WHERE user_id = '" + std::to_string(pNewCart.userID) + "'");
    pNewCart.cartID = resultCartID.at(0).at("id").get<int>().value();

    auto resultDeviceID = db->exec("SELECT device_id FROM basket_device WHERE basket_id = '"+std::to_string (pNewCart.cartID)+"'");

    pqxx::result result;
    for (int i = offset; i < limit; ++i) {
        result = db->exec("SELECT * FROM device WHERE id = '"+ std::to_string (resultDeviceID.at(i).at("device_id").get<int>().value()) +"'");
        Json::Value r;
        r["id"] =  result.at(0).at("id").get<unsigned int>().value();
        r["name"]= result.at(0).at("name").get<const char*>().value();
        r["price"] =  result.at(0).at("price").get<float>().value();
        r["rating"]= result.at(0).at("rating").get<float>().value();
        r["img"] =  result.at(0).at("img").get<const char*>().value();
        r["typeId"]= result.at(0).at("type").get<int>().value();
        r["brandId"] =  result.at(0).at("brand").get<int>().value();
        ret.append(r);
        db->commit();
    }
    delete db;
    db = nullptr;
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void cartController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Cart::RemoveDTO &&pNewCart) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    auto resultCartID = db->exec("SELECT id FROM basket WHERE user_id = '" + std::to_string(pNewCart.userID) + "'");
    pNewCart.cartID = resultCartID.at(0).at("id").get<int>().value();

    auto result = db->exec("DELETE FROM basket_device WHERE device_id = '"+ std::to_string(pNewCart.deviceID) + "' AND basket_id = '" + std::to_string(pNewCart.cartID ) + "' )");
    db->commit();
    delete db;
    db = nullptr;
    Json::Value ret;
    ret["massage"] = (" Cart "  + std::to_string(pNewCart.cartID) + " add ");

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);
}
