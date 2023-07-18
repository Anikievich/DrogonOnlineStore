//
// Created by aniki on 5/10/23.
//

#ifndef ONLINESTORE_USER_H
#define ONLINESTORE_USER_H

#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>
#include <jwt-cpp/jwt.h>
#include <trantor/utils/Logger.h>


namespace User{
    struct RegistrationDTO{
        int id;
        std::string email;
        std::string password;
        std::string role;
    };

    struct LoginDTO{
        int id;
        std::string email;
        std::string password;
        std::string role;
    };

    struct CheckDTO{
        int id;
        std::string role;
    };

    struct UpdateDTO{
        int id;
        std::optional <std::string> email;
        std::optional <std::string> password;
        std::string role;
    };
    struct JwtResponseDTO{
        explicit JwtResponseDTO(RegistrationDTO const& user) : id(user.id), role(user.role){};
        explicit JwtResponseDTO(LoginDTO const& user) : id(user.id), role(user.role){};
        explicit JwtResponseDTO(CheckDTO const& user) : id(user.id), role(user.role){};
        explicit JwtResponseDTO(UpdateDTO const& user) : id(user.id), role(user.role){};
        int id;
        std::string role;
    };

    struct getUserIdFilterDTO{
        std::optional <int> id;
    };
    struct getUserRoleFilterDTO{
        std::optional <int> id;
        std::string role;
    };


}
namespace drogon
{
    template <>
    inline User::RegistrationDTO fromRequest(const HttpRequest &req)
    {
        auto const& json = req.getJsonObject();
        User::RegistrationDTO user;
        if(json)
        {
            user.password = (*json)["password"].asString();
            user.email = (*json)["email"].asString();
        }
        return user;
    }

    template <>
    inline User::LoginDTO fromRequest(const HttpRequest &req)
    {
        auto const& json = req.getJsonObject();
        User::LoginDTO user;
        if(json)
        {
            user.password = (*json)["password"].asString();
            user.email = (*json)["email"].asString();
        }
        return user;
    }

    template <>
    inline User::CheckDTO fromRequest(const HttpRequest &req)
    {
        LOG_DEBUG << "checkDTO";
        auto const& token = req.getHeader("Authorization").substr(6);
        User::CheckDTO user;
        auto decoded = jwt::decode(token);
        LOG_DEBUG << "checkDTO 1";
        user.id =  stoi(decoded.get_payload_claim("id").as_string());
        user.role = decoded.get_payload_claim("role").as_string();
        LOG_DEBUG << "checkDTO 2";
        return user;
    }

    template <>
    inline User::UpdateDTO fromRequest(const HttpRequest &req)
    {
        auto const& json = req.getJsonObject();
        User::UpdateDTO user;

        LOG_DEBUG <<(*json)["password"].empty();
        LOG_DEBUG <<(*json)["email"].empty();
        if(json)
        {
            user.id = (*json)["id"].asInt();
            LOG_DEBUG <<"User id : " << user.id;
            ((*json)["password"].empty())? user.password = std::nullopt : user.password = (*json)["password"].asString();
           // LOG_DEBUG <<"User id : "<< user.password.value();
            ((*json)["email"].empty()) ?  user.email = std::nullopt : user.email = (*json)["email"].asString();
         //   LOG_DEBUG <<"User id : "<< user.email.value();
        }
       // LOG_DEBUG << "Update password "<<user.password.value();
       // LOG_DEBUG << "Update email "<<user.email.value();
        return user;
    }
}
#endif //ONLINESTORE_USER_H
