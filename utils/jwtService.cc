//
// Created by aniki on 7/5/23.
//

#include "jwtService.h"
#include <utility>
#include <unordered_map>
#include <chrono>

//const string jwtService::secret = drogon::app().getCustomConfig()["jwt-secret"].asString();
const string jwtService::secret = "nRvyYC4soFxBdZ-F-5Nnzz5USXstR1YylsTd-mA0aKtI9HUlriGrtkf-TiuDapkLiUCogO3JOK7kwZisrHp6wA";
//const int jwtService::duration = drogon::app().getCustomConfig()["jwt-sessionTime"].asInt();
const int jwtService::duration = 86400;
const verifier <jwt::default_clock, jwt::traits::kazuho_picojson> jwtService::_verifier = verify()
        .allow_algorithm(algorithm::hs256{jwtService::secret})
        .with_issuer("auth0");


auto jwtService::generateFromUser(User::JwtResponseDTO const& user) -> string {
    auto a = std::chrono::system_clock::now();
    //i<<std::chrono::system_clock::now();
    std::time_t t= std::chrono::system_clock::to_time_t (a);
    LOG_DEBUG<< ctime(&t);
    LOG_DEBUG<<duration;
    return jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds (duration))
            .set_payload_claim("id", jwt::claim(to_string(user.id)))
            .set_payload_claim("role", jwt::claim(user.role))
            .sign(jwt::algorithm::hs256{secret});
}

auto jwtService::getUserIdFromJwt(const string& token) -> User::getUserIdFilterDTO{
    auto decoded = jwt::decode(token);
    LOG_DEBUG<<jwtService::secret;
    LOG_DEBUG<<jwtService::duration;
    LOG_ERROR<<1;
    User::getUserIdFilterDTO user;
    try {
        _verifier.verify(decoded);
    } catch (const runtime_error &e) {
        LOG_ERROR << e.what();
        user.id = nullopt;
        return user;
    }

    LOG_DEBUG << "checkDTO 1";
    user.id =  stoi(decoded.get_payload_claim("id").as_string());

    LOG_ERROR<<2;
    LOG_ERROR<<decoded.get_payload_claim("id").as_string();
    return user;
}
auto jwtService::getUserRoleFromJwt(const string& token) -> User::getUserRoleFilterDTO{
    auto decoded = jwt::decode(token);
    LOG_DEBUG<<jwtService::secret;
    LOG_DEBUG<<jwtService::duration;
    LOG_ERROR<<1;
    User::getUserRoleFilterDTO user;
    try {
        _verifier.verify(decoded);
    } catch (const runtime_error &e) {
        LOG_ERROR << e.what();
        user.id = nullopt;
        return user;
    }

    LOG_DEBUG << "checkDTO 1";
    user.id =  stoi(decoded.get_payload_claim("id").as_string());
    user.role = decoded.get_payload_claim("role").as_string();

    LOG_ERROR<<2;
    LOG_ERROR<<decoded.get_payload_claim("id").as_string();
    return user;
}

auto jwtService::getCurrentUserIdFromRequest(const HttpRequestPtr &req) -> User::getUserIdFilterDTO{
    //LOG_ERROR<<req->getHeader("Authorization").substr(6);
    auto token = req->getHeader("Authorization").substr(6);
    return getUserIdFromJwt(token);
}
auto jwtService::getCurrentUserRoleFromRequest(const HttpRequestPtr &req) -> User::getUserRoleFilterDTO{
   // LOG_ERROR<<req->getHeader("Authorization").substr(6);
    auto token = req->getHeader("Authorization").substr(6);
    return getUserRoleFromJwt(token);
}



