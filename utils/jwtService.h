//
// Created by aniki on 7/5/23.
//
//#pragma once
#ifndef ONLINESTORE_JWTSERVICE_H
#define ONLINESTORE_JWTSERVICE_H
#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include "../entity/User.h"
#include <picojson.h>

using namespace std;
using namespace drogon;
using namespace jwt;

class jwtService {
public:

    //User::JwtResponseDTO const& user;
    static auto generateFromUser(User::JwtResponseDTO const& user) -> string;
    static auto getUserIdFromJwt(const string& token)-> User::getUserIdFilterDTO;
    static auto getUserRoleFromJwt(const string& token)-> User::getUserRoleFilterDTO;
    static auto getCurrentUserIdFromRequest(const HttpRequestPtr &req) -> User::getUserIdFilterDTO;
    static auto getCurrentUserRoleFromRequest(const HttpRequestPtr &req) -> User::getUserRoleFilterDTO;

private:
    static const string secret;
    static const int duration;
    static const verifier <jwt::default_clock, jwt::traits::kazuho_picojson> _verifier;

  //  static const auto _verifier = verify()
  //  .allow_algorithm(algorithm::hs256{jwtService::secret})
  //  .with_issuer("auth0");
};


#endif //ONLINESTORE_JWTSERVICE_H
