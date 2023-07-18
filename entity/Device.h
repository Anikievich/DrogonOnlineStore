//
// Created by aniki on 5/10/23.
//

#ifndef ONLINESTORE_DEVICE_H
#define ONLINESTORE_DEVICE_H

#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>


namespace Device{
    struct CreateDTO {
    public:
        std::string name;
        float price;
        std::string image;
        int brandID;
        int typeID;
        Json::Value info;

        std::string infoTitle;
        std::string infoDescription;
        int infoDeviceID;
    };
    class GetAllDTO {
    public:

        int brandID;
        int typeID;

        int limit = 0;
        int page = 0;
    };

    struct UpdateDTO {
    public:
        int id;
        std::optional <std::string> name;
        std::optional <float> price;
        std::optional <std::string> image;
        std::optional <int> brandID;
        std::optional <int> typeID;
    };
}

namespace drogon
{
    template <>
    inline Device::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Device::CreateDTO device;
        if(json)
        {
            device.name = (*json)["name"].asString();
            device.price = (*json)["price"].asFloat();
            device.image = (*json)["image"].asString();
            device.brandID = (*json)["brandID"].asInt();
            device.typeID = (*json)["typeID"].asInt();
            device.info = (*json)["info"];

            device.infoTitle = (*json)["info"]["description"].asString();
            device.infoDescription = (*json)["info"]["title"].asString();

        }

        return device;
    }

    template<>
    inline Device::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Device::GetAllDTO device;
        if(json)
        {
            device.brandID = (*json)["brandID"].asInt();
            device.typeID = (*json)["typeID"].asInt();

            device.limit = (*json)["limit"].asInt();
            device.page = (*json)["page"].asInt();
        }
        return device;
    }

    template <>
    inline Device::UpdateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Device::UpdateDTO device;
        if(json)
        {
            device.id = (*json)["id"].asInt();

            ((*json)["name"].empty())? device.name = std::nullopt : device.name = (*json)["name"].asString();
            ((*json)["price"].empty()) ?  device.price = std::nullopt : device.price = (*json)["price"].asFloat();
            ((*json)["image"].empty())? device.image = std::nullopt : device.image = (*json)["image"].asString();
            ((*json)["brandID"].empty()) ?  device.brandID = std::nullopt : device.brandID = (*json)["brandID"].asInt();
            ((*json)["typeID"].empty()) ?  device.typeID = std::nullopt : device.typeID = (*json)["typeID"].asInt();

        }
        return device;
    }

}


#endif //ONLINESTORE_DEVICE_H
