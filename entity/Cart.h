//
// Created by aniki on 7/18/23.
//

#ifndef ONLINESTORE_CART_H
#define ONLINESTORE_CART_H
#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>

namespace Cart {
    class CreateDTO {
    public:
        int deviceID;
        int cartID;

    };
    class GetAllDTO {   //admin
    public:
        int limit = 0;
        int page = 0;
    };

    class UpdateDTO {
    public:
        int id;
        std::string name;
    };

};

namespace drogon
{
    template <>
    inline Cart::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Cart::CreateDTO brand;
        if(json)
        {
            brand.name = (*json)["name"].asString();
        }
        return brand;
    }


    template<>
    inline Cart::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Cart::GetAllDTO brand;
        if(json)
        {
            brand.limit = (*json)["limit"].asInt();
            brand.page = (*json)["page"].asInt();
        }
        return brand;
    }
    template<>
    inline Cart::UpdateDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Cart::UpdateDTO brand;
        if(json)
        {
            brand.id = (*json)["id"].asInt();
            brand.name = (*json)["name"].asString();
        }
        return brand;
    }

}
#endif //ONLINESTORE_CART_H
