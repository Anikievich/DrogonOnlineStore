//
// Created by aniki on 5/10/23.
//

#ifndef ONLINESTORE_BRAND_H
#define ONLINESTORE_BRAND_H
#include <iostream>
#include <optional>
#include <drogon/HttpRequest.h>

namespace Brand{
    class CreateDTO {
    public:
        std::string name;

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
    inline Brand::CreateDTO fromRequest(const HttpRequest &req)
    {
        const auto& json = req.getJsonObject();
        Brand::CreateDTO brand;
        if(json)
        {
            brand.name = (*json)["name"].asString();
        }
        return brand;
    }


    template<>
    inline Brand::GetAllDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Brand::GetAllDTO brand;
        if(json)
        {
            brand.limit = (*json)["limit"].asInt();
            brand.page = (*json)["page"].asInt();
        }
        return brand;
    }
    template<>
    inline Brand::UpdateDTO fromRequest(const HttpRequest &req) {
        const auto& json = req.getJsonObject();
        Brand::UpdateDTO brand;
        if(json)
        {
            brand.id = (*json)["id"].asInt();
            brand.name = (*json)["name"].asString();
        }
        return brand;
    }

}



#endif //ONLINESTORE_BRAND_H
