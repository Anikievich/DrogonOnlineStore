//
// Created by aniki on 7/20/23.
//

#ifndef ONLINESTORE_DEVICEINFO_H
#define ONLINESTORE_DEVICEINFO_H

#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>

namespace DeviceInfo{
    struct CreateDTO {
    public:
        std::string title;
        std::string description;
        int deviceID;
    };
    class GetAllDTO {
    public:

        int limit = 0;
        int page = 0;
    };

    struct UpdateDTO {
    public:
        int id;
        std::optional <std::string> title;
        std::optional <std::string>  description;
        std::optional <int> deviceID;
    };
}

namespace drogon
{
    template <>
    inline DeviceInfo::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        DeviceInfo::CreateDTO deviceInfo;
        if(json)
        {
            deviceInfo.deviceID = (*json)["deviceID"].asInt();
            deviceInfo.description = (*json)["info"]["description"].asString();
            deviceInfo.title = (*json)["info"]["title"].asString();
        }
        return deviceInfo;
    }

    template<>
    inline DeviceInfo::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        DeviceInfo::GetAllDTO deviceInfo;
        if(json)
        {
            deviceInfo.limit = (*json)["limit"].asInt();
            deviceInfo.page = (*json)["page"].asInt();
        }
        return deviceInfo;
    }

    template <>
    inline DeviceInfo::UpdateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        DeviceInfo::UpdateDTO deviceInfo;
        if(json)
        {
            deviceInfo.id = (*json)["id"].asInt();

            ((*json)["title"].empty())? deviceInfo.title = std::nullopt : deviceInfo.title = (*json)["title"].asString();
            ((*json)["deviceID"].empty()) ?  deviceInfo.deviceID = std::nullopt : deviceInfo.deviceID = (*json)["deviceID"].asInt();
            ((*json)["description"].empty()) ? deviceInfo.description = std::nullopt :deviceInfo.description  = (*json)["description"].asString();
        }
        return deviceInfo;
    }

}


#endif //ONLINESTORE_DEVICEINFO_H
