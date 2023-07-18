//
// Created by aniki on 5/10/23.
//

#ifndef ONLINESTORE_TYPE_H
#define ONLINESTORE_TYPE_H

#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>
#include <trantor/utils/Logger.h>

    namespace Type{
        class CreateDTO {
        public:
            std::string name ;

        };
        class GetAllDTO {
        public:
            int limit = 0;
            int page = 0;
        };

        class UpdateDTO {
        public:
            int id;
            std::string name;
        };
    }

namespace drogon
{
    template <>
    inline Type::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Type::CreateDTO type;
        if(json)
        {
            type.name = (*json)["name"].asString();
        }

        return type;
    }


    template<>
    inline Type::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Type::GetAllDTO type;
        if(json)
        {
            type.limit = (*json)["limit"].asInt();
            type.page = (*json)["page"].asInt();
        }

        return type;
    }

    template<>
    inline Type::UpdateDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Type::UpdateDTO type;
        if(json)
        {
            type.id = (*json)["id"].asInt();
            type.name = (*json)["name"].asString();
        }
        return type;
    }
}

#endif //ONLINESTORE_TYPE_H
