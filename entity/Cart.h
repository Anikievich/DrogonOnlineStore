//
// Created by aniki on 7/18/23.
//

#ifndef ONLINESTORE_CART_H
#define ONLINESTORE_CART_H
#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>

namespace Cart {
    class AddDTO {
    public:
        int userID;
        int cartID;
        int deviceID;

    };
    class GetAllDTO {   //ADMIN
    public:
        int limit = 0;
        int page = 0;
    };
    class GetUserCartDTO {   //USER
    public:
        int userID;
        int cartID;
        int limit = 0;
        int page = 0;
    };

    class RemoveDTO {
    public:
        int userID;
        int cartID;
        int deviceID;

    };

};

namespace drogon
{
    template <>
    inline Cart::AddDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Cart::AddDTO cart;
        if(json)
        {
            cart.userID = (*json)["userID"].asInt();
            cart.deviceID = (*json)["deviceID"].asInt();
        }
        return cart;
    }


    template<>
    inline Cart::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Cart::GetAllDTO cart;
        if(json)
        {
            cart.limit = (*json)["limit"].asInt();
            cart.page = (*json)["page"].asInt();
        }
        return cart;
    }
    template<>
    inline Cart::GetUserCartDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Cart::GetUserCartDTO cart;
        if(json)
        {
            cart.userID = (*json)["userID"].asInt();
            cart.limit = (*json)["limit"].asInt();
            cart.page = (*json)["page"].asInt();
        }
        return cart;
    }
    template <>
    inline Cart::RemoveDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Cart::RemoveDTO cart;
        if(json)
        {
            cart.userID = (*json)["userID"].asInt();
            cart.deviceID = (*json)["deviceID"].asInt();
        }
        return cart;
    }

}
#endif //ONLINESTORE_CART_H
