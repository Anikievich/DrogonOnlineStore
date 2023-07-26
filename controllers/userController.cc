#include "userController.h"

// Add definition of your processing function here

void api::userController::registration(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, User::RegistrationDTO &&pNewUser){

   if(pNewUser.email.empty() || pNewUser.password.empty()){
       callback(ErrorHandlingMiddleware::errorReturn(ApiError::badRequest("Incorrect email or password.")));
       return;
   }
    DatabaseHelper* db = DatabaseHelper::getInstance();
    pqxx::result resultEmail = db->exec("SELECT email FROM user_ WHERE email = '"+ pNewUser.email +"'");
    db->commit();
    LOG_ERROR<< "empty " << (resultEmail.empty());
    if (!resultEmail.empty()){
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::badRequest("A user with the same name already exists.")));
        delete db;
        db = nullptr;
        return;
    }

    auto hashPassword = BCrypt::generateHash(pNewUser.password);
    LOG_ERROR<<hashPassword;
    pqxx::result result = db->exec("INSERT INTO user_ (password, email) VALUES('"
                                   + hashPassword + "', '"
                                   + pNewUser.email + "')");
    db->commit();
    auto s = result.inserted_oid();
    LOG_ERROR<< s;
    LOG_DEBUG<<  s;
    auto resultUserId = db->exec("SELECT * FROM user_ WHERE email = '" + (pNewUser.email) + "'");
    LOG_DEBUG<<  resultUserId.at(0).at("id").get<int>().value();
    pNewUser.id = resultUserId.at(0).at("id").get<int>().value();
    pNewUser.role = resultUserId.at(0).at("role").get<std::string>().value();

    pqxx::result resultBasket = db->exec("INSERT INTO basket (user_id) VALUES('"
                                   + std::to_string(pNewUser.id) + "')");
    LOG_ERROR << (pNewUser.id);
    User::JwtResponseDTO userJwt (pNewUser);
    const auto jwt = jwtService::generateFromUser(userJwt);

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["token"] = jwt;
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k201Created);
    callback(res);

}

void api::userController::login(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback,
                                User::LoginDTO &&pNewUser) {
    DatabaseHelper* db = DatabaseHelper::getInstance();
    pqxx::result resultId = db->exec("SELECT * FROM user_ WHERE email = '"+ pNewUser.email +"'");
    db->commit();

    LOG_ERROR<< "empty " << (resultId.empty());
    if (resultId.empty()){
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::internal("User is not found.")));
        delete db;
        db = nullptr;

        return;
    }

    LOG_DEBUG<<pNewUser.password;

    if (!(BCrypt::validatePassword(pNewUser.password, resultId.at(0).at("password").get<std::string>().value()))){
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::internal("Wrong password specified.")));
        delete db;
        db = nullptr;
        return;
    }
    pNewUser.role = resultId.at(0).at("role").get<std::string>().value();
    pNewUser.id = resultId.at(0).at("id").get<int>().value();

    User::JwtResponseDTO userJwt(pNewUser);
    const auto jwt = jwtService::generateFromUser(userJwt);

    Json::Value ret;
    ret["token"] = jwt;

    delete db;
    db = nullptr;

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::userController::check(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback,
                                User::CheckDTO &&pNewUser) {
    LOG_DEBUG << "auth";
    User::JwtResponseDTO userJwt(pNewUser);
    const auto jwt = jwtService::generateFromUser(userJwt);
    Json::Value ret;
    ret["token"] = jwt;
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}

void api::userController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                                 int id)  {
    Json::Value ret;
    try {
        DatabaseHelper *db = DatabaseHelper::getInstance();
        auto result = db->exec("DELETE FROM user_ WHERE id = '" + std::to_string(id) + "' ");
        db->commit();

        delete db;
        db = nullptr;

        auto res = HttpResponse::newHttpJsonResponse(ret);
        res->setStatusCode(HttpStatusCode::k200OK);
        callback(res);
    }
    catch (const std::runtime_error &e){
        callback(ErrorHandlingMiddleware::errorReturn(ApiError::badRequest(e.what())));
    }

}

void api::userController::update(const drogon::HttpRequestPtr &req,
                                 std::function<void(const HttpResponsePtr &)> &&callback, User::UpdateDTO &&pNewUser) {
    LOG_DEBUG << "Update !!!";
    DatabaseHelper* db = DatabaseHelper::getInstance();
    //pqxx::result resultUser = db->exec("SELECT * FROM user_ WHERE email = '"+ pNewUser.email.value() +"'");
    //db->commit();

    //bool validate = BCrypt::validatePassword(pNewUser.password.value(), resultUser.at(0).at("password").get<std::string>().value());
    //bool validateEmail = pNewUser.email.value()==resultUser.at(0).at("email").get<std::string>().value();
    //if(pNewUser.password!=std::nullopt && !validate) {
        //auto hashPassword = BCrypt::generateHash(pNewUser.password.value());
    //}

    auto result = db->exec(UpdateDecorator::UpdateUser(pNewUser));
    db->commit();

    pqxx::result resultId = db->exec("SELECT role, email FROM user_ WHERE id = '"+ std::to_string(pNewUser.id) +"'");
    db->commit();
    pNewUser.role = resultId.at(0).at("role").get<std::string>().value();
    //pNewUser.email = resultId.at(0).at("email").get<std::string>().value();

    User::JwtResponseDTO userJwt(pNewUser);
    const auto jwt = jwtService::generateFromUser(userJwt);

    delete db;
    db = nullptr;

    Json::Value ret;
    ret["token"] = jwt;

    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(HttpStatusCode::k200OK);
    callback(res);
}