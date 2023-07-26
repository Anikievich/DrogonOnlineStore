//
// Created by aniki on 7/20/23.
//

#ifndef ONLINESTORE_RATING_H
#define ONLINESTORE_RATING_H
#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>

namespace Rating {
    class CreateDTO {
    public:
        int userID;
        int deviceID;
        int rate;
    };

    class GetAllDTO {   //ADMIN
    public:
        int limit = 0;
        int page = 0;
    };

    class GetOneDTO {   //USER
    public:
        int userID;
        int deviceID;
    };

    class UpdateDTO {
    public:
        int userID;
        int deviceID;
        std::optional<int> rate;

    };
};

namespace drogon
{
    template <>
    inline Rating::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Rating::CreateDTO rating;
        if(json)
        {
            rating.userID = (*json)["userID"].asInt();
            rating.deviceID = (*json)["deviceID"].asInt();
            rating.rate = (*json)["rate"].asInt();
        }
        return rating;
    }


    template<>
    inline Rating::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Rating::GetAllDTO rating;
        if(json)
        {
            rating.limit = (*json)["limit"].asInt();
            rating.page = (*json)["page"].asInt();
        }
        return rating;
    }
    template<>
    inline Rating::GetOneDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Rating::GetOneDTO rating;
        if(json)
        {
            rating.userID = (*json)["userID"].asInt();
            rating.deviceID = (*json)["deviceID"].asInt();
        }
        return rating;
    }
    template <>
    inline Rating::UpdateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Rating::UpdateDTO rating;
        if(json)
        {
            rating.userID = (*json)["userID"].asInt();
            rating.deviceID = (*json)["deviceID"].asInt();

            ((*json)["rate"].empty()) ? rating.rate == std::nullopt : rating.rate = (*json)["rate"].asInt();
        }
        return rating;
    }

}

#endif //ONLINESTORE_RATING_H
